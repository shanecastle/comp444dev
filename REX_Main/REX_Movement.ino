// REX_Movement.ino
// Arduino Giga R1 code to control DC motors on R.E.X. Model 1
// COMP444 - Shane Castle #2621506 - August, 2023

// DC motor wiring (model 37GB-520-30F):
//           (PWM)               Encoder
//           speed   direction   A    B
// Motor 1 =   2     52,53       00   00
// Motor 2 =   3     50,51       00   00
// Motor 3 =   4     25,24       00   00
// Motor 4 =   5     23,22       00   00

// Motor Driver speed control (model L298N)
const int driver1motor1enA = 2;  // Speed control for motor 1
const int driver1motor2enB = 3;
const int driver2motor3enA = 4;  // Speed control for motor 3
const int driver2motor4enB = 5;

// Motor Driver direction control (model L298N)
const int driver1motor1in1 = 52;  // REAR_RIGHT
const int driver1motor1in2 = 53;

const int driver1motor2in3 = 50;  // REAR_LEFT
const int driver1motor2in4 = 51;

const int driver2motor3in1 = 25;  // FRONT_RIGHT
const int driver2motor3in2 = 24;

const int driver2motor4in3 = 23;  // FRONT_LEFT
const int driver2motor4in4 = 22;

// Motor control constants
const int REAR_RIGHT = 0;
const int REAR_LEFT = 1;
const int FRONT_RIGHT = 2;
const int FRONT_LEFT = 3;
const int FORWARD = 0;
const int REVERSE = 1;
const int STOP = 2;

const int greenButtonPin = 64;  // start motors
const int redButtonPin = 65;    // stop motors
int speed = 0;                  // motor speed (0 to 255)
int potentiometer = A0;         // motor speed adust

volatile byte runMotors = 0;  // disable movement by default

void setupMovement() {
  logDebug("[MOVE] Setting up motor button pins and interrupts");
  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);

  // assign the motor driver pins for all four motors
  setMotorPins();

  // Turn off motors - Initial state
  stopAllMotors();

  // set the initial motor speed to current potentiometer value
  potentiometer = analogRead(A0);
  speed = map(potentiometer, 0, 1023, 0, 255);
  setAllMotorSpeed(speed);
}

void setMotorPins() {
  // Set motor speed control pins outputs
  pinMode(driver1motor1enA, OUTPUT);
  pinMode(driver1motor2enB, OUTPUT);
  pinMode(driver2motor3enA, OUTPUT);
  pinMode(driver2motor4enB, OUTPUT);

  // Set the motor direction control
  pinMode(driver1motor1in1, OUTPUT);
  pinMode(driver1motor1in2, OUTPUT);
  pinMode(driver1motor2in3, OUTPUT);
  pinMode(driver1motor2in4, OUTPUT);
  pinMode(driver2motor3in1, OUTPUT);
  pinMode(driver2motor3in2, OUTPUT);
  pinMode(driver2motor4in3, OUTPUT);
  pinMode(driver2motor4in4, OUTPUT);
}

// set the run flag to false and stop the motors
void disableMotors() {
  // logDebug("[MOVE] Disabling motors");
  runMotors = 0;
  // stopAllMotors();
}

void checkMotorButtons() {
  if (digitalRead(redButtonPin) == LOW) {
    logDebug("[MOVE] Setting runMotors to 0");
    runMotors = false;
    stopAllMotors();
  } else if (digitalRead(greenButtonPin) == LOW) {
    logDebug("[MOVE] Setting runMotors to 1");
    runMotors = 1;
  }
}

// enable the run flag
void enableMotors() {
  logDebug("[MOVE] Enabling motors");
  runMotors = 1;
}

void motorTest() {
  if (runMotors != 1) return;
  logDebug("[MOVE] Starting motor test");

  // speak using the REX_Sound methods
  logDebug("[MOVE] Calling play sound");
  playSoundFile("startmotortest.wav");

  // test motors
  setAllMotorSpeed(100);

  //                "0123456789012345"
  //showMessage(0, 2, "Test each motor");
  //delay(300);
  //stopAllMotors();
  //testMotor(FRONT_LEFT);
  //testMotor(FRONT_RIGHT);
  //testMotor(REAR_LEFT);
  //testMotor(REAR_RIGHT);

  //                "0123456789012345"
  showMessage(0, 2, "Move FORWARD    ");
  playSoundFile("moveforward.wav");
  moveForward();
  delay(2000);
  stopAllMotors();
  delay(1000);


  //                "0123456789012345"
  showMessage(0, 2, "Move REVERSE    ");
  playSoundFile("movereverse.wav");
  moveReverse();
  delay(2000);
  stopAllMotors();
  delay(1000);

  //                "0123456789012345"
  showMessage(0, 2, "Move ROTATE LEFT");
  playSoundFile("moveleft.wav");
  rotateLeft();
  delay(2000);
  stopAllMotors();
  delay(1000);

  //                "0123456789012345"
  /*showMessage(0, 2, "Move STRAFE LEFT");
  strafeLeft();
  delay(1000);
  stopAllMotors();
  delay(1000);
*/
  //                "0123456789012345"
  playSoundFile("endmotortest.wav");
  showMessage(0, 2, " Test Complete  ");
  playSoundFile("SHAKE.wav");
  runMotors = false;
}

