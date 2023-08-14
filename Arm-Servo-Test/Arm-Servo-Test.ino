/*
  Super basic servo test
*/
#include <Servo.h>  //include the servo library
Servo servo;        //create a servo object

void setup() {
  Serial.begin(9600);
  Serial.println("-----------------------------------------");
  Serial.println("Servo test");
  servo.attach(9);  // servo in pin 9
}

bool done = false;

int closedRange = 5;
int openRange = 170;

// servo 1 (gripper) limit is 120 to 180 for open/closed
const int OPEN = 120;

// 180 is closed

const int CLOSED = 180;

void loop() {
  for (int i = OPEN; i <= CLOSED; i += 10) {
    Serial.println(i);
    servo.write(i);
    delay(300);
  }

  for (int i = CLOSED; i >= OPEN; i -= 10) {
    Serial.println(i);
    servo.write(i);
    delay(300);
  }
  
  return;

  /*

  if (done) return;

  //for (int i = 0; i < 5; i++) {

    // Note:avoid driving servos all the 0 or 180 degrees it can
    // cause the motor to jitter which is bad for the servo
    for (int x = closedRange; x <= openRange; x += 10) {
      Serial.print("moving to ");
      Serial.println(x);
      servo.write(x);  //move the servo to the 10 degree position
      delay(500);
    }

    Serial.println("test complete");
  //}
    done = true;

    */
}