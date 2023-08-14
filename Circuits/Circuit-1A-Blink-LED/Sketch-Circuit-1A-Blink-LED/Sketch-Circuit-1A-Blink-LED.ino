// COMP444 - Circuit 1A - Blink an LED

void setup() {
  pinMode(13, OUTPUT); // set pin 13 to output
  pinMode(12, OUTPUT); // set pin 12 to output
  pinMode(11, OUTPUT); // set pin 11 to output
  pinMode(10, OUTPUT); // set pin 10 to output
}

void loop() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}
