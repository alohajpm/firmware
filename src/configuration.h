#pragma once

//
// Meshtastic Firmware Configuration
//
// This file contains settings for the Meshtastic firmware. You can
// change settings here and recompile the firmware to change the firmware.
//

// ******************************************************
// User configurable variables start below this point
// ******************************************************

/**
 * The application version, reported by the mobile app. Should be
 * bumped on each release so that the apps can warn users if a
 * new/incompatible firmware is available.
 */
//#undef APP_VERSION

#ifndef VARIANT_H
#define VARIANT_H

#include <Arduino.h>
#include "pins_arduino.h"

#define VARIANT_H

#ifdef __cplusplus
extern "C"
{
#endif

    extern uint16_t current_voltage;

    void initVariant(void);

#ifdef __cplusplus
}
#endif

// This must be a literal
#define USER_SETUP_LOADED

#define LILYGO_T5_V2_1_3

// #define LILYGO_T5_V2_3

#define HAS_DISPLAY

#define GxGDEW047C80
#define EPD_DC 8
#define EPD_CS 9
#define EPD_BUSY 6
#define EPD_RST 7

#define TOUCH_SDA 4
#define TOUCH_SCL 5
#define TOUCH_RST 0
#define TOUCH_IRQ 1

#define LORA_SCK 12
#define LORA_MISO 13
#define LORA_MOSI 11
#define LORA_CS 10
#define LORA_RST 21
#define LORA_IRQ 39
#define LORA_BUSY 38

#define HAS_LORA

#define HAS_RTC

#define HAS_ACCELEROMETER

#define HAS_BUTTON

#define HAS_BATTERYADC

#define BATTERY_MULTIPLIER 1.7

#define BOARD_LED 2

#define BAT_VOL_PIN 3

#define BUTTON_1 3
#define BUTTON_2 4
#define BUTTON_3 5

#define EPD_POWER_ENABLE_PIN -1
#define EPD_RESET_PIN -1

#define SPI_MOSI 11
#define SPI_MISO 13
#define SPI_SCK 12

#define LORA_PREAMBLE_LEN 20
#define LORA_CODING_RATE 7
#define LORA_SIGNAL_BANDWIDTH 125000
#define LORA_SPREADING_FACTOR 7
#define LORA_TX_POWER 14
#define LORA_CHANNEL_NUM 3

#define USER_NAME "T5 User"
#define SHORT_NAME "T5"
#define LONG_NAME "T5 User"
#define SOFTWARE_VERSION "0.0.1"

#endif // VARIANT_H

// ******************************************************
//
//
// No user configurable items below this point.
//
// (Changing these settings might be okay, but do so at your own risk)
//
//
// ******************************************************

#include "platform/esp32/architecture.h"
#include "main.h"
#include "mesh/MeshTypes.h"

// These defines cause all settings to be obtained from nonvolatile
// ram.  Useful for development, but should not be used in a release
// build.

// FIXME - should auto detect the platform #define CONFIG_FROM_NVS

/**
 * This header is a good place to #undef values from the config files
 * to turn features off
 */