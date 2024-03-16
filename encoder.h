#include "config.h"
#include <ESP32Encoder.h>
#include "esp_task_wdt.h"

#define BUTTON_PIN 17 // GPIO21 pin connected to button

 // Encoder A and B pins connected with 1K series resistor to pins 4 and 5, common pin to ground.
  //         |- A   --- 1K --- pin 16
  //  >=[enc]|- GND
  //         |- B   --- 1K --- pin 4


static IRAM_ATTR void enc_cb(void* arg) {
  ESP32Encoder* enc = (ESP32Encoder*) arg;
  angle=enc->getCount();
  //Serial.printf("enc cb: count: %d\n", enc->getCount());
  //static bool leds = false;
  //digitalWrite(LED_BUILTIN, (int)leds);
  //leds = !leds;
}

extern bool loopTaskWDTEnabled;
extern TaskHandle_t loopTaskHandle;
ESP32Encoder encoder(true, enc_cb);

void encoderInit(){
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), storeTempValue, FALLING);
  loopTaskWDTEnabled = true;
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  
  encoder.attachSingleEdge(16, 4);
  encoder.setFilter(1023);
  encoder.setCount(angle);
  esp_task_wdt_add(loopTaskHandle);
}