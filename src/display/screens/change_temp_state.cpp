#include "display/screens/change_temp_state.hpp"
#include "display/screens/home_screen_state.hpp"

// Initialize the screen with the temperature adjustment interface
void ChangeTemperatureState::init(DisplayContext& context) {
    tft.fillScreen(ST77XX_BLACK);
    drawTitle();
    drawTemperatureThreshold(context);
    lastActivityTime = millis();
}

// No continuous updates are required in this state
void ChangeTemperatureState::update(DisplayContext& context) {
    checkInactivityTimeout(context);
}

// Perform any necessary cleanup before exiting the state
void ChangeTemperatureState::exit(DisplayContext& context) {
    // No cleanup needed for this state
}

// Handle rotary encoder and button input
void ChangeTemperatureState::handleButtonInput(DisplayContext& context, char input) {
  switch(input) {
  case 'w': 
    context.temperature_threshold += 1.0;
    drawTemperatureThreshold(context);
    resetTimeout();
    break;
  case 's': 
    context.temperature_threshold -= 1.0;
    drawTemperatureThreshold(context);
    resetTimeout();
    break;
  case 'f':        
    context.saveSettings();
    context.setState(new HomeScreen());
    break;
  default:
    break;
  }
}

// Draw the screen title
void ChangeTemperatureState::drawTitle() {
    drawText(10, 10, "Adjust Temp Threshold", 1, TEXT_FONT, ST77XX_WHITE);
}

// Display the current temperature threshold
void ChangeTemperatureState::drawTemperatureThreshold(DisplayContext& context) {
    char buffer[10];
    dtostrf(context.temperature_threshold, 3, 1, buffer);
    int nullPos =  0;
    while(buffer[nullPos] != '\0') nullPos++; // finding last position
    // appending 'C'
    if (nullPos + 1 <= 10) { // if smaller than buffer size
        buffer[nullPos] = 'C';
        buffer[nullPos + 1] = '\0';
    }
    tft.fillRect(20, 60, SCREEN_WIDTH, 60, ST77XX_BLACK);    // Clear the area where the threshold value is displayed
    drawText(60, 80, buffer, 1, NUMERIC_FONT, ST77XX_ORANGE);

   // Display user instructions
    drawText(10, 135, "Press the knob to save.", 1, TEXT_FONT, ST77XX_WHITE);
}

void ChangeTemperatureState::checkInactivityTimeout(DisplayContext& context) {
  if (millis() - lastActivityTime > INACTIVITY_TIMEOUT_MS) {
    context.setState(new HomeScreen());
  }
}

void inline ChangeTemperatureState::resetTimeout() {
  lastActivityTime = millis();
}