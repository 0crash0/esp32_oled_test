//ESP32 dev module

#include "wifi.h"
#include "server.h"
#include "screen.h"
#include "config.h"
#include "encoder.h"


void setup(void) {
  
  Serial.begin(115200);
  prefInit();
  screen_init();

  connect_WIFI();
  Serial.print("Start server");
  set_temp();
  prepare_server();

 

  encoderInit();
}


unsigned long previousMillis = 0;

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 250) {
    //angle=encoder.getCount();
    set_temp();
  }
  
  //if (count < 30)
  //delay(250);  // After 15s draw as fast as possible!
}
