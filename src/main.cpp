#include <Arduino.h>
#include <GxEPD.h>
#include <GxGDEW047C80/GxGDEW047C80.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "Button.h"
#include "display.h"
#include "Meshtastic.h"
#include "Screen.h"
#include "Preferences.h"

Meshtastic meshtastic;

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("Initializing Meshtastic...");
  meshtastic.init();
  meshtastic.setDebugMode(true); // Enable debug logging
  Serial.println("Meshtastic initialized.");

  // You can add more initialization code here for the display, buttons, etc.
}

void loop() {
  meshtastic.loop();
  delay(10); // Short delay to prevent watchdog timeout
}