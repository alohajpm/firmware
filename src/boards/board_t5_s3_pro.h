#pragma once

#include <variant.h>

#ifdef BOARD_T5_S3_PRO

#define NUM_BUTTONS 3

// Button Pins
#define BUTTON_LEFT_PIN     3
#define BUTTON_CENTER_PIN   4
#define BUTTON_RIGHT_PIN    5

// LoRa Pins (SX1262)
#define LORA_SCK_PIN       12
#define LORA_MISO_PIN      13
#define LORA_MOSI_PIN      11
#define LORA_CS_PIN        10
#define LORA_RST_PIN       21
#define LORA_IRQ_PIN       39
#define LORA_BUSY_PIN      38

// Display Pins (4.7" E-Paper)
#define EPD_SCK_PIN        12
#define EPD_MISO_PIN       13
#define EPD_MOSI_PIN       11
#define EPD_CS_PIN         9
#define EPD_DC_PIN         8
#define EPD_RST_PIN        7
#define EPD_BUSY_PIN       6

// Accelerometer Pins (if present)
#define ACCEL_SDA_PIN      4  // Replace with actual pins if different
#define ACCEL_SCL_PIN      5 // Replace with actual pins if different
#define ACCEL_INT_PIN      1 // Replace with actual pins if different

// RTC Pins (if present)
#define RTC_SDA_PIN        4  // Replace with actual pins if different
#define RTC_SCL_PIN        5 // Replace with actual pins if different
#define RTC_INT_PIN        2  // Replace with actual pins if different

// Battery ADC Pin
#define BATTERY_ADC_PIN    36 // Replace with actual pin

// Other Definitions
#define BATTERY_MULTIPLIER 1.7 // Adjust if needed based on your voltage divider

// Function to get ADC for battery level (example)
static inline uint16_t getBatteryVoltage() {
  return analogRead(BATTERY_ADC_PIN) * BATTERY_MULTIPLIER;
}

#endif // BOARD_T5_S3_PRO