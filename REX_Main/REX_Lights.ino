//REX_Lights.ino - LED lightstrip for REX
// Note: Uses Arduino Giga specific build for NeoPixel library

//#include <Adafruit_NeoPixel.h>
//#define PIN 39
//#define NUMPIXELS 143 // had to cut one pixel

//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//#define DELAYVAL 30

void setupLights(){
  log("[LIGHTS] Lights are deployed to the M4 core");
}

void showLights() {
  logDebug("[LIGHTS] calling RPC function 'showLightsM4'");
  RPC.call("showLightsM4");
}

void loopColor(int r, int g, int b) {
  RPC.call("loopColourM4", r, g, b);
}


/*
void blackAllLeds() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Black;
  }
  FastLED.show();
}

void showAllLeds() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Blue;
  }
  FastLED.show();
}

void showSingleLED(int ledId) {
  leds[ledId] = CRGB::Red;
  FastLED.show();
  delay(2000);
}

void initBlack() {
  // Set the first led back to black for 1 second
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
}

void initBlack2() {
  // Set the first led back to black for 1 second
  leds[0] = CRGB::Black;
  leds[5] = CRGB::Black;

  FastLED.show();
  delay(1000);
}

void runXylon() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
  }

  for (int dot = NUM_LEDS; dot >= 0; dot--) {
    leds[dot] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
  }
}

void runXylon2() {
  Serial.println("--------------------------------------------");
  Serial.println("Xylon2 starting");

  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot - 1] = CRGB::Red;
    leds[dot] = CRGB::Blue;
    leds[dot + 5] = CRGB::Green;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot - 1] = CRGB::Black;
    leds[dot] = CRGB::Black;
    leds[dot + 5] = CRGB::Black;

    delay(30);
  }

  for (int dot = NUM_LEDS; dot >= 6; dot--) {

    leds[dot - 5] = CRGB::Green;
    leds[dot] = CRGB::Blue;
    leds[dot + 1] = CRGB::Red;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot - 5] = CRGB::Black;
    leds[dot] = CRGB::Black;
    leds[dot + 1] = CRGB::Black;
    delay(30);
  }
  Serial.println("Xylon2 done");
}

*/

