void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("-----------------------------------------");
  Serial.println("Servo test");

#define SERVO_COUNT 6
  Servo servos[SERVO_COUNT];

  // attach the servos to digital pins. 
  // 1 based instead of 0 to simplify things
  // servo 1 is in digital pin 1
  for (int i = 1; i <= SERVO_COUNT; i++) {
    servos[i].attach(i);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
