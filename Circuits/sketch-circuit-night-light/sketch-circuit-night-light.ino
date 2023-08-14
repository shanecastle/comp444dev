// night-light
int photoresistor = 0;
int threshold = 750;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

int count = 0;
void loop() {
  photoresistor = analogRead(A0);
  if (count++ % 20 == 0) {
    Serial.println(photoresistor);
  } else {
    Serial.print(String(photoresistor) + " - ");
  }
  if (photoresistor < threshold) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(100);
}
