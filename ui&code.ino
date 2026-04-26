#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <SPI.h>
#include <math.h>
#include "image_data.h"


#define TFT_CS    7  
#define TFT_DC    5  
#define TFT_RST   4
#define BLK_PIN   13   // Backlight පාලනය සඳහා GPIO 13 භාවිතා කරයි
#define NEXT_BTN  15
#define PREV_BTN  14 

Adafruit_GC9A01A tft = Adafruit_GC9A01A(TFT_CS, TFT_DC, TFT_RST);

int currentIndex = 0;
const int totalImages = 6; 
const uint16_t* album[] = {image1, image2, image3, image4, image5, image6};


unsigned long lastActivityTime = 0;
const unsigned long screenOffDelay = 120000; 

void setup() {
  SPI.setSCK(2);
  SPI.setTX(3);
  
  pinMode(NEXT_BTN, INPUT_PULLUP);
  pinMode(PREV_BTN, INPUT_PULLUP);
  pinMode(BLK_PIN, OUTPUT);
  
 
  digitalWrite(BLK_PIN, HIGH); 

  tft.begin(24000000); 
  tft.setRotation(0);
  
  runStartupAnimation(); 
  lastActivityTime = millis(); 
}

void loop() {
  unsigned long currentTime = millis();

 
  if (digitalRead(NEXT_BTN) == LOW) {
    if (isDisplayOff) {
      wakeUpDisplay();
    } else {
      currentIndex++;
      if (currentIndex >= totalImages) currentIndex = 0;
      showImage();
      lastActivityTime = currentTime; 
    }
    delay(300);
  }

 
  if (digitalRead(PREV_BTN) == LOW) {
    if (isDisplayOff) {
      wakeUpDisplay();
    } else {
      currentIndex--;
      if (currentIndex < 0) currentIndex = totalImages - 1;
      showImage();
      lastActivityTime = currentTime; 
    }
    delay(300);
  }

  \
  if (!isDisplayOff && (currentTime - lastActivityTime > screenOffDelay)) {
    digitalWrite(BLK_PIN, LOW);
    isDisplayOff = true;
  }
}


void wakeUpDisplay() {
  digitalWrite(BLK_PIN, HIGH); 
  isDisplayOff = false;
  lastActivityTime = millis();
  showImage();
}

void runStartupAnimation() {
  tft.fillScreen(GC9A01A_BLACK);
  unsigned long startTime = millis();
  float angle = 0;
  uint16_t colors[] = {GC9A01A_RED, GC9A01A_GREEN, GC9A01A_BLUE, GC9A01A_MAGENTA, GC9A01A_YELLOW, GC9A01A_CYAN};
  int colorIdx = 0;

  while (millis() - startTime < 5000) {
    int x = 120 + 50 * cos(angle);
    int y = 120 + 50 * sin(angle);
    tft.fillCircle(x, y, 6, colors[colorIdx]);
    angle += 0.15;
    if (angle > 6.28) {
      angle = 0;
      colorIdx = (colorIdx + 1) % 6;
      tft.fillScreen(GC9A01A_BLACK); 
    }
    tft.setCursor(85, 115);
    tft.setTextColor(GC9A01A_WHITE);
    tft.setTextSize(1);
    tft.print("INITIALIZING...");
    delay(15);
  }
  showImage();
}

void showImage() {
  tft.fillScreen(GC9A01A_BLACK);
  tft.drawRGBBitmap(0, 0, album[currentIndex], 240, 240);
  
  tft.setCursor(110, 220);
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(1);
  tft.print(currentIndex + 1);
  tft.print("/");
  tft.print(totalImages);
}
