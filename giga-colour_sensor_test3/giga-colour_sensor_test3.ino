#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <RPC.h>  // to support 2nd CPU core
#include <LiquidCrystal.h>

/* Adafruit TCS34725 */
/* Connect SCL    to analog 5 on UNO (SCL on Giga)
   Connect SDA    to analog 4 on UNO (SDA on Giga)
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
LiquidCrystal lcd(59, 61, 63, 58, 60, 62);


void setup(void) {
  RPC.begin();

  Serial.begin(9600);
  delay(1000);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    // while (1);
  }
}

void loop(void) {
  // Serial.println("in loop");

  uint16_t r, g, b, c, colorTemp, lux;
  float r2, g2, b2;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  tcs.getRGB(&r2, &g2, &b2);

  //Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  //Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  //Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  //Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  //Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  //Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");

  Serial.print("R/G/B (2): ");
  Serial.print(round(r2), DEC);
  Serial.print("/");
  Serial.print(round(g2), DEC);
  Serial.print("/");
  Serial.print(round(b2), DEC);
  Serial.print(" Lux:");
  Serial.print(lux);

  if (lux > 1000) {
    Serial.print(" No block detected");
  } else {
    if (r2 > g2 && r2 > b2) Serial.print("  RED detected");
    if (g2 > r2 && g2 > b2) Serial.print("  GREEN detected");
    if (b2 > r2 && b2 > g2) Serial.print("  BLUE detected");
  }

  Serial.println(" ");

  delay(2000);
}
