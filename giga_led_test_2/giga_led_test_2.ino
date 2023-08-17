#include <Adafruit_NeoPixel.h>
#define PIN 49
#define NUMPIXELS 144

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 30

void setup() {
  pixels.begin();
}

void loop() {
  pixels.clear();

  loopColor(150, 0, 0);
  loopColor(0, 150, 0);
  loopColor(0, 0, 150);
}

void loopColor(int r, int g, int b) {
  for (int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
    delay(DELAYVAL);
  }
}