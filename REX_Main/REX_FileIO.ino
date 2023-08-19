// REX_FileIO

#include <Arduino_USBHostMbed5.h>
#include <PluggableUSBMSD.h>

USBHostMSD msd;
mbed::FATFileSystem usb("USB_DRIVE");

FILE *file = nullptr;

void setupUsb() {
  logDebug("[FILEIO] Setting up USB device");

  // Enable power for HOST USB connector
  pinMode(PA_15, OUTPUT);
  digitalWrite(PA_15, HIGH);

  while (!msd.connect()) {
    logDebug("[FILEIO] Insert a USB stick into the USB-A port.");
    delay(300);
  }

  logDebug("[FILEIO] Mounting USB device ...");
  int const rc_mount = usb.mount(&msd);
  if (rc_mount) {
    Serial.print("[FILEIO] Error mounting USB device ");
    Serial.println(rc_mount);
    return;
  }

  logDebug("[FILEIO] setup complete");
}