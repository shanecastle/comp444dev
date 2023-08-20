// REX_Main.ino
// Main source file for R.E.X. - COMP444 final project
// Shane Castle, #2621506, August, 2023

#include "Arduino.h"

// write serial messages
bool debugMode = true;

void setup() {
  //RPC.begin();  //boot the M4 coprocessor
  Serial.begin(9600);
  delay(1000);
  log("------------------------------------------------");
  log("[SETUP] - STARTING SETUP -");

  // initialize the LCD display (in REX_Display.ino)
  log("[SETUP] Setting up display");
  setupDisplay();


  log("[SETUP] Setting up USB");
  setupUsb();

  // initialize the motors (in REX_Movement.ino)
  log("[SETUP] Setting up movement");
  setupMovement();

  log("[SETUP] - SETUP COMPLETE -");
  playSoundFile("WARP.wav");
}

void loop() {
  //logDebug("Showing test message");
  showMessage("test1 " + String(millis()));

  checkMotorButtons();

  motorTest();
}

void log(String message) {
  Serial.println(message);
}

void logDebug(String message) {
  if (!debugMode) return;
  Serial.println(message);
}

