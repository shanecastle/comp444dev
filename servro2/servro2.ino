/*
  Super basic servo test
*/
#include <Servo.h>  //include the servo library
Servo servo;        //create a servo object

void setup() {
  Serial.begin(9600);
  servo.attach(9);  // servo in pin 9

  Serial.println("-----------------------------------------");
  Serial.println("Enter degree to move to (0 to 180)");
}

int moveToDegree = 0;

void loop() {

  while (Serial.available() == 0) {
  }

  moveToDegree = Serial.readStringUntil('\n').toInt();
  Serial.print("Input: ");
  Serial.println(moveToDegree);

  if (moveToDegree < 0 || moveToDegree > 180) {
    Serial.print("Input out of range (0 to 180). Input: ");
    Serial.println(moveToDegree);
    return;
  }

  Serial.print("Moving to ");
  Serial.println(moveToDegree);
  servo.write(moveToDegree);
  delay(1000);

  Serial.println("-----------------------------------------");
  Serial.println("Enter degree to move to (0 to 180)");
  //}
}