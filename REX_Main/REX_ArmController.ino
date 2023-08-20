//REX_ArmController.ino
// Controls 6DOF robotic arm on Rex

#include <Servo.h>  //include the servo library
Servo servo1;       //create a servo object
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int buttonPin = 57;

const int servo1Pin = 40;
const int servo2Pin = 41;
const int servo3Pin = 42;
const int servo4Pin = 43;
const int servo5Pin = 44;
const int servo6Pin = 45;

void testRobotArm() {

  Serial.println("Servo test. Press Blue");

  pinMode(buttonPin, INPUT_PULLUP);

  // wait until the button is pressed
  // while (digitalRead(buttonPin) == HIGH) {
  //}

  Serial.println("Servo 5 to 1500us");
  //servo5.write(15);  // degs
  servo5.attach(servo5Pin);
  //servo5.write(15);  // degs
  servo5.writeMicroseconds(1500);
  delay(500);

  //return;

  //servo5.write(15);  // degs
  // delay(500);
  // servo5.write(90);  // degs

  // wait until the button is pressed
  // while (digitalRead(buttonPin) == HIGH) {
  //}

  Serial.println("Servo 4 to 90 deg");
  //servo4.write(90);  // degs
  servo4.attach(servo4Pin);
  //servo4.write(90);
  servo4.writeMicroseconds(1500);
  delay(500);


  /*
  for (int i = 90; i >= 0; i -= 5) {
    servo4.write(i);
    delay(100);
  }

  for (int i = 15; i <= 90; i += 5) {
    servo5.write(i);
    delay(100);
  }

  for (int i = 0; i <= 90; i += 5) {
    servo4.write(i);
    delay(100);
  }
*/

  servo3.attach(servo3Pin);        // pin
  servo3.writeMicroseconds(1000);  // degs
  delay(2000);

  servo3.writeMicroseconds(1500);
  delay(500);
  servo3.writeMicroseconds(2000);
  delay(2000);

  servo2.attach(servo2Pin);
  servo2.writeMicroseconds(1500);
  delay(2000);

  servo1.attach(servo1Pin);
  servo1.writeMicroseconds(1500);
  delay(2000);

  servo6.attach(servo6Pin);
  servo6.writeMicroseconds(1500);
  delay(500);
  servo6.writeMicroseconds(2000);
  delay(500);
  servo6.writeMicroseconds(1000);
  delay(500);


  /*
  for (int i = 0; i <= 90; i += 5) {
    servo3.write(i);
    delay(100);
  }

  servo1.write(120);
  servo1.attach(servo1Pin);

  for (int i = 120; i <= 180; i += 5) {
    servo1.write(i);
    delay(100);
  }


  //------------------------------------------------------------------
  Serial.println("Starting Shutdown routine.");
  for (int i = 90; i >= 0; i -= 5) {
    servo3.write(i);
    delay(100);
  }
  for (int i = 90; i <= 180; i += 5) {
    servo4.write(i);
    delay(100);
  }
  */
}

//==========================================================================================
