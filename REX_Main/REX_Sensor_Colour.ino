#include "Wire.h"
#include "Adafruit_TCS34725.h"
#include "LiquidCrystal.h"

/* Adafruit TCS34725 */
/* Connect SCL    to analog 5 on UNO (SCL on Giga)
   Connect SDA    to analog 4 on UNO (SDA on Giga)
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);


void setupColourSensor() {
  if (tcs.begin()) {
    log("[COLOUR] Found sensor");
  } else {
    log("[COLOUR] ERROR - No TCS34725 found");
  }
}

void detectColour() {
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

  Serial.println("R/G/B (2): "
                 + String(round(r2))
                 + "/" + String(round(g2))
                 + "/" + String(round(b2))
                 + " Lux:" + String(lux));

  if (lux > 1000) {
    logDebug("[COLOUR] No block detected");
    showMessage(0, 1, "  No Block   ");
  } else {
    if (r2 > g2 && r2 > b2) {
      logDebug("[COLOUR] RED detected");
      showMessage(0, 1, "RED Block");
      playSoundFile("redblock.wav");
    }

    if (g2 > r2 && g2 > b2) {
      logDebug("[COLOUR] GREEN detected");
      showMessage(0, 1, "GREEN Block");
      playSoundFile("greenblock.wav");
    }
    if (b2 > r2 && b2 > g2) {
      logDebug("[COLOUR] BLUE detected");
      showMessage(0, 1, "BLUE Block");
      playSoundFile("blueblock.wav");
    }
  }
}
