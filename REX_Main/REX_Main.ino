// REX_Main.ino
// Main source file for R.E.X. - COMP444 final project
// Shane Castle, #2621506, August, 2023

#include "RPC.h"
#include "Arduino.h"

// write serial messages
bool debugMode = true;

// for rpc serial messages
String buffer = "";
//bool showLightsFlag = true;


void setup() {

  Serial.begin(9600);
  delay(1000);
  log("------------------------------------------------");
  log("[SETUP] - STARTING SETUP -");

  log("[SETUP] Starting RPC (boot M4)");
  RPC.begin();  //boot the M4 coprocessor

  // initialize the LCD display (in REX_Display.ino)
  log("[SETUP] Setting up display");
  setupDisplay();

  log("[SETUP] Setting up USB");
  setupUsb();

  // initialize the motors (in REX_Movement.ino)
  log("[SETUP] Setting up movement");
  setupMovement();

  log("[SETUP] Setting up laser");
  setupLaser();

  log("[SETUP] Setting up colour sensor");
  setupColourSensor();

  log("[SETUP] Setting up Arm Controller");
  setupArmController();

  log("[SETUP] Setup Distance detectors");
  setupDistance();

  log("[SETUP] Setup LED lights");
  setupLights();

  log("[SETUP] - SETUP COMPLETE -");
  log("------------------------------------------------");

  playSoundFile("WARP.wav");
}

void loop() {
  //logDebug("Showing test message");
  showMessage("test1 " + String(millis()));

  showRpcSerial();

  /*
  if (showLightsFlag) {
    showMessage(0, 1, "Starting Lights");
    showLights();
    showLightsFlag = false;
  }
  */

  //showDistance();
  //getDistance();
  //showDistance();

  //detectColour();

  // arm test
  testRobotArm();

  //detectBeam();

  //checkMotorButtons();
  //motorTest();
}

void showRpcSerial() {
  buffer = "";
  while (RPC.available()) {
    buffer += (char)RPC.read();  // Fill the buffer with characters
  }
  if (buffer.length() > 0) {
    logDebug("[RPC] " + buffer);
  }
}

void log(String message) {
  Serial.println(message);
}

void logDebug(String message) {
  if (!debugMode) return;
  Serial.println(message);
}
