#include <Arduino.h>

#include <GxEPD.h>
#include <GxGDEW047C80/GxGDEW047C80.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "axp2101.h"

#include <esp_adc_cal.h>
#include "esp_heap_caps.h"

#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_err.h"
#include "esp_log.h"

#include "board_t5_s3_pro.h"

#define ADC1_BAT_VOLTAGE_CHANNEL (ADC1_CHANNEL_7) // GPIO3
#define DEFAULT_VREF 1100

static const char *TAG = "variant.cpp";
static esp_adc_cal_characteristics_t adc1_chars;
bool g_tp_wakeup = false;

uint16_t current_voltage = 0;

void initVariant()
{
    pinMode(3, INPUT_PULLUP);
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, DEFAULT_VREF, &adc1_chars);
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_BAT_VOLTAGE_CHANNEL, ADC_ATTEN_DB_11);

    uint32_t v1 = adc1_get_raw(ADC1_BAT_VOLTAGE_CHANNEL);

    uint16_t v2 = esp_adc_cal_raw_to_voltage(v1, &adc1_chars);
    current_voltage = v2;

    ESP_LOGI(TAG, "Battery voltage:%d mV", v2);

    ESP_LOGI(TAG, "ePoi Labs T5-4.7-S3 initialization complete");
}