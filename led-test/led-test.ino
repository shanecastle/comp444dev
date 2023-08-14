int pinNum = 12;

void setup() {

  pinMode(pinNum, OUTPUT);  // Set pin 13 to output
}

void loop() {
  digitalWrite(pinNum, HIGH);  // Turn on the LED
  delay(2000);                 // Wait for two seconds
  digitalWrite(pinNum, LOW);   // Turn off the LED
  delay(2000);                 // Wait for two seconds
}
