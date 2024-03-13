//ESP32 dev module

#include "wifi.h"
#include "server.h"

//wifi

#define EEPROM_SIZE 2048



void setup(void) {
    Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  char read_eeprom[8];
  Serial.print("ITEM_INSIDE_SERIAL get=");
    EEPROM.get(0,read_eeprom);
    Serial.println(read_eeprom);
    Serial.print("ITEM_INSIDE_SERIAL get=");
    EEPROM.get(10,angle);
    Serial.println(angle);
  


  screen_init();

  connect_WIFI();
  Serial.print("Start server");
  set_temp();
  prepare_server();
  
}

void loop() {

  //if (count < 30)
  //delay(10);  // After 15s draw as fast as possible!
}
