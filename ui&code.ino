#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <SPI.h>
#include <math.h>
#include "image_data.h"

// Pin අර්ථ දැක්වීම්
#define TFT_CS   7  
#define TFT_DC   5  
#define TFT_RST  4
#define BLK_PIN  6   // Backlight control (PWM)
#define NEXT_BTN 15
#define PREV_BTN 14 

Adafruit_GC9A01A tft = Adafruit_GC9A01A(TFT_CS, TFT_DC, TFT_RST);

int currentIndex = 0;
const int totalImages = 6; 
const uint16_t* album[] = {image1, image2, image3, image4, image5, image6};

// Timer variables
unsigned long lastActivityTime = 0;
const unsigned long dimDelay = 120000; // විනාඩි 2 (120,000 milliseconds)
bool isDimmed = false;

void setup() {
  SPI.setSCK(2);
  SPI.setTX(3);
  
  pinMode(NEXT_BTN, INPUT_PULLUP);
  pinMode(PREV_BTN, INPUT_PULLUP);
  pinMode(BLK_PIN, OUTPUT);
  
  analogWrite(BLK_PIN, 255); // ආරම්භයේදී උපරිම දීප්තිය

  tft.begin(24000000); 
  tft.setRotation(0);
  
  runStartupAnimation(); 
  lastActivityTime = millis(); // කාලය මැනීම ආරම්භ කරන්න
}

void loop() {
  unsigned long currentTime = millis();

  // --- NEXT BUTTON ---
  if (digitalRead(NEXT_BTN) == LOW) {
    resetDimming(); // Button එක එබූ නිසා දීප්තිය වැඩි කරන්න
    currentIndex++;
    if (currentIndex >= totalImages) currentIndex = 0;
    showImage();
    delay(300);
  }

  // --- PREVIOUS BUTTON ---
  if (digitalRead(PREV_BTN) == LOW) {
    resetDimming(); // Button එක එබූ නිසා දීප්තිය වැඩි කරන්න
    currentIndex--;
    if (currentIndex < 0) currentIndex = totalImages - 1;
    showImage();
    delay(300);
  }

  // --- AUTO DIM LOGIC (විනාඩි 2ක් පසුව) ---
  if (!isDimmed && (currentTime - lastActivityTime > dimDelay)) {
    analogWrite(BLK_PIN, 20); // දීප්තිය ගොඩක් අඩු කරන්න (20/255)
    isDimmed = true;
  }
}

// දීප්තිය නැවත වැඩි කරන Function එක
void resetDimming() {
  analogWrite(BLK_PIN, 255); 
  lastActivityTime = millis(); // කාලය අලුතින් මැනීම අරඹන්න
  isDimmed = false;
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
