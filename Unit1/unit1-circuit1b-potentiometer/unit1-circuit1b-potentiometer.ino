int potPosition;
float voltage;
int previousPos;

void setup() {
  Serial.begin(9600);  // connect to computer
  pinMode(13, OUTPUT);
}

void loop() {
  potPosition = analogRead(A0);
  voltage = potPosition * (5.0 / 1023.0);
  if (potPosition != previousPos) {
    Serial.println("Position: [" + String(potPosition) + "], Voltage: [" + String(voltage) +"]");
    previousPos = potPosition;
  }
  digitalWrite(13, HIGH);
  delay(potPosition);
  digitalWrite(13, LOW);
  delay(potPosition);
}
