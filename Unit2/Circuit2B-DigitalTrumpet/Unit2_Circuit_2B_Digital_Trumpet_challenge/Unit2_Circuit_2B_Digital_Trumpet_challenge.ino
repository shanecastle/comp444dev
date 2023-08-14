/*
  SparkFun Inventor’s Kit
  Circuit 2B-ButtonTrumpet

  Use 3 buttons plugged to play musical notes on a buzzer.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

//set the pins for the button and buzzer
int firstKeyPin = 2;
int secondKeyPin = 3;
int thirdKeyPin = 4;

int buzzerPin = 10;

int notes[] = { 262, 294, 330, 349, 392, 440, 494, 523 };
int previousNote = 0;

void setup() {
  Serial.begin(9600);

  //set the button pins as inputs
  pinMode(firstKeyPin, INPUT_PULLUP);
  pinMode(secondKeyPin, INPUT_PULLUP);
  pinMode(thirdKeyPin, INPUT_PULLUP);

  //set the buzzer pin as an output
  pinMode(buzzerPin, OUTPUT);
}

void loop() {

  int note = 0;
  bool play = false;

  if (digitalRead(firstKeyPin) == LOW) {  //if the first key is pressed
    note += 1;
    play = true;
  }

  if (digitalRead(secondKeyPin) == LOW) {  //if the second key is pressed
    note += 2;
    play = true;
  }

  if (digitalRead(thirdKeyPin) == LOW) {  //if the third key is pressed
    note += 4;
    play = true;
  }

  if (play == true) {
    int noteToPlay = notes[note - 1];
    if (noteToPlay != previousNote) {
      Serial.println("Playing note [" + String(note - 1) + "] " + String(noteToPlay));
      previousNote = noteToPlay;
    }
    tone(buzzerPin, noteToPlay);
  } else {
    noTone(buzzerPin);  //if no key is pressed turn the buzzer off
    previousNote = 0;
  }
}

/*
  note  frequency
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz
*/
