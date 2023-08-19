// REX_Display.ino
// Arduino Giga R1 code to display messages on R.E.X. Model 1's LCD display
// COMP444 - Shane Castle #2621506 - August, 2023

#include <LiquidCrystal.h>

int rsPin = 59;      // register select
int enablePin = 61;  // enable
int d4Pin = 63;      // data pins
int d5Pin = 58;
int d6Pin = 60;
int d7Pin = 62;

// Initialize Hitachi HD44780 LCD Display
LiquidCrystal lcd(rsPin, enablePin, d4Pin, d5Pin, d6Pin, d7Pin);

void setupDisplay() {
  // initialize 16x2 display
  lcd.begin(16, 2);
  lcd.clear();
}

void showMessage(String message) {
  showMessage(0, 0, message);
}

// display a message on the 16x2 LCD screen
// column and row are zero indexed
// eg: 0,0 = top left of first row
//    15,0 = top right of first row
//     0,1 = bottom left of second row
//    15,1 = bottom right of second row
void showMessage(int column, int row, String message) {
  lcd.setCursor(column, row);
  lcd.print(message);
}

void clearDisplay() {
  lcd.clear();
}

void scrollDisplayLeft(int positions) {
  // scroll to the left to move message offscreen
  for (int positionCounter = 0; positionCounter < positions; positionCounter++) {
    lcd.scrollDisplayLeft();  // scroll one position left
    delay(150);               // wait a bit
  }
}
