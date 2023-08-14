// COMP444 - Circuit 1A - Blink an LED

int delayVal = 150;
void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);  // set pin 13 to output
  pinMode(12, OUTPUT);  // set pin 12 to output
  pinMode(11, OUTPUT);  // set pin 11 to output
  pinMode(10, OUTPUT);  // set pin 10 to output
}

void loop() {
  while (true) {
    for (int i = 14; i >= 9;i--) {
      Serial.println(String("Setting to ON: ") + i );
      digitalWrite(i, HIGH);
      delay(delayVal);
      Serial.println(String("Setting to OFF: ") + i );
      digitalWrite(i, LOW);
    }

    Serial.print("-- Second loop --");
    for (int i = 9; i < 14;i++) {
      Serial.print("Setting " + i + " to ON");
      digitalWrite(i, HIGH);
      delay(delayVal);
      Serial.print("Setting " + i + " to OFF");
      digitalWrite(i, LOW);
    }
  }
}
