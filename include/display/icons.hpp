#pragma once
#include "tft_display.hpp"

class Wokwi_Icon_48Bit{
public:
    Wokwi_Icon_48Bit(const byte (*frames)[288], int frameCount, Adafruit_ST7789 &display, int x, int y)
        : pFrames(frames), FRAME_COUNT(frameCount), display(display), x(x), y(y), frame(0) {}

    void animate(unsigned long currentTimeMS, uint16_t frameDelay) {
        if (currentTimeMS - lastUpdateTimeMS > frameDelay) {
            display.fillRect(x, y, FRAME_WIDTH, FRAME_HEIGHT, ST77XX_BLACK);  // Clear the area
            display.drawBitmap(x, y, pFrames[frame], FRAME_WIDTH, FRAME_HEIGHT, iconColor);
            frame = (frame + 1) % FRAME_COUNT;  // Loop through frames
            lastUpdateTimeMS = currentTimeMS;
        }
    }
    int x;                       // X position on the screen
    int y;                       // Y position on the screen
    unsigned long lastUpdateTimeMS;
    const byte FRAME_WIDTH = 48;
    const byte FRAME_HEIGHT = 48;
    const byte (*pFrames)[288]; // Pointer to the frames
    const int FRAME_COUNT;       // Total number of frames
    uint16_t frameDelay;
    int frame;                  // Current frame index
    Adafruit_ST7789 &display;    // Reference to the display
    uint16_t iconColor = ST77XX_WHITE;
};

// Declare icon frames
extern const byte PROGMEM thermometer_icon_frames[][288];
extern const byte PROGMEM fire_icon_frames[][288];
extern const byte PROGMEM hourglass_icon_frames[][288];

// Declare icon instances
extern Wokwi_Icon_48Bit fireIcon;
extern Wokwi_Icon_48Bit thermometerIcon;
extern Wokwi_Icon_48Bit hourglassIcon;