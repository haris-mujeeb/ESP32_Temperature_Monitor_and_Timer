#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include "gui/temperature_sensor.hpp"
#include "tft_display.hpp"
#include "rotary_encoder.hpp"
#include "display/display_context.hpp"

// Pin definitions for various hardware components

// Temperature and Time Settings
#define DEFAULT_TEMP_THRESHOLD 50.0   // Default temperature threshold in Celsius
#define DEFAULT_TIME_THRESHOLD 20 * 1000 // Default time threshold in milliseconds (20 seconds)

// EEPROM settings
#define EEPROM_SIZE 64  // EEPROM size in bytes (ESP32 allows up to 512 bytes by default)

#define BOOT_PIN 0

// Initialize hardware components
void initializeHardware();
void initializeEncoder();