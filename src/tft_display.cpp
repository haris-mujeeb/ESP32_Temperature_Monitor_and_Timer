#include "tft_display.hpp"

void initializeTFT() {
    // Initialize the TFT display
    tft.init(SCREEN_HEIGHT, SCREEN_WIDTH);
    tft.setRotation(1);  // Rotate the screen to the correct orientation
    tft.fillScreen(ST77XX_BLACK);  // Clear the screen
    Serial.println("[Log] TFT initialized successfully.");
}

void clearScreen() {
    tft.fillScreen(ST77XX_BLACK);  // Clears the screen to black
}

void drawText(int x, int y, const char* text, int fontSize, const GFXfont *textFont, uint16_t color) {
    tft.setCursor(x, y + 25);
    tft.setFont(textFont);
    tft.setTextSize(fontSize);  // Set the text size
    tft.setTextColor(color);    // Set the text color
    tft.print(text);            // Print the text
}