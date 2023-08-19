// REX_Main.ino
// Main source file for R.E.X. - COMP444 final project
// Shane Castle, #2621506, August, 2023

#include "Arduino.h"
// Use RPC to work with the 2nd core
//#include <RPC.h>

//Thread soundThread;
//Thread displayThread;
//Thread moveThread;

// write serial messages
bool debugMode = true;

void setup() {
  //RPC.begin();  //boot the M4 coprocessor
  Serial.begin(9600);

  // initialize the LCD display (in REX_Display.ino)
  log("Setting up display");
  setupDisplay();

  // initialize the DAC (in REX_Sound.ino)
  //log("Setting up sound.");
  //setupSound();

  // initialize the motors (in REX_Movement.ino)
  setupMovement();
}

void loop() {
  //logDebug("Showing test message");
  showMessage("test1 " + String(millis()));

  // play the champion song (in REX_Sound.ino)
  //playChampion();

  motorTest();
}

void log(String message) {
  Serial.println(message);
}

void logDebug(String message) {
  if (!debugMode) return;
  Serial.println(message);
}


/*
void processSerialBuffer() {
  String buffer = "";
  while (RPC.available()) {
    buffer += (char)RPC.read();  // Fill the buffer with characters
  }
  if (buffer.length() > 0) {
    Serial.print(buffer);
  }
}
*/
