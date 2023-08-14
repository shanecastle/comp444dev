/*
  Super basic servo test
*/
#include <Servo.h>  //include the servo library
Servo servo1;        //create a servo object
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;


void setup() {
  Serial.begin(9600);
  Serial.println("-----------------------------------------");
  Serial.println("Servo test. Press enter to start.");
  //servo.attach(8);  // servo in pin 9
  //servo2.attach(9);

  pinMode(7, INPUT_PULLUP); // pin 7 - momentary switch

 // wait for enter key
 // while (Serial.available() == 0) {
 // }

  // wait until the button is pressed
  while (digitalRead(7) == HIGH){
  }

  servo5.write(15);  // degs
  servo5.attach(12);
  delay(500);

  servo4.write(90);  // degs
  servo4.attach(11);
  delay(500);

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

  servo3.write(0);    // degs
  servo3.attach(10);  // pin
  delay(2000);

  for (int i = 0; i <= 90; i += 5) {
    servo3.write(i);
    delay(100);
  }

  servo1.write(120);
  servo1.attach(8);

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

bool done = false;


//==========================================================================================

void loop() {
  if (done) return;

   return;

  for (int i = 0; i < 180; i += 5) {
    servo4.write(i);
    delay(100);
  }

  done = true;
  return;

  /*

  for (int i = 0; i < 90; i += 5) {
    servo5.write(i);
    delay(100);
  }


  for (int i = 0; i < 90; i += 5) {
    servo3.write(i);
    delay(100);
  }
*/






  // for (int i = 0; i < 90; i+=5) {
  //   servo3.write(i);
  //    delay(100);
  //  }

  /*
  for (int i = 90; i >= 0; i -= 5) {
    Serial.print("setting to ");
    Serial.println(i);
    servo3.write(i);
    delay(100);
  }


  for (int i = 0; i <= 180; i += 5) {
    Serial.print("setting to ");
    Serial.println(i);
    servo3.write(i);
    delay(1000);
  }

  for (int i = 180; i >= 0; i -= 5) {
    Serial.print("setting to ");
    Serial.println(i);
    servo3.write(i);
    delay(1000);
  }
*/


  /*
 // servo6.write(100);
 // delay(100);
  Serial.println("setting to 0");
  servo5.write(0);

  Serial.println("setting to 90");
  servo5.write(90);
  delay(100);

 // Serial.println("setting to 180");
 // servo5.write(180);

 */




  servo2.write(120);
  delay(100);
  servo3.write(120);
  delay(100);
  servo4.write(120);
  delay(100);

  // Note:avoid driving servos all the 0 or 180 degrees it can
  // cause the motor to jitter which is bad for the servo
  for (int x = 120; x <= 180; x += 10) {
    Serial.print("moving to ");
    Serial.println(x);
    servo1.write(x);  //move the servo to the 10 degree position
    delay(100);
  }

  Serial.println("test complete");
  done = true;
}
