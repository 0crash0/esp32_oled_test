#include "screen.h"
#include <EEPROM.h>
//#include <Preferences.h>   moove eeprom to preferences

void saveEEprom() {
  //if (datachanged) {
    //datachanged = false;
    Serial.println("Save in EEprom");
    
    EEPROM.put(0, ssid);
    EEPROM.put(10, angle);
  //}
  EEPROM.commit();
}

/**
void prefInit(){
  preferences.begin("my-app", false); 
}*/
