#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "globalVars.h"

int tryDelay = 500;
int numberOfTries = 20;

const char *ssidAP = "ESP32";
const char *passwordAP = "";

void startWifiAP() {
  if (!WiFi.softAP(ssidAP, passwordAP)) {
    log_e("Soft AP creation failed.");
    return;
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("wifi AP started");
}

void connect_WIFI() {
  if (ssid == "" || password == "") {
    Serial.println("No values saved for network credentials");
    Serial.println("Configuring access point...");

    // You can remove the password parameter if you want the AP to be open.
    // a valid password must have more than 7 characters
    startWifiAP();
  } else {
    // Connect to Wi-Fi

    Serial.print("[WiFi] Connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("Hello, SSID: " + ssid + " PASS: " + password);

    while (true) {

      switch (WiFi.status()) {
        case WL_NO_SSID_AVAIL:
          Serial.println("[WiFi] SSID not found");
          break;
        case WL_CONNECT_FAILED:
          Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
          return;
          break;
        case WL_CONNECTION_LOST:
          Serial.println("[WiFi] Connection was lost");
          break;
        case WL_SCAN_COMPLETED:
          Serial.println("[WiFi] Scan is completed");
          break;
        case WL_DISCONNECTED:
          Serial.println("[WiFi] WiFi is disconnected");
          break;
        case WL_CONNECTED:
          Serial.println("[WiFi] WiFi is connected!");
          Serial.print("[WiFi] IP address: ");
          Serial.println(WiFi.localIP());
          return;
          break;
        default:
          Serial.print("[WiFi] WiFi Status: ");
          Serial.println(WiFi.status());
          break;
      }
      delay(tryDelay);

      if (numberOfTries <= 0) {
        Serial.print("[WiFi] Failed to connect to WiFi!");
        // Use disconnect function to force stop trying to connect
        WiFi.disconnect();
        startWifiAP();
        return;
      } else {
        numberOfTries--;
      }
    }
  }
}
