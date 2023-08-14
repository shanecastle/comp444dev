
// Motor driver test

#include <RPC.h> // to boot the 2nd core

// L298N Motor Driver 1 connections
int driver1motor1enA = 4;  // Speed control for motor 1
int driver1motor1in1 = 5;  // Direction control for Motor 1
int driver1motor1in2 = 6;  // Direction control for Motor 1
int driver1motor2enB = 9;
int driver1motor2in3 = 11;
int driver1motor2in4 = 10;

// L298N Motor Driver 2 connections
int driver2motor3enA = 56;  // Speed control for motor 3
int driver2motor3in1 = 58;  // Direction control for Motor 3
int driver2motor3in2 = 60;  // Direction control for Motor 3
int driver2motor4enB = 62;
int driver2motor4in3 = 64;
int driver2motor4in4 = 66;


#define M1_ENCODER_A 2  //  Motor 1 Encoder A
#define M1_ENCODER_B 3  //  Motor 1 Encoder B

#define M2_ENCODER_A 7  //  Motor 2 Encoder A
#define M2_ENCODER_B 8  //  Motor 2 Encoder B

void setup() {
   RPC.begin();


 // Serial.begin(9600);
 // Serial.write("Staring motor test");

  // Set all the motor control pins to outputs
  pinMode(driver1motor1enA, OUTPUT);
  pinMode(driver1motor2enB, OUTPUT);
  pinMode(driver1motor1in1, OUTPUT);
  pinMode(driver1motor1in2, OUTPUT);
  pinMode(driver1motor2in3, OUTPUT);
  pinMode(driver1motor2in4, OUTPUT);


  pinMode(driver2motor3enA, OUTPUT);
  pinMode(driver2motor4enB, OUTPUT);
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
  pinMode(M1_ENCODER_A, INPUT);
  pinMode(M1_ENCODER_B, INPUT);

  pinMode(M2_ENCODER_A, INPUT);
  pinMode(M2_ENCODER_B, INPUT);

}

void loop() {
  directionControl();
  delay(1000);
  speedControl();
  delay(1000);

  int a = digitalRead(M1_ENCODER_A);
  int b = digitalRead(M1_ENCODER_B);
 // Serial.print(a * 5);
//  Serial.print(" ");
 // Serial.print(b * 5);
//  Serial.println();
  delay(1000);
}

// This function lets you control spinning direction of motors
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(driver1motor1enA, 255);
  analogWrite(driver1motor2enB, 255);

//// this crashes the giga
//  analogWrite(driver2motor3enA, 255);
//  analogWrite(driver2motor4enB, 255);
// try digital instead
  digitalWrite(driver2motor3enA, 255);
  digitalWrite(driver2motor4enB, 255);


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

//  digitalWrite(driver2motor3in1, LOW);
//  digitalWrite(driver2motor3in2, HIGH);
//  digitalWrite(driver2motor4in3, LOW);
//  digitalWrite(driver2motor4in4, HIGH);


  delay(2000);

  // Turn off motors
  digitalWrite(driver1motor1in1, LOW);
  digitalWrite(driver1motor1in2, LOW);
  digitalWrite(driver1motor2in3, LOW);
  digitalWrite(driver1motor2in4, LOW);

//  digitalWrite(driver2motor3in1, LOW);
//  digitalWrite(driver2motor3in2, LOW);
//  digitalWrite(driver2motor4in3, LOW);
//  digitalWrite(driver2motor4in4, LOW);

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

//  digitalWrite(driver2motor3in1, LOW);
//  digitalWrite(driver2motor3in2, LOW);

//  digitalWrite(driver2motor4in3, LOW);
//  digitalWrite(driver2motor4in4, LOW);
}

////
