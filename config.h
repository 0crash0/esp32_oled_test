#include <Preferences.h>  //moove eeprom to preferences
#include "globalVars.h"
#ifndef __CONFIG_H__
#define __CONFIG_H__
Preferences pref;




void prefInit() {
  pref.begin("WiFiCredential", true);
  ssid = pref.getString("SSID", "");
  password = pref.getString("WPassword", "");
  pref.end();
  pref.begin("Temp", true);
  angle = pref.getInt("value", 50);
  pref.end();
  Serial.println("PREFINIT, SSID: " + ssid + " PASS: " + password);
  if (ssid == "" || password == "") {
    Serial.println("No values saved for network credentials");
  }
}

void storeWiFiCreds() {
  pref.begin("WiFiCredential", false);
  pref.putString("SSID", ssid);
  pref.putString("WPassword", password);

  //Serial.println("Network Credentials have been Saved");
  //Serial.println("Hello, SSID: " + ssid + " PASS: " + password);
  pref.end();
}

void storeTempValue() {
  pref.begin("Temp", false);
  pref.putInt("value", angle);
 // Serial.println("temp saved");
  pref.end();
}
#endif
