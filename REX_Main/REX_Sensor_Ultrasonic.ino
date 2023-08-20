// REX_Sensor_Ultrasonic.ino
//

//distance sensor pins
const int trig1Pin = 28;
const int echo1Pin = 29;
const int trig2Pin = 30;
const int echo2Pin = 31;
const int trig3Pin = 32;
const int echo3Pin = 33;
const int trig4Pin = 34;
const int echo4Pin = 35;

// ultrasonic distances
float distanceFront = 0;
float distanceLeft = 0;
float distanceRight = 0;
float distanceBack = 0;

const int FRONT = 1;
const int BACK = 2;
const int LEFT = 3;
const int RIGHT = 4;

void setupUltrasonic() {
  // setup distance sensors
  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo2Pin, INPUT);
  pinMode(trig3Pin, OUTPUT);
  pinMode(echo3Pin, INPUT);
  pinMode(trig4Pin, OUTPUT);
  pinMode(echo4Pin, INPUT);
}

void getDistance() {
  distanceFront = getDistance(FRONT);
  distanceBack = getDistance(BACK);
  distanceLeft = getDistance(LEFT);
  distanceRight = getDistance(RIGHT);
}

void showDistance() {
  String message = "D:"
                   + String(distanceFront, 0) + ","
                   + String(distanceBack, 0) + ","
                   + String(distanceLeft, 0) + ","
                   + String(distanceRight, 0);

  logDebug(message);
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
