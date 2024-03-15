// #include <SPI.h>
#include <TFT_eSPI.h>  // Include the graphics library
#include "globalVars.h"
TFT_eSPI tft_screen = TFT_eSPI();  // Create object "tft"


#define TFT_MOSI 15  // In some display driver board, it might be written as "SDA" and so on.
#define TFT_SCLK 14
#define TFT_CS 5    // Chip select control pin
#define TFT_DC 27   // Data Command control pin
#define TFT_RST 33  // Reset pin (could connect to Arduino RESET pin)
#define TFT_BL 22   // LED back-light
#define GC9A01_DRIVER
#define TFT_BLACK 0x0000

uint16_t fg_color = 0x110;
uint16_t bg_color = TFT_BLACK;  // This is the background colour used for smoothing (anti-aliasing)

uint16_t x = 120;  //random(tft.width());  // Position of centre of arc
uint16_t y = 120;  //random(tft.height());

uint8_t radius = 120;                       // Outer arc radius
uint8_t thickness = 15;                     // Thickness
uint8_t inner_radius = radius - thickness;  // Calculate inner radius (can be 0 for circle segment)
bool arc_end = 0;
uint16_t start_angle = 0;


bool up = true;

void screen_init() {
  tft_screen.init();
  tft_screen.setRotation(0);
  tft_screen.fillScreen(TFT_BLACK);
}

void set_temp() {
  tft_screen.fillRect(x - 25, y - 15, 50, 30, bg_color);
  tft_screen.drawRect(x - 26, y - 15, 50, 30, fg_color);
  tft_screen.setTextColor(TFT_WHITE);
  tft_screen.setTextSize(2);
  //tft.setCursor(x, y);
  tft_screen.setTextDatum(CC_DATUM);
  //tft.print(String(angle));
  tft_screen.drawNumber(angle, x, y, 2);

  //tft.drawCentreString(String(angle), x, y, 2);
  /*static uint32_t count = 0;
    if (up) {
    angle++;
    if (angle >= 360) {
      up = false;
    }
    } else {
    angle--;
    if (angle <= 1) {
      up = true;
    }
    }*/

  uint16_t end_angle = angle;  // End angle must be in range 0 to 360

  // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
  // tft.fillScreen(TFT_BLACK);
  tft_screen.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color, arc_end);
  tft_screen.drawSmoothArc(x, y, radius, inner_radius, end_angle, start_angle, bg_color, bg_color, arc_end);

  //count++;
}
