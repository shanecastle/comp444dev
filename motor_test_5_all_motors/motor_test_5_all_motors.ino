
// Motor driver test

#include <RPC.h>  // to boot the 2nd core

//wiring:
//           (PWM)               Encoder
//           speed   direction   A    B
// Motor 1 =   2     52,53       00   00
// Motor 2 =   3     50,51       00   00
// Motor 3 =   4     25,24       00   00
// Motor 4 =   5     23,22       00   00

// L298N Motor Driver speed  control
int driver1motor1enA = 2;  // Speed control for motor 1
int driver1motor2enB = 3;
int driver2motor3enA = 4;  // Speed control for motor 3
int driver2motor4enB = 5;

// L298N Motor Driver 2 encoder
int driver1motor1in1 = 52;  // Direction control for Motor 1
int driver1motor1in2 = 53;  // Direction control for Motor 1
int driver1motor2in3 = 50;
int driver1motor2in4 = 51;
int driver2motor3in1 = 25;  // Direction control for Motor 3
int driver2motor3in2 = 24;  // Direction control for Motor 3
int driver2motor4in3 = 23;
int driver2motor4in4 = 22;

int potentiometer = A0;
int speed = 0;


#define M1_ENCODER_A 2  //  Motor 1 Encoder A
#define M1_ENCODER_B 3  //  Motor 1 Encoder B

#define M2_ENCODER_A 7  //  Motor 2 Encoder A
#define M2_ENCODER_B 8  //  Motor 2 Encoder B


// setup start/stop buttons
int redButtonPin = 65;
int greenButtonPin = 64;

bool runWheels = false;

void setup() {
  RPC.begin();


  // Serial.begin(9600);
  // Serial.write("Staring motor test");

  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);

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
  digitalWrite(driver1motor1in1, LOW);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, LOW);
  digitalWrite(driver1motor2in4, LOW);
  digitalWrite(driver2motor3in1, LOW);
  digitalWrite(driver2motor3in2, LOW);
  digitalWrite(driver2motor4in3, LOW);
  digitalWrite(driver2motor4in4, LOW);


  // set encoder pins
  //  pinMode(M1_ENCODER_A, INPUT);
  // pinMode(M1_ENCODER_B, INPUT);

  //  pinMode(M2_ENCODER_A, INPUT);
  // pinMode(M2_ENCODER_B, INPUT);
}

void loop() {

  if (digitalRead(redButtonPin) == LOW) {
    runWheels = false;
    stopAllWheels();
  } else if (digitalRead(greenButtonPin) == LOW) {
    runWheels = true;
  }

  if (runWheels == false) return;

  potentiometer = analogRead(A0);
  speed = potentiometer / 4; // potentiometer returns 0 to 1023

  setAllMotorSpeed(speed);

  // run all wheels
  moveForward();
  return;

  //moveLeft();

  strafeRight();
  delay(2500);
  stopAllWheels();

  runWheels = false;

  // speedControl();
  //delay(1000);


  // directionControl();

  // int a = digitalRead(M1_ENCODER_A);
  // int b = digitalRead(M1_ENCODER_B);
  // Serial.print(a * 5);
  //  Serial.print(" ");
  // Serial.print(b * 5);
  //  Serial.println();
  //delay(1000);
}

void setAllMotorSpeed(int speed) {
  // For PWM maximum possible values are 0 to 255
  if (speed < 0 || speed > 255) {
    return;
  }
  analogWrite(driver1motor1enA, speed);
  analogWrite(driver1motor2enB, speed);
  analogWrite(driver2motor3enA, speed);
  analogWrite(driver2motor4enB, speed);
}

void moveForward() {
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
  digitalWrite(driver1motor1in1, HIGH);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, HIGH);
  digitalWrite(driver1motor2in4, LOW);
  digitalWrite(driver2motor3in1, HIGH);
  digitalWrite(driver2motor3in2, LOW);
  digitalWrite(driver2motor4in3, HIGH);
  digitalWrite(driver2motor4in4, LOW);
}

void strafeRight(){
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

void stopAllWheels() {
  digitalWrite(driver1motor1in1, LOW);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, LOW);
  digitalWrite(driver1motor2in4, LOW);
  digitalWrite(driver2motor3in1, LOW);
  digitalWrite(driver2motor3in2, LOW);
  digitalWrite(driver2motor4in3, LOW);
  digitalWrite(driver2motor4in4, LOW);
}

// This function lets you control spinning direction of motors
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(driver1motor1enA, 200);
  analogWrite(driver1motor2enB, 200);

  //// this crashes the giga
  analogWrite(driver2motor3enA, 200);
  analogWrite(driver2motor4enB, 200);
  // try digital instead
  // digitalWrite(driver2motor3enA, 255);
  // digitalWrite(driver2motor4enB, 255);


  // Turn on motor A & B
  digitalWrite(driver1motor1in1, HIGH);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, HIGH);
  digitalWrite(driver1motor2in4, LOW);

  digitalWrite(driver2motor3in1, HIGH);
  digitalWrite(driver2motor3in2, LOW);
  digitalWrite(driver2motor4in3, HIGH);
  digitalWrite(driver2motor4in4, LOW);

  delay(2000);

  // Now change motor directions
  digitalWrite(driver1motor1in1, LOW);
  digitalWrite(driver1motor1in2, HIGH);
  digitalWrite(driver1motor2in3, LOW);
  digitalWrite(driver1motor2in4, HIGH);

  digitalWrite(driver2motor3in1, LOW);
  digitalWrite(driver2motor3in2, HIGH);
  digitalWrite(driver2motor4in3, LOW);
  digitalWrite(driver2motor4in4, HIGH);


  delay(2000);

  // Turn off motors
  digitalWrite(driver1motor1in1, LOW);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, LOW);
  digitalWrite(driver1motor2in4, LOW);

  digitalWrite(driver2motor3in1, LOW);
  digitalWrite(driver2motor3in2, LOW);
  digitalWrite(driver2motor4in3, LOW);
  digitalWrite(driver2motor4in4, LOW);
}

// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(driver1motor1in1, LOW);
  digitalWrite(driver1motor1in2, HIGH);
  digitalWrite(driver1motor2in3, LOW);
  digitalWrite(driver1motor2in4, HIGH);

  //  digitalWrite(driver2motor3in1, LOW);
  //  digitalWrite(driver2motor3in2, HIGH);
  //  digitalWrite(driver2motor4in3, LOW);
  //  digitalWrite(driver2motor4in4, HIGH);


  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(driver1motor1enA, i);
    analogWrite(driver1motor2enB, i);

    //    analogWrite(driver2motor3enA, i);
    //    analogWrite(driver2motor4enB, i);

    delay(20);
  }

  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(driver1motor1enA, i);
    analogWrite(driver1motor2enB, i);
    //   analogWrite(driver2motor3enA, i);
    //    analogWrite(driver2motor4enB, i);
    delay(20);
  }

  // Now turn off motors
  digitalWrite(driver1motor1in1, LOW);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, LOW);
  digitalWrite(driver1motor2in4, LOW);
  digitalWrite(driver2motor3in1, LOW);
  digitalWrite(driver2motor3in2, LOW);
  digitalWrite(driver2motor4in3, LOW);
  digitalWrite(driver2motor4in4, LOW);
}

////
