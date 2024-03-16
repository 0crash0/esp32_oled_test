#include "globalVars.h"

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "config.h"


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
     <style type="text/css">
.align {
  -webkit-box-align: center;
      -ms-flex-align: center;
          align-items: center;
  display: -webkit-box;
  display: -ms-flexbox;
  display: flex;
  -webkit-box-orient: vertical;
  -webkit-box-direction: normal;
      -ms-flex-direction: column;
          flex-direction: column;
  -webkit-box-pack: center;
      -ms-flex-pack: center;
          justify-content: center;
}

.grid {
  margin-left: auto;
  margin-right: auto;
  max-width: 320px;
  max-width: 20rem;
  width: 90%;
}

* {
  -webkit-box-sizing: inherit;
          box-sizing: inherit;
}

html {
  -webkit-box-sizing: border-box;
          box-sizing: border-box;
  font-size: 100%;
  height: 100%;
}

body {
  background-color: #2c3338;
  color: #606468;
  font-family: 'Open Sans', sans-serif;
  font-size: 14px;
  font-size: 0.875rem;
  font-weight: 400;
  height: 100%;
  line-height: 1.5;
  margin: 0;
  min-height: 100vh;
}

a {
  color: #eee;
  outline: 0;
  text-decoration: none;
}

a:focus,
a:hover {
  text-decoration: underline;
}

input {
  background-image: none;
  border: 0;
  color: inherit;
  font: inherit;
  margin: 0;
  outline: 0;
  padding: 0;
  -webkit-transition: background-color 0.3s;
  transition: background-color 0.3s;
}

input[type='submit'] {
  cursor: pointer;
}

.form {
  margin: -14px;
  margin: -0.875rem;
}

.form input[type='password'],
.form input[type='text'],
.form input[type='submit'] {
  width: 100%;
}

.form__field {
  display: -webkit-box;
  display: -ms-flexbox;
  display: flex;
  margin: 14px;
  margin: 0.875rem;
}

.form__input {
  -webkit-box-flex: 1;
      -ms-flex: 1;
          flex: 1;
}

.login {
  color: #eee;
}

.login label,
.login input[type='text'],
.login input[type='password'],
.login input[type='submit'] {
  border-radius: 0.25rem;
  padding: 16px;
  padding: 1rem;
}

.login label {
  background-color: #363b41;
  border-bottom-right-radius: 0;
  border-top-right-radius: 0;
  padding-left: 20px;
  padding-left: 1.25rem;
  padding-right: 20px;
  padding-right: 1.25rem;
}

.login input[type='password'],
.login input[type='text'] {
  background-color: #3b4148;
  border-bottom-left-radius: 0;
  border-top-left-radius: 0;
}

.login input[type='password']:focus,
.login input[type='password']:hover,
.login input[type='text']:focus,
.login input[type='text']:hover {
  background-color: #434a52;
}

.login input[type='submit'] {
  background-color: #ea4c88;
  color: #eee;
  font-weight: 700;
  text-transform: uppercase;
}

.login input[type='submit']:focus,
.login input[type='submit']:hover {
  background-color: #d44179;
}

p {
  margin-bottom: 24px;
  margin-bottom: 1.5rem;
  margin-top: 24px;
  margin-top: 1.5rem;
}

.text--center {
  text-align: center;
}
</style>
</head>
<body>
  <h2>ESP Web Server</h2>
  <button onclick="logoutButton()">Logout</button>
  <p>Ouput - GPIO 2 - State <span id="state">%STATE%</span></p>
  %BUTTONPLACEHOLDER%

<div class="grid">
    <form action="savessid" method="POST" class="form login">
      <div class="form__field">
        <label for="login__username"><span>SSID</span></label>
        <input id="login__username" type="text" name="ssid" class="form__input" placeholder="SSID" required="">
      </div>
      <div class="form__field">
        <label for="login__password"><span class="">Pass</span></label>
        <input id="login__password" type="password" name="password" class="form__input" placeholder="Password" required="">
      </div>
      <div class="form__field">
        <input type="submit" value="Save">
      </div>
    </form>
  </div>

  <div class="grid">
    <form action="settemp" method="POST" class="form login">
      <div class="form__field">
        <label for="temp"><span>Temp</span></label>
        <input id="temp" type="text" name="value" class="form__input" placeholder="temp" required="">
      </div>
      <div class="form__field">
        <input type="submit" value="Save">
      </div>
    </form>
  </div>

<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ 
    xhr.open("GET", "/update?state=1", true); 
    document.getElementById("state").innerHTML = "ON";  
  }
  else { 
    xhr.open("GET", "/update?state=0", true); 
    document.getElementById("state").innerHTML = "OFF";      
  }
  xhr.send();
}
function logoutButton() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/logout", true);
  xhr.send();
  setTimeout(function(){ window.open("/logged-out","_self"); }, 1000);
}
</script>
</body>
</html>
)rawliteral";

const char logout_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <p>Logged out or <a href="/">return to homepage</a>.</p>
  <p><strong>Note:</strong> close all web browser tabs to complete the logout process.</p>
</body>
</html>
)rawliteral";

AsyncWebServer server(80);
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
const char *PARAM_MESSAGE = "message";
void prepare_server() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send_P(200, "text/html", index_html);
  });

  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(401);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", logout_html);
  });




  server.on("/settemp", HTTP_GET, [](AsyncWebServerRequest *request) {
    String message;
    if (request->hasParam("value")) {
      message = request->getParam("value")->value();
      angle = message.toInt();
      storeTempValue();

    } else {
      message = "No message sent";
    }
    request->send(200, "text/plain", "Hello, GET: " + message);
  });

  // Send a POST request to <IP>/post with a form field message set to <message>
  server.on("/settemp", HTTP_POST, [](AsyncWebServerRequest *request) {
    String message;
    if (request->hasParam("value")) {
      message = request->getParam("value")->value();
      angle = message.toInt();
      storeTempValue();

    } else {
      message = "No message sent";
    }
    request->send(200, "text/plain", "Hello, POST: " + message);
  });

  server.on("/savessid", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    if (request->hasParam("ssid", true) and request->hasParam("password", true)) {
      ssid = request->getParam("ssid", true)->value();
      password = request->getParam("password", true)->value();
      //Serial.println("/savessid, SSID: " + ssid + " PASS: " + password);
      storeWiFiCreds();
    }
    request->send(200, "text/plain", "Hello, SSID: " + ssid + " PASS: " + password);
  });

  server.onNotFound(notFound);

  server.begin();
}
