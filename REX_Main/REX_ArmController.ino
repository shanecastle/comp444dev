//REX_ArmController.ino
// Controls 6DOF robotic arm on Rex

#include <Servo.h>  //include the servo library
Servo servo1;       //create a servo object
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int blueButtonPin = 57;

const int servo1Pin = 40;
const int servo2Pin = 41;
const int servo3Pin = 42;
const int servo4Pin = 43;
const int servo5Pin = 44;
const int servo6Pin = 45;

void setupArmController() {
  pinMode(blueButtonPin, INPUT_PULLUP);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
  servo6.attach(servo6Pin);
}

void testRobotArm() {
  log("[ARM] Servo test. Press Blue");
  showMessage(0, 1, "Press Blue");


  // wait until the blue button is pressed
  while (digitalRead(blueButtonPin) == HIGH) {
  }

  loopColour(0,0,150);

  //playSoundFile("activatearm.wav");

  //servo3test();

  //fullRangeTest();
  pickupBlock();
  playSoundFile("DRUM.wav");
  delay(5000);
  // moveToRestPosition();
}

void servo3test() {
  //  moveServo(5, 1500, false, 500);
  //  moveServo(4, 1100, false, 500);

  for (int i = 500; i < 2500; i += 100) {
    moveServo(3, i, true, 100);
  }
}

void servo2test() {
  for (int i = 500; i < 2500; i += 200) {
    moveServo(2, i, true, 50);
  }
}


void pickupBlock() {

  //playSoundFile("activatearm.wav");
  moveServo(5, 1500, true, 100);
  moveServo(4, 1100, true, 100);
  moveServo(1, 1200, true, 100);  // open
  moveServo(5, 1200, true, 100);
  moveServo(6, 2100, true, 100);
  moveServo(2, 2100, true, 100);
  moveServo(3, 2100, true, 100);
  //moveServo(5, 1400, true, 100);

  playSoundFile("servo4.wav");
  playSoundFile("moving.wav");
  playSoundFile("/numbers/600.wav");
  for (int i = 1100; i > 600; i -= 10) {
    moveServo(4, i, false, 50);
  }

  /*
  playSoundFile("servo3.wav");
  playSoundFile("moving.wav");
  playSoundFile("/numbers/600.wav");
  for (int i = 2100; i > 1900; i -= 10) {
    moveServo(3, i, false, 50);
  }
*/

  /*
  playSoundFile("servo4.wav");
  playSoundFile("moving.wav");
  playSoundFile("/numbers/600.wav");
  for (int i = 800; i > 600; i -= 10) {
    moveServo(4, i, false, 50);
  }
*/

  //moveServo(1, 2500, true, 500);  // closed

  // close gripper
  playSoundFile("servo1.wav");
  playSoundFile("moving.wav");
  playSoundFile("/numbers/2500.wav");
  for (int i = 1200; i < 2500; i += 10) {
    moveServo(1, i, false, 100);
  }


  playSoundFile("servo4.wav");
  playSoundFile("moving.wav");
  playSoundFile("/numbers/2500.wav");
  for (int i = 500; i < 1500; i += 10) {
    moveServo(4, i, false, 50);
  }
}

void moveToRestPosition() {
  playSoundFile("moving.wav");
  playSoundFile("/numbers/0.wav");

  moveServo(1, 2300, false, 500);  // closed
  moveServo(4, 1500, false, 500);
  moveServo(3, 1000, false, 500);

  moveServo(6, 1500, false, 500);
  moveServo(5, 1500, false, 500);
  moveServo(4, 700, false, 500);
}

void fullRangeTest() {
  moveServo(5, 1500);
  moveServo(4, 1500);
  moveServo(3, 1500);

  moveServo(5, 1000);
  moveServo(5, 1500);
  moveServo(5, 2000);

  moveServo(4, 1000);
  moveServo(4, 1500);
  moveServo(4, 2000);

  moveServo(6, 1000);
  moveServo(6, 1500);
  moveServo(6, 2000);

  moveServo(3, 1000);
  moveServo(3, 1500);
  moveServo(3, 2000);

  moveServo(2, 1000);
  moveServo(2, 1500);
  moveServo(2, 2000);

  moveServo(1, 1500);  // fully open
  moveServo(1, 2000);  // closed
}


void moveServo(int id, int microseconds) {
  moveServo(id, microseconds, true, 500);
}

void moveServo2(int id, int microseconds, bool announce, int delayMilliseconds) {
  logDebug("[ARM] Servo " + String(id) + " to " + String(microseconds) + "us");

  if (announce) {
    String servoFile = "servo" + String(id) + ".wav";
    playSoundFile(servoFile.c_str());
    playSoundFile("moving.wav");
    String numberFile = "/numbers/" + String(microseconds) + ".wav";
    playSoundFile(numberFile.c_str());
  }

  switch (id) {
    case 1:
      servo1.writeMicroseconds(microseconds);
      break;
    case 2:
      servo2.writeMicroseconds(microseconds);
      break;
    case 3:
      servo3.writeMicroseconds(microseconds);
      break;
    case 4:
      servo4.writeMicroseconds(microseconds);
      break;
    case 5:
      servo5.writeMicroseconds(microseconds);
      break;
    case 6:
      servo6.writeMicroseconds(microseconds);
      break;
  }

  delay(delayMilliseconds);
}

//move a servo to a position (microsecond range: 1000 to 2000. 1500 is midpoint)
// docs: https://www.arduino.cc/reference/en/libraries/servo/writemicroseconds/
void moveServo(int id, int microseconds, bool announce, int delayMilliseconds) {
  logDebug("[ARM] Servo " + String(id) + " to " + String(microseconds) + "us");

  if (announce) {
    String servoFile = "servo" + String(id) + ".wav";
    playSoundFile(servoFile.c_str());
    playSoundFile("moving.wav");
    String numberFile = "/numbers/" + String(microseconds) + ".wav";
    playSoundFile(numberFile.c_str());
  }

  switch (id) {
    case 1:
      servo1.writeMicroseconds(microseconds);
      break;
    case 2:
      servo2.writeMicroseconds(microseconds);
      break;
    case 3:
      servo3.writeMicroseconds(microseconds);
      break;
    case 4:
      servo4.writeMicroseconds(microseconds);
      break;
    case 5:
      servo5.writeMicroseconds(microseconds);
      break;
    case 6:
      servo6.writeMicroseconds(microseconds);
      break;
  }

  delay(delayMilliseconds);
}
