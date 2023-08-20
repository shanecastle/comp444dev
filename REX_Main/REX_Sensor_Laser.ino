// REX_Laser.ino

#define laserPin 48
#define sensorPin 49

void setupLaser() {
  pinMode(laserPin, OUTPUT);
  pinMode(sensorPin, INPUT);}

void turnOnLaser() {
  digitalWrite(LaserPin, HIGH);
}

void turnOffLaser() {
  digitalWrite(LaserPin, LOW);
}

void detectBeam() {
  bool value = digitalRead(sensorPin);
  Serial.print("sensor: ");
  Serial.println(value);

  if (value == 0) {
    digitalWrite(LED, HIGH);
    Serial.println("Tripped!");

  } else {
    digitalWrite(LED, LOW);
    Serial.println("Beam not blocked");
  }
}
