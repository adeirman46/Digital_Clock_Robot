#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define TFT_GREY 0xBDF7
#define TFT_BLUE 0x001F
#define TFT_BLACK 0x0000
#define TFT_CYAN 0x07FF
#define TFT_RED 0xF800
#define TFT_GREEN 0x07E0

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
float sdeg=0, mdeg=0, hdeg=0;
uint16_t osx=88, osy=110, omx=88, omy=110, ohx=88, ohy=110;  // Saved H, M, S x & y coords
uint16_t x0=0, x1=0, yy0=0, yy1=0;
uint32_t targetTime = 0;                    // for next 1 second timeout

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_GREY);
  tft.setTextColor(TFT_GREEN, TFT_GREY);  // Adding a black background colour erases previous text automatically
  
  // Draw clock face
  tft.fillCircle(88, 110, 106, TFT_BLUE);
  tft.fillCircle(88, 110, 102, TFT_BLACK);

  // Draw 12 lines
  for(int i = 0; i<360; i+= 30) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*102+88;
    yy0 = sy*102+110;
    x1 = sx*90+88;
    yy1 = sy*90+110;

    tft.drawLine(x0, yy0, x1, yy1, TFT_BLUE);
  }

  // Draw 60 dots
  for(int i = 0; i<360; i+= 6) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*95+88;
    yy0 = sy*95+110;
    
    tft.drawPixel(x0, yy0, TFT_BLUE);
    if(i==0 || i==180) tft.fillCircle(x0, yy0, 2, TFT_CYAN);
    if(i==90 || i==270) tft.fillCircle(x0, yy0, 2, TFT_CYAN);
  }

  tft.fillCircle(88, 110, 6, TFT_RED);

  // Draw text at position 88, 185 using fonts 4
  // tft.drawCentreString("Time flies",88,185,4);

  targetTime = millis() + 1000; 
}

void loop() {
  DateTime now = rtc.now();

  if (targetTime < millis()) {
    targetTime = millis()+1000;
    uint8_t ss = now.second();
    uint8_t mm = now.minute();
    uint8_t hh = now.hour();

    // Pre-compute hand degrees, x & y coords for a fast screen update
    sdeg = ss*6;                  // 0-59 -> 0-354
    mdeg = mm*6+sdeg*0.01666667;  // 0-59 -> 0-360 - includes seconds
    hdeg = hh*30+mdeg*0.0833333;  // 0-11 -> 0-360 - includes minutes and seconds
    hx = cos((hdeg-90)*0.0174532925);    
    hy = sin((hdeg-90)*0.0174532925);
    mx = cos((mdeg-90)*0.0174532925);    
    my = sin((mdeg-90)*0.0174532925);
    sx = cos((sdeg-90)*0.0174532925);    
    sy = sin((sdeg-90)*0.0174532925);

    if (ss==0) {
      // Erase hour and minute hand positions every minute
      tft.drawLine(ohx, ohy, 88, 110, TFT_BLACK);
      ohx = hx*54+88;    
      ohy = hy*54+110;
      tft.drawLine(omx, omy, 88, 110, TFT_BLACK);
      omx = mx*72+88;    
      omy = my*72+110;
    }

    // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
    tft.drawLine(osx, osy, 88, 110, TFT_BLACK);
    tft.drawLine(ohx, ohy, 88, 110, TFT_WHITE);
    tft.drawLine(omx, omy, 88, 110, TFT_WHITE);
    osx = sx*94+88;    
    osy = sy*94+110;
    tft.drawLine(osx, osy, 88, 110, TFT_RED);

    tft.fillCircle(88, 110, 6, TFT_RED);
  }
}
