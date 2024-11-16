#include "display/screens/home_screen_state.hpp"
#include "display/display_context.hpp"
#include "display/screens/settings_screen_state.hpp"
#include "display/icons.hpp"


HomeScreen::HomeScreen() {}

void HomeScreen::init(DisplayContext& context) {
    progressBarColor = PROGRESS_BAR_DEFAULT_COLOR;
    tft.fillScreen(ST77XX_BLACK);
    drawTemperatureBox();
    drawTimeBox();
    drawProgressBarOutline();
    checkTempSensor();
    Serial.println("[Log] MAX6675 is connected!");
    setIcons();
}

void HomeScreen::update(DisplayContext& context) {
    tempSensor.begin();
    currentTime = millis();
    getTemperature();
    updateTimers(context);
    updateLiveData(context);
    updateIcons(context);
    updateProgressBar(context);
    // save setting every 5 seconds
    if (currentTime - lastSavedTime > 5000) {
        context.saveSettings();
        lastSavedTime = currentTime;
    }
}

void HomeScreen::exit(DisplayContext& context) {
    // Cleanup or reset actions if needed
}

void HomeScreen::handleButtonInput(DisplayContext& context, char input) {
    if (input == 'f') {
        context.setState(new SettingsScreen());
    }
}

// Helper Functions
void HomeScreen::drawTemperatureBox() {
    tft.fillRect(TEMP_BOX_X , TEMP_BOX_Y, TEMP_BOX_WIDTH, TEMP_BOX_HEIGHT, TEMP_BOX_DEFAULT_COLOR);
    drawText(TEMP_BOX_X , TEMP_BOX_Y + 5, "Temp:", 1, TEXT_FONT, TEMP_TITLE_COLOR);
}

void HomeScreen::drawTimeBox() {
    tft.fillRect(TIME_BOX_X , TIME_BOX_Y, TEMP_BOX_WIDTH, TEMP_BOX_HEIGHT, TIME_BOX_DEFAULT_COLOR);
    drawText(TIME_BOX_X , TIME_BOX_Y + 10, "Time:", 1, TEXT_FONT, TIME_TITLE_COLOR);
}

void HomeScreen::drawProgressBarOutline() {
    tft.drawRect(PROGRESS_BAR_X, PROGRESS_BAR_Y, PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT, ST77XX_WHITE);
}

void HomeScreen::getTemperature() {
    if (currentTime - thermocoupleLastUpdatedTime > 500) {
        temperature = tempSensor.readTemperature();
        checkTempSensor();
        thermocoupleLastUpdatedTime = currentTime;
    }
}

void HomeScreen::updateTimers(DisplayContext& context) {
  if (isTempSensorWorking) {
    if (temperature >= context.temperature_threshold) {
        context.timerRunning = true;
        context.timeElapsed += currentTime - context.lastUpdateTime;
        thermometerIcon.iconColor = progressBarColor;
        hourglassIcon.iconColor = TIME_ICON_OPERATING_COLOR;
    } else {
        context.timerRunning = false;
        thermometerIcon.iconColor = TEMP_ICON_DEFAULT_COLOR;
        hourglassIcon.iconColor = TIME_ICON_DEFAULT_COLOR;
    }
    context.lastUpdateTime = currentTime;
  }
}

void HomeScreen::updateLiveData(DisplayContext& context) {
  // update temp
  tft.fillRect(TEMP_BOX_X + TEMP_BOX_WIDTH, TEMP_BOX_Y, 
    SCREEN_WIDTH - TEMP_BOX_X - TEMP_BOX_WIDTH - 2, TEMP_BOX_HEIGHT, TEMP_BOX_DEFAULT_COLOR);
  char buffer[10];
  dtostrf(temperature, 4, 2, buffer); // float to string
  int nullPos =  0;
  while(buffer[nullPos] != '\0') nullPos++; // finding last position
  if (nullPos + 1 <= 10) { // if smaller than buffer size
    buffer[nullPos] = 'C';  // appending 'C'
    buffer[nullPos + 1] = '\0';
  }
  drawText(TEMP_BOX_X + TEMP_BOX_WIDTH + 10, TEMP_BOX_Y + 10, buffer, 1, NUMERIC_FONT, tempTextColor);
  
  // update time
  tft.fillRect(TIME_BOX_X + TEMP_BOX_WIDTH, TIME_BOX_Y, 
    SCREEN_WIDTH - TEMP_BOX_X - TEMP_BOX_WIDTH - 2, TEMP_BOX_HEIGHT, TIME_BOX_DEFAULT_COLOR);

  formatElapsedTime(context.timeElapsed, buffer, sizeof(buffer));
  drawText(TIME_BOX_X + TEMP_BOX_WIDTH + 10, TIME_BOX_Y + 10, buffer, 1, NUMERIC_FONT, timeTextColor);
}

