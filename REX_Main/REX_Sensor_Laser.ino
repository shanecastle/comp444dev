// REX_Laser.ino

#define laserPin 48
#define sensorPin 49

void setupLaser() {
  pinMode(laserPin, OUTPUT);
  pinMode(sensorPin, INPUT);}

void turnOnLaser() {
  digitalWrite(laserPin, HIGH);
}

void turnOffLaser() {
  digitalWrite(laserPin, LOW);
}

void detectBeam() {
  bool value = digitalRead(sensorPin);
  logDebug("[LASER] sensor: " + String(value));

  if (value == 0) {
    logDebug("[LASER] Tripped!");

  } else {
    logDebug("[LASER] Beam not blocked");
  }
}
