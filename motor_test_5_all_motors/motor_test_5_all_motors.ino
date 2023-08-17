
// Motor driver test
// -----------------------------------------------------------

#include <RPC.h>            // to support 2nd CPU core
#include <LiquidCrystal.h>  // LCD screen
#include <Servo.h>          // servo library
#include <FastLED.h>

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

// setup LED Lights
#define NUM_LEDS 144
#define DATA_PIN 6

CRGB leds[NUM_LEDS];


// setup start/stop buttons
int redButtonPin = 65;    // stop motors
int greenButtonPin = 64;  // start motors
int blueButtonPin = 57;   // start arm

// ultrasonic distances
float distanceFront = 0;
float distanceLeft = 0;
float distanceRight = 0;
float distanceBack = 0;

// lcd screen setup
LiquidCrystal lcd(59, 61, 63, 58, 60, 62);
unsigned long messageDelay = 0;  // used to update screen once per second
bool delayRunning = false;
unsigned long DELAY_TIME = 1500;


//distance sensor pins
const int trig1Pin = 28;
const int echo1Pin = 29;
const int trig2Pin = 30;
const int echo2Pin = 31;
const int trig3Pin = 32;
const int echo3Pin = 33;
const int trig4Pin = 34;
const int echo4Pin = 35;

const int FRONT = 1;
const int BACK = 2;
const int LEFT = 3;
const int RIGHT = 4;

bool runWheels = false;
String message = "";


//create servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

const int servo1Pin = 40;
const int servo2Pin = 41;
const int servo3Pin = 42;
const int servo4Pin = 43;
const int servo5Pin = 44;
const int servo6Pin = 45;

//-----------------------------------------------------------------------------

void setup() {
  RPC.begin();

  //tell the lcd the display is 16 wide by 2 characters high
  lcd.begin(16, 2);
  lcd.clear();
  messageDelay = millis();
  delayRunning = true;

  // init LED lights
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Serial.begin(9600);
  // Serial.write("Staring motor test");

  // setup motor on/off buttons
  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);

  // setup distance sensors
  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo2Pin, INPUT);
  pinMode(trig3Pin, OUTPUT);
  pinMode(echo3Pin, INPUT);
  pinMode(trig4Pin, OUTPUT);
  pinMode(echo4Pin, INPUT);

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
  //  pinMode(M1_ENCODER_B, INPUT);
  //  pinMode(M2_ENCODER_A, INPUT);
  //  pinMode(M2_ENCODER_B, INPUT);

  showMessage("Press Blue");
  while (digitalRead(blueButtonPin) == HIGH) {}

  servoTest();
}