bool HomeScreen::checkTempSensor() {
  if (isnan(temperature)) {
      thermometerIcon.iconColor = TEMP_ICON_WARNING_COLOR;
      isTempSensorWorking = false;
  } else {
      isTempSensorWorking = true;
  }
  return isTempSensorWorking;
}

void HomeScreen::updateProgressBar(DisplayContext& context) {
  float progressRatio = static_cast<float>(context.timeElapsed) / static_cast<float>(context.time_threshold);
  if(progressRatio >= 1.0f){
    handleProgressBarEnd();
  } else {
    int filledWidth = static_cast<int>(progressRatio * (PROGRESS_BAR_WIDTH - 4));
    updateProgressBarColor(progressRatio);
    renderProgressBar(filledWidth);
    if (progressRatio > 0.25) {
      char buffer[5];
      snprintf(buffer, sizeof(buffer), "%d%%", static_cast<int>(std::floor(progressRatio * 100)));
      drawText(PROGRESS_BAR_X + filledWidth - 75, PROGRESS_BAR_Y + 10, buffer, 1, NUMERIC_FONT,ST77XX_WHITE);
  }
  }
}

void HomeScreen::updateProgressBarColor(float progressRatio) {
    // Clamp the progress value between 0.0 and 1.0
    if (progressRatio < 0.0f) {
        progressRatio = 0.0f;
    } else if (progressRatio > 1.0f) {
        progressRatio = 1.0f;
    }
    uint8_t red, green;
    if (progressRatio <= 0.5f) {
        // Transition from red to yellow
        green = 255; // Red stays at 255
        red = (uint8_t)(progressRatio * 2 * 255); // Green increases from 0 to 255
    } else {
        // Transition from yellow to green
        green = (uint8_t)((1.0f - progressRatio) * 255 * 2); // Red decreases from 255 to 0
        red = 255; // Red stays at 255
    }
    // Convert to RGB565 format
    progressBarColor = ((red >> 3) << 11) | ((green >> 2) << 5) | (0); // Blue is always 0
}

void HomeScreen::renderProgressBar(int filledWidth) {
    tft.fillRect(PROGRESS_BAR_X + 2, PROGRESS_BAR_Y + 2, filledWidth, PROGRESS_BAR_HEIGHT - 4, progressBarColor);
}

void HomeScreen::handleProgressBarEnd() {
  if (currentTime - progressBarLastTime > 500) {
    progressBarLastTime = currentTime;
    timesUpToggleFlag = !timesUpToggleFlag;
  }
  if (timesUpToggleFlag) {
    progressBarColor = ST77XX_RED;
    renderProgressBar(PROGRESS_BAR_WIDTH - 4);
  } else {
    drawText(PROGRESS_BAR_X + 25, PROGRESS_BAR_Y + 2 + 6, 
      "Time's up!!!", 0, TEXT_FONT,ST77XX_WHITE);
  }
}

void HomeScreen::formatElapsedTime(unsigned long millis, char* buffer, size_t bufferSize) {
    unsigned long seconds = millis / 1000;
    unsigned long minutes = seconds / 60;
    seconds %= 60;
    snprintf(buffer, bufferSize, "%lu:%02lu", minutes, seconds);
}

void HomeScreen::updateIcons(DisplayContext& context){
  if(context.timerRunning) {
  } else {
    hourglassIcon.frame=0;
  }
  hourglassIcon.animate(currentTime, 0);
  thermometerIcon.animate(currentTime, 0);
}

void HomeScreen::setIcons() {
  hourglassIcon.x = 0;
  hourglassIcon.y = 60;
  hourglassIcon.iconColor = TEMP_ICON_DEFAULT_COLOR;
  thermometerIcon.x = 0;
  thermometerIcon.y = 2;
  thermometerIcon.iconColor = TEMP_ICON_DEFAULT_COLOR;
}