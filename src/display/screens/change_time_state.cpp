#include "display/screens/change_time_state.hpp"
#include "tft_display.hpp"

// Initialize the screen with the time adjustment interface
void ChangeTimeState::init(DisplayContext& context) {
    tft.fillScreen(ST77XX_BLACK);
    drawTitle();
    drawTimeThreshold(context);
    lastActivityTime = millis();
}

// No continuous updates are required in this state
void ChangeTimeState::update(DisplayContext& context) {
    checkInactivityTimeout(context);
}

// Perform any necessary cleanup before exiting the state
void ChangeTimeState::exit(DisplayContext& context) {
    // No cleanup needed for this state
}

// Handle rotary encoder and button input
void ChangeTimeState::handleButtonInput(DisplayContext& context, char input) {
  int value = round(context.time_threshold/60000);
  switch (input)
  {
  case 'w':
    context.time_threshold =  (value + 1)*60000;  // Increase the time threshold by 1 minute
    drawTimeThreshold(context);      
    resetTimeout();
    break;
  case 's':
    context.time_threshold = (value < 1 ?  0 : (value - 1)*60000); // Decrease the time threshold by 1 minute
    drawTimeThreshold(context);
    resetTimeout();
    break;
  case 'f': // Return to the HomeScreen when the button is pressed
    context.saveSettings();
    context.setState(new HomeScreen());
    break;
  default:
    break;
  }
}

// Draw the screen title
void ChangeTimeState::drawTitle() {
  drawText(10, 20, "Adjust Time Threshold", 1, TEXT_FONT, ST77XX_WHITE);
}

// Display the current time threshold
void ChangeTimeState::drawTimeThreshold(DisplayContext& context) {
    char buffer[10];
    formatElapsedTime(context.time_threshold, buffer, sizeof(buffer));

    // Clear the area where the threshold value is displayed
    tft.fillRect(20, 60, SCREEN_WIDTH, 60, ST77XX_BLACK);

    // Display the updated time threshold
    drawText(50, 80, buffer, 1, NUMERIC_FONT, ST77XX_ORANGE);

    // Display user instructions
    drawText(10, 135, "Press the knob to save.", 1, TEXT_FONT, ST77XX_WHITE);
}

// Format elapsed time in milliseconds into a human-readable string
void ChangeTimeState::formatElapsedTime(unsigned long millis, char* buffer, size_t bufferSize) {
    unsigned long seconds = millis / 1000;
    unsigned long minutes = seconds / 60;
    snprintf(buffer, bufferSize, "%lu min.", minutes);
}


void ChangeTimeState::checkInactivityTimeout(DisplayContext& context){
  if (millis() - lastActivityTime > INACTIVITY_TIMEOUT_MS) {
    context.setState(new HomeScreen());
  }
}

void inline ChangeTimeState::resetTimeout() {
  lastActivityTime = millis();
}