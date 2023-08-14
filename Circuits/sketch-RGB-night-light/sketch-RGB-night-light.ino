int photoresistor = A0;
int potentiometer = A1;
int threshold = 700;

const int RedPin = 9;
const int GreenPin = 10;
const int BluePin = 11;

void setup() {
  Serial.begin(9600);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
}

void loop() {
  photoresistor = analogRead(A0);
  potentiometer = analogRead(A1);
  Serial.print("Photoreistor value:");
  Serial.print(photoresistor);
  Serial.print(" Potentiometer value:");
  Serial.println(potentiometer);
  if (photoresistor < threshold) {
    if (potentiometer > 0 && potentiometer <= 150)
      red();
    if (potentiometer > 150 && potentiometer <= 300)
      orange();
    if (potentiometer > 300 && potentiometer <= 450)
      yellow();
    if (potentiometer > 450 && potentiometer <= 600)
      green();
    if (potentiometer > 600 && potentiometer <= 750)
      cyan();
    if (potentiometer > 750 && potentiometer <= 900)
      blue();
    if (potentiometer > 900)
      magenta();
  } else {      //if it isn't dark turn the LED off
    turnOff();  //call the turn off function
  }
  delay(100);
}
void red() {

  //set the LED pins to values that make red
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
  while(true){
    orange();
    delay(150);
    green();
    delay(150);
    blue();
    delay(150);
  }
}
void orange() {

  //set the LED pins to values that make orange
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 50);
  analogWrite(BluePin, 0);
}
void yellow() {

  //set the LED pins to values that make yellow
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 0);
}
void green() {

  //set the LED pins to values that make green
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 0);
}
void cyan() {

  //set the LED pins to values that make cyan
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 100);
}
void blue() {

  //set the LED pins to values that make blue
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 100);
}
void magenta() {

  //set the LED pins to values that make magenta
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 100);
}
void turnOff() {

  //set all three LED pins to 0 or OFF
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
}
