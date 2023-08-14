/*
  Super basic servo test
*/
#include <Servo.h>  //include the servo library

#define SERVO_COUNT 6

//create a servo object array
Servo servos[SERVO_COUNT];

void setup() {
  Serial.begin(9600);
  Serial.println("-----------------------------------------");
  Serial.println("Servo test");
  servos[0].attach(8);  // servo 1 (gripper) in pin 8
  delay(500);
  servos[1].attach(9);  // servo 2 in pin 9
  delay(500);
  servos[2].attach(10);  // servo 3 in pin 10
  delay(500);
  servos[3].attach(11);
  delay(500);
  servos[4].attach(12);
  delay(500);
  servos[5].attach(13);
}

bool done = false;

void loop() {
  if (done) return;

  for (int currentServo = 0; currentServo < SERVO_COUNT; currentServo++) {
    // Note:avoid driving servos all the 0 or 180 degrees it can
    // cause the motor to jitter which is bad for the servo
    Serial.print("Working on servo number ");
    Serial.println(currentServo);

    servos[currentServo].write(100);
    delay(5000);
  }

  delay(10000);

  Serial.println("test complete");
  done = true;
}
