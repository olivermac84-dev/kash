#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <SPI.h>
#include "image_data.h"

#define TFT_CS   7  
#define TFT_DC   5  
#define TFT_RST  4
#define NEXT_BTN 15
#define PREV_BTN 14

Adafruit_GC9A01A tft = Adafruit_GC9A01A(TFT_CS, TFT_DC, TFT_RST);

const int totalImages = 2; 
int currentIndex = 0;

void updateUI() {

  if (currentIndex == 0) tft.drawRGBBitmap(0, 0, image1, 240, 240);
  else if (currentIndex == 1) tft.drawRGBBitmap(0, 0, image2, 240, 240);


  tft.fillRect(80, 200, 80, 25, GC9A01A_BLACK); 
  tft.drawRoundRect(78, 198, 84, 29, 5, GC9A01A_WHITE); 
  
  tft.setCursor(95, 205);
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(2);
  tft.print(currentIndex + 1);
  tft.print("/");
  tft.print(totalImages);
}

void setup() {
  SPI.setSCK(2);
  SPI.setTX(3);

  pinMode(NEXT_BTN, INPUT_PULLUP);
  pinMode(PREV_BTN, INPUT_PULLUP);

  tft.begin(24000000); 
  tft.setRotation(0);
  tft.fillScreen(GC9A01A_BLACK);

  updateUI(); 
}

void loop() {
  
  if (digitalRead(NEXT_BTN) == LOW) {
    currentIndex++;
    if (currentIndex >= totalImages) currentIndex = 0; 
    updateUI();
    delay(300); 
  }

  
  if (digitalRead(PREV_BTN) == LOW) {
    currentIndex--;
    if (currentIndex < 0) currentIndex = totalImages - 1; 
    updateUI();
    delay(300); // Debounce delay
  }
}
