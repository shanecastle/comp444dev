#include <Wire.h>

#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

void setup() {
  Serial.begin(9600);
  Serial.println("-----------------------------------------");
  Serial.println("16 channel PWM test !");

  // if you want to really speed stuff up, you can go into ‘fast 400khz I2C’ mode
  // some i2c devices dont like this so much so if you’re sharing the bus, watch
  // out for this!
  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency

  // save I2C bitrate
  uint8_t twbrbackup = TWBR;

  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12;  // upgrade to 400KHz!
}

bool done = false;

uint16_t pwmConst = 256;
uint16_t servoCount = 2;

void loop() {
  if (done) return;

  Serial.println(F("-------------------------------------"));
  Serial.println(F("Setting servo manually "));

  pwm.setPWM(1, 0, 300);
  delay(1000);
  pwm.setPWM(1, 0, 2000);
  delay(1000);
  /*
  pwm.setPWM(1, 0, 100);
  delay(1000);
  pwm.setPWM(1, 0, 150);
  delay(1000);
  pwm.setPWM(1, 0, 170);
  delay(1000);
*/

  Serial.println(F("done"));

    done = true;
    return;
  
  pwm.setPWM(3, 0, 50);
  delay(500);
  pwm.setPWM(3, 0, 100);
  delay(500);
  pwm.setPWM(3, 0, 150);
  delay(500);
  pwm.setPWM(3, 0, 200);
  delay(500);


  pwm.setPWM(1, 0, 50);
  pwm.setPWM(2, 0, 50);
  pwm.setPWM(3, 0, 50);
  pwm.setPWM(4, 0, 50);


  Serial.println(F("Setting servo manually "));
  pwm.setPWM(0, 0, 100);
  pwm.setPWM(0, 0, 0);
  delay(1000);

  pwm.setPWM(1, 0, 100);
  pwm.setPWM(1, 0, 0);
  delay(1000);


  // Drive each PWM in a ‘wave’
  for (uint16_t i = 0; i < pwmConst; i += 8) {
    for (uint8_t pwmnum = 0; pwmnum < servoCount; pwmnum++) {
      //uint8_t pwmnum = 0;
      uint16_t val = (i + (pwmConst / servoCount) * pwmnum) % pwmConst;
      Serial.print(F("Setting val on servo "));
      Serial.print(pwmnum);
      Serial.print(" to ");
      Serial.println(val);
      pwm.setPWM(pwmnum, 0, val);
    }
  }

  Serial.println("test complete");
  done = true;
}