void loop() {

  potentiometer = analogRead(A0);
  //speed = round(potentiometer / 4);  // potentiometer returns 0 to 1023
  speed = map(potentiometer, 0, 1023, 0, 255);

  distanceFront = getDistance(FRONT);
  distanceBack = getDistance(BACK);
  distanceLeft = getDistance(LEFT);
  distanceRight = getDistance(RIGHT);


  if (digitalRead(redButtonPin) == LOW) {
    runWheels = false;
    stopAllWheels();
  } else if (digitalRead(greenButtonPin) == LOW) {
    runWheels = true;
  }

  showCurrentStatus();

  if (runWheels == false) return;

  setAllMotorSpeed(speed);

  // run all wheels
  //moveForward();
  // return;

  //moveLeft();

  strafeRight();
  delay(1500);

  stopAllWheels();
  delay(3000);

  strafeLeft();
  delay(1500);

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

void strafeRight() {
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

void showMessage(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void showCurrentStatus() {

  // has one second passed?

  // see here: https://www.instructables.com/Coding-Timers-and-Delays-in-Arduino/
  //if ((millis() - nextDisplay) > 3000) return;
  if (delayRunning && ((millis() - messageDelay) < DELAY_TIME)) return;

  lcd.clear();

  message = "D:"
            + String(distanceFront, 0) + ","
            + String(distanceBack, 0) + ","
            + String(distanceLeft, 0) + ","
            + String(distanceRight, 0);

  lcd.setCursor(0, 0);
  lcd.print(message);

  //move the cursor to the first space of the bottom row
  lcd.setCursor(14, 1);
  lcd.print(millis() / 1000);

  lcd.setCursor(0, 1);
  String motorMessage = "M:" + String(runWheels) + ",S:" + String(speed);
  lcd.print(motorMessage);

  // set the next update for one second from now
  //nextDisplay = millis() + 3000;
  messageDelay += DELAY_TIME;

  /*
  /// CLEANUP - Unused

    //set the cursor to the 0,0 position (top left corner)
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.setCursor(2, 0);
  lcd.print(speed);

  lcd.setCursor(6, 1);
  lcd.print(runWheels);
  */
}

void waitForBlueButtonPress() {
  while (digitalRead(blueButtonPin) == HIGH) {}
}

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
int getDistance(int side) {
  // FROM SIK Circuit 3B - https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41/all#circuit-3b-distance-sensor
  float echoTime;          //variable to store the time it takes for a ping to bounce off an object
  int calculatedDistance;  //variable to store the distance calculated from the echo time
  int trigPin = 0;
  int echoPin = 0;

  if (side == FRONT) {
    trigPin = trig1Pin;
    echoPin = echo1Pin;
  } else if (side == BACK) {
    trigPin = trig2Pin;
    echoPin = echo2Pin;
  } else if (side == LEFT) {
    trigPin = trig3Pin;
    echoPin = echo3Pin;
  } else if (side == RIGHT) {
    trigPin = trig4Pin;
    echoPin = echo4Pin;
  }

  if (trigPin == 0) return -1;  // shouldnt get here

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //use the pulsein command to see how long it takes for the
  //pulse to bounce back to the sensor
  echoTime = pulseIn(echoPin, HIGH);

  //calculate the distance of the object that reflected the pulse
  //(half the bounce time multiplied by the speed of sound)
  calculatedDistance = round(echoTime / 148.0);

  //send back the distance that was calculated
  return calculatedDistance;
}

void servoTest() {
  showMessage("Servo5 15deg");
  servo5.write(15);  // degs
  servo5.attach(servo5Pin);
  delay(500);

  waitForBlueButtonPress();

  showMessage("Servo4 90deg");
  servo4.write(90);  // degs
  servo4.attach(servo4Pin);
  delay(500);

  for (int i = 90; i >= 0; i -= 5) {
    servo4.write(i);
    delay(100);
  }

  waitForBlueButtonPress();

  showMessage("Servo5 90deg");
  for (int i = 15; i <= 90; i += 5) {
    servo5.write(i);
    delay(100);
  }
  waitForBlueButtonPress();

  showMessage("Servo4 90deg");
  for (int i = 0; i <= 90; i += 5) {
    servo4.write(i);
    delay(100);
  }

  showMessage("Press Servo3");
  waitForBlueButtonPress();

  servo3.write(0);           // degs
  servo3.attach(servo3Pin);  // pin
  delay(2000);

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
}


//-----------------------------------------------------------------------------
// LED LIGHTS

void blackAllLeds() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Black;
  }
  FastLED.show();
}

void showAllLeds() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Blue;
  }
  FastLED.show();
}

void showSingleLED(int ledId) {
  leds[ledId] = CRGB::Red;
  FastLED.show();
  delay(2000);
}

void initBlack() {
  // Set the first led back to black for 1 second
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
}

void initBlack2() {
  // Set the first led back to black for 1 second
  leds[0] = CRGB::Black;
  leds[5] = CRGB::Black;

  FastLED.show();
  delay(1000);
}

void runXylon() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
  }

  for (int dot = NUM_LEDS; dot >= 0; dot--) {
    leds[dot] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
  }
}

void runXylon2() {
  Serial.println("--------------------------------------------");
  Serial.println("Xylon2 starting");

  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot - 1] = CRGB::Red;
    leds[dot] = CRGB::Blue;
    leds[dot + 5] = CRGB::Green;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot - 1] = CRGB::Black;
    leds[dot] = CRGB::Black;
    leds[dot + 5] = CRGB::Black;

    delay(30);
  }

  for (int dot = NUM_LEDS; dot >= 6; dot--) {

    leds[dot - 5] = CRGB::Green;
    leds[dot] = CRGB::Blue;
    leds[dot + 1] = CRGB::Red;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot - 5] = CRGB::Black;
    leds[dot] = CRGB::Black;
    leds[dot + 1] = CRGB::Black;
    delay(30);
  }
  Serial.println("Xylon2 done");
}

////
