#include <Arduino.h>
#include "variant.h"
#include <GxEPD.h>
#include <GxGDEW047C80/GxGDEW047C80.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "Meshtastic.h"

GxIO_Class io(SPI, /*CS=*/9, /*DC=*/8, /*RST=*/7);
GxEPD_Class display(io, /*RST=*/7, /*BUSY=*/6);

Meshtastic meshtastic;

void setup() {
  Serial.begin(115200);
  initVariant();

  display.init(115200, true, 2, false);
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(0, 15);
  display.println("Initializing Meshtastic...");
  display.display(false);

  meshtastic.init();
  meshtastic.setDebugMode(true);

  display.setCursor(0, 35);
  display.println("Meshtastic initialized.");
  display.display(false);
}

void loop() {
  meshtastic.loop();
  delay(10);
}