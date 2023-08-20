// REX_Laser.ino

#define laserPin 49
#define sensorPin 48

void setupLaser() {
  pinMode(laserPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  turnOnLaser();
}

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
