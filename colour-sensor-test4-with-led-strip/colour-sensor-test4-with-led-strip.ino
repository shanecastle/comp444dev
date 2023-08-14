#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 9

CRGB leds[NUM_LEDS];

#define redpin 3
#define greenpin 5
#define bluepin 6

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1)
      ;
  }

  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  // Now we're ready to get readings!

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("R:");
  Serial.print(r);
  Serial.print(" G:");
  Serial.print(g);
  Serial.print(" B:");
  Serial.print(b);
  Serial.print(" C:");
  Serial.print(c);
  Serial.print(" - ");

  // test for red
  if (r > 1000 && g < 800 && b < 800 && c < 3100) {
    Serial.println("Detected RED");
    redFadeLeds();
    analogWrite(redpin, 255);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);
  }

  //test for purple
  else if (r > 1000 && g > 800 && b > 900 && c < 5000) {
    Serial.println("Detected PURPLE");
    purpleFadeLeds();
    analogWrite(redpin, 255);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 255);
  }
  /*
  //test for blue
  else if (r b > 900 && c < 2000) {
    Serial.println("Detected BLUE");
    analogWrite(redpin, 0);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 255);
  } */
  
  // test for green
  else if (r < 1000 && g > 800 && b < 900 &&  c < 3100) {
    Serial.println("Detected GREEN");
    greenFadeLeds();
    analogWrite(redpin, 0);
    analogWrite(greenpin, 255);
    analogWrite(bluepin, 0);
    }
    
  else {
    Serial.println("No colour detected.");
    blackFadeLeds();
    analogWrite(redpin, 0);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);
  }
}

void redFadeLeds() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Red;
    FastLED.show();
    //delay(30);
  }
}

void purpleFadeLeds() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Purple;
    FastLED.show();
    delay(30);
  }
}

void greenFadeLeds() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Green;
    FastLED.show();
    delay(30);
  }
}

void blackFadeLeds() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Black;
    FastLED.show();
    delay(30);
  }
}