void testMotor(int motorId) {
  logDebug("[MOVE] Testing motor " + String(motorId));
  //                "0123456789012345"
  showMessage(0, 2, "Testing motor " + String(motorId));
  setMotor(motorId, FORWARD);
  delay(1500);
  setMotor(motorId, STOP);
  delay(500);
  setMotor(motorId, REVERSE);
  delay(1500);
  setMotor(motorId, STOP);
  delay(500);
}

void setAllMotorSpeed(int newSpeed) {
  // For PWM maximum possible values are 0 to 255
  if (newSpeed < 0 || newSpeed > 255) {
    return;
  }
  analogWrite(driver1motor1enA, newSpeed);
  analogWrite(driver1motor2enB, newSpeed);
  analogWrite(driver2motor3enA, newSpeed);
  analogWrite(driver2motor4enB, newSpeed);
}

void moveForward() {
  logDebug("[MOVE] Moving forward");
  if (runMotors == 0) {
    logDebug("[MOVE] Motors disabled.");
    return;
  }

  setMotor(FRONT_LEFT, FORWARD);
  setMotor(FRONT_RIGHT, FORWARD);
  setMotor(REAR_LEFT, FORWARD);
  setMotor(REAR_RIGHT, FORWARD);
}

void moveReverse() {
  logDebug("[MOVE] Moving reverse");
  if (runMotors == 0) {
    logDebug("[MOVE] Motors disabled.");
    return;
  }

  setMotor(FRONT_LEFT, REVERSE);
  setMotor(FRONT_RIGHT, REVERSE);
  setMotor(REAR_LEFT, REVERSE);
  setMotor(REAR_RIGHT, REVERSE);
}

void rotateLeft() {
  logDebug("[MOVE] Rotating left");
  if (runMotors == 0) {
    logDebug("[MOVE] Motors disabled.");
    return;
  }

  setMotor(FRONT_LEFT, FORWARD);
  setMotor(FRONT_RIGHT, FORWARD);
  setMotor(REAR_LEFT, REVERSE);
  setMotor(REAR_RIGHT, REVERSE);
}

void strafeLeft() {
  logDebug("[MOVE] Strafe Left");
  if (runMotors == 0) {
    logDebug("[MOVE] Motors disabled.");
    return;
  }

  setMotor(FRONT_LEFT, REVERSE);
  setMotor(FRONT_RIGHT, FORWARD);
  setMotor(REAR_LEFT, FORWARD);
  setMotor(REAR_RIGHT, REVERSE);
}

void strafeRight() {
  logDebug("[MOVE] Strafe right");
  if (runMotors == 0) {
    logDebug("[MOVE] Motors disabled.");
    return;
  }
}

void stopAllMotors() {
  logDebug("[MOVE] Stopping all motors.");
  setMotor(FRONT_LEFT, STOP);
  setMotor(FRONT_RIGHT, STOP);
  setMotor(REAR_LEFT, STOP);
  setMotor(REAR_RIGHT, STOP);
}

// start a motor in a given direction
// id =   FRONT_LEFT = 0
//        FRONT_RIGHT = 1
//        REAR_LEFT = 3
//        REAR_RIGHT = 4
// direction = FORWARD = 0
//             REVERSE = 1
//             STOP = 2
void setMotor(int motorId, int direction) {
  int in1 = -1;
  int in2 = -1;
  switch (motorId) {
    case REAR_RIGHT:
      in1 = driver1motor1in1;
      in2 = driver1motor1in2;
      break;
    case REAR_LEFT:
      in1 = driver1motor2in3;
      in2 = driver1motor2in4;
      break;
    case FRONT_RIGHT:
      in1 = driver2motor3in1;
      in2 = driver2motor3in2;
      break;
    case FRONT_LEFT:
      in1 = driver2motor4in3;
      in2 = driver2motor4in4;
      break;
  }

  switch (direction) {
    case FORWARD:
      logDebug("[MOVE] Setting Motor " + String(motorId) + " forward");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      break;
    case REVERSE:
      logDebug("[MOVE] Setting Motor " + String(motorId) + " reverse");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      break;
    case STOP:
      logDebug("[MOVE] Setting Motor " + String(motorId) + " stop");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      break;
  }
}
