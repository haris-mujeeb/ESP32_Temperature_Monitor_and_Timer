#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>  // Make sure you have the correct library for your screen
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBoldOblique9pt7b.h>
#include <Fonts/FreeMonoBoldOblique18pt7b.h>
#include <Fonts/FreeMonoBoldOblique24pt7b.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include <Fonts/FreeSerifItalic24pt7b.h>
#include <Fonts/FreeSerifBoldItalic18pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBoldOblique12pt7b.h>
#include <Fonts/FreeSansBoldOblique18pt7b.h>
#include <Fonts/FreeMonoBoldOblique24pt7b.h>

// TFT Screen configuration
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS 15 // Chip select pin
#define TFT_DC 2 // Data/Command pin
#define TFT_RST 4 // Reset pin
#define TFT_BLK 32

// Screen Dimensions
#define SCREEN_WIDTH    320  // Screen width in pixels
#define SCREEN_HEIGHT   172  // Screen height in pixels

// Other Hardware Configurations
#define MAX_BRIGHTNESS 255  // Maximum brightness for the screen (0 to 255)
#define MIN_BRIGHTNESS 0    // Minimum brightness for the screen (0 to 255)


// Create TFT display object
extern Adafruit_ST7789 tft;

// Helper functions for display management
void initializeTFT();
void clearScreen();
void drawText(int x, int y, const char* text, int textSize, const GFXfont* fontType,uint16_t color);