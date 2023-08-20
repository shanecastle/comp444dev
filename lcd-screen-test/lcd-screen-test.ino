// Simple LCD screen test

#include <RPC.h> // to support 2nd CPU core
#include <LiquidCrystal.h>  

LiquidCrystal lcd(59, 61, 63, 58, 60, 62);

void setup() {
  RPC.begin();

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("8888888888888888");
  lcd.setCursor(0, 1);
  lcd.print("8888888888888888");
}

void loop() {
  String buffer = "";
  while (RPC.available()) {
    buffer += (char)RPC.read();  // Fill the buffer with characters
  }
  if (buffer.length() > 0) {
    Serial.print(buffer);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(buffer);
  }

}
