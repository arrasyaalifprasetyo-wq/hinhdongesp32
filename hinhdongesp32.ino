/*
 * ESP32-C3 SuperMini + OLED 0.96 SSD1306
 * Fixed I2C for C3
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "all_frames.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

// ESP32-C3 SuperMini I2C pins
#define I2C_SDA 8
#define I2C_SCL 9

#define FRAME_DELAY 42   // 24 FPS

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // IMPORTANT for ESP32-C3
  Wire.begin(I2C_SDA, I2C_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    while (true);
  }

  display.clearDisplay();
  display.display();

  Serial.println("OLED OK - Animation Start");
}

void loop() {
  static unsigned long lastFrameTime = 0;
  static int currentFrame = 0;

  unsigned long currentTime = millis();

  if (currentTime - lastFrameTime >= FRAME_DELAY) {
    lastFrameTime = currentTime;

    display.clearDisplay();
    display.drawBitmap(
      0,
      0,
      frames[currentFrame],
      FRAME_WIDTH,
      FRAME_HEIGHT,
      SSD1306_WHITE
    );

    display.display();

    currentFrame++;
    if (currentFrame >= TOTAL_FRAMES) {
      currentFrame = 0;
    }
  }
}