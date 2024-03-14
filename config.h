#include "screen.h"
#include <EEPROM.h>
#include <Preferences.h>   moove eeprom to preferences
Preferences pref;
String ssid;
String password;

void saveEEprom() {

  //if (datachanged) {
    //datachanged = false;
    Serial.println("Save in EEprom");
    
    EEPROM.put(0, ssid);
    EEPROM.put(10, angle);
  //}
  EEPROM.commit();
}


void prefInit(){
  preferences.begin("WiFiCredential", true); 
  ssid = preferences.getString("SSID", ""); 
  password = preferences.getString("WPassword", "");

  if (ssid == "" || password == ""){
    Serial.println("No values saved for network credentials");
  }
}

void storeWiFiCreds(){
  preferences.begin("WiFiCredential", false);
  preferences.putString("SSID", ssid); 
  preferences.putString("WPassword", password);

  Serial.println("Network Credentials have been Saved");

  preferences.end();
}
