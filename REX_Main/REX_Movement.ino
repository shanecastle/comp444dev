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
const int driver1motor1in1 = 52;
const int driver1motor1in2 = 53;
const int driver1motor2in3 = 50;
const int driver1motor2in4 = 51;
const int driver2motor3in1 = 25;
const int driver2motor3in2 = 24;
const int driver2motor4in3 = 23;
const int driver2motor4in4 = 22;

const int greenButtonPin = 64;  // start motors
const int redButtonPin = 65;    // stop motors
int speed = 0;            // motor speed (0 to 255)
int potentiometer = A0;   // motor speed adust

volatile byte runMotors = 0;  // disable movement by default

void setupMovement() {
  logDebug("[MOVE] Setting up motor button pins and interrupts");
  pinMode(redButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(redButtonPin), disableMotors, CHANGE);
  pinMode(greenButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(greenButtonPin), enableMotors, CHANGE);

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

  // Turn off motors - Initial state
  stopAllMotors();

  potentiometer = analogRead(A0);
  speed = map(potentiometer, 0, 1023, 0, 255);
  setAllMotorSpeed(speed);
}

// set the run flag to false and stop the motors
void disableMotors() {
 // logDebug("[MOVE] Disabling motors");
  runMotors = 0;
 // stopAllMotors();
}

// enable the run flag
void enableMotors() {
 // logDebug("[MOVE] Enabling motors");
  runMotors = 1;
}

void motorTest() {
  if (runMotors == 1) {
    // test motors
    setAllMotorSpeed(100);
    moveForward();
    delay(1000);
    moveLeft();
    delay(1000);

    stopAllMotors();
    runMotors = false;
  }
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

  digitalWrite(driver1motor1in1, HIGH);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, HIGH);
  digitalWrite(driver1motor2in4, LOW);
  digitalWrite(driver2motor3in1, HIGH);
  digitalWrite(driver2motor3in2, LOW);
  digitalWrite(driver2motor4in3, HIGH);
  digitalWrite(driver2motor4in4, LOW);
}

void moveLeft() {
  logDebug("[MOVE] Moving left");
  if (runMotors == 0) { 
    logDebug("[MOVE] Motors disabled.");
    return;
  }

  digitalWrite(driver1motor1in1, HIGH);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, HIGH);
  digitalWrite(driver1motor2in4, LOW);
  digitalWrite(driver2motor3in1, HIGH);
  digitalWrite(driver2motor3in2, LOW);
  digitalWrite(driver2motor4in3, HIGH);
  digitalWrite(driver2motor4in4, LOW);
}

void strafeRight() {
  logDebug("[MOVE] Strafe right");
  if (runMotors == 0) { 
    logDebug("[MOVE] Motors disabled.");
    return;
  }

  //strafeRight	FORWARD	REVERSE	REVERSE	FORWARD
  digitalWrite(driver1motor1in1, HIGH);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver2motor3in1, LOW);
  digitalWrite(driver2motor3in2, HIGH);

  digitalWrite(driver1motor2in3, LOW);
  digitalWrite(driver1motor2in4, HIGH);
  digitalWrite(driver2motor4in3, HIGH);
  digitalWrite(driver2motor4in4, LOW);
}

void strafeLeft() {
  logDebug("[MOVE] Strafe left");
  if (runMotors == 0) return;

  //strafeLeft REVERSE	FORWARD	FORWARD	REVERSE
  digitalWrite(driver1motor1in1, LOW);
  digitalWrite(driver1motor1in2, HIGH);
  digitalWrite(driver2motor3in1, HIGH);
  digitalWrite(driver2motor3in2, LOW);

  digitalWrite(driver1motor2in3, HIGH);
  digitalWrite(driver1motor2in4, LOW);
  digitalWrite(driver2motor4in3, LOW);
  digitalWrite(driver2motor4in4, HIGH);
}

void stopAllMotors() {
  logDebug("[MOVE] Stopping all motors.");
  digitalWrite(driver1motor1in1, LOW);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, LOW);
  digitalWrite(driver1motor2in4, LOW);
  digitalWrite(driver2motor3in1, LOW);
  digitalWrite(driver2motor3in2, LOW);
  digitalWrite(driver2motor4in3, LOW);
  digitalWrite(driver2motor4in4, LOW);
}
