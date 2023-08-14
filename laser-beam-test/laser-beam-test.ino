#define sensor 8
#define LED 12

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  bool value = digitalRead(sensor);
  Serial.print("sensor: ");
  Serial.println(value);

  digitalWrite(LED, HIGH);
 // return;


  if (value == 0) {
    digitalWrite(LED, HIGH);
    Serial.println("Tripped!");

  } else {
    digitalWrite(LED, LOW);
    Serial.println("Beam not blocked");
  }

 // delay(2000);
}
