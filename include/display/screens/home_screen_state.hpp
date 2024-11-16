#pragma once
#include <cstdint>
#include <max6675.h>
#include "display/display_context.hpp"
#include "hardware_config.hpp"


// Forward Declarations
class DisplayContext;
 
// Constants
constexpr int TEMP_BOX_X = 50+2, TEMP_BOX_Y = 2, TEMP_BOX_WIDTH = 100, TEMP_BOX_HEIGHT = 47;
constexpr int TIME_BOX_X = TEMP_BOX_X, TIME_BOX_Y = TEMP_BOX_Y + TEMP_BOX_HEIGHT + 10;
constexpr int PROGRESS_BAR_X = 2, PROGRESS_BAR_Y = TIME_BOX_Y + TEMP_BOX_HEIGHT + 10;
constexpr int PROGRESS_BAR_WIDTH = SCREEN_WIDTH - 10, PROGRESS_BAR_HEIGHT = 48;

// Color definitions
constexpr uint16_t TIME_BOX`_DEFAULT_COLOR = ST77XX_BLACK;
constexpr uint16_t TEMP_BOX_DEFAULT_COLOR = ST77XX_BLACK;
constexpr uint16_t TIME_TITLE_COLOR = 0xfea0; // gold
constexpr uint16_t TEMP_TITLE_COLOR = 0x05ff; // deepskyblue
constexpr uint16_t TIME_ICON_DEFAULT_COLOR = ST77XX_WHITE;
constexpr uint16_t TEMP_ICON_DEFAULT_COLOR = ST77XX_WHITE;
constexpr uint16_t TIME_ICON_OPERATING_COLOR = ST77XX_GREEN ;
constexpr uint16_t TEMP_ICON_OPERATING_COLOR = ST77XX_GREEN;
constexpr uint16_t TEMP_ICON_WARNING_COLOR = ST77XX_RED;
constexpr uint16_t FIRE_ICON_DEFAULT_COLOR = ST77XX_RED;
constexpr uint16_t PROGRESS_BAR_DEFAULT_COLOR = ST77XX_GREEN;

// Thresholds and timings
constexpr float TEMPERATURE_THRESHOLD = 50.0f;
constexpr unsigned long TIME_THRESHOLD = 10000;

// Class Definition
class HomeScreen : public DisplayState {
public:
    HomeScreen();
    ~HomeScreen() override = default;

    void init(DisplayContext& context) override;
    void update(DisplayContext& context) override;
    void exit(DisplayContext& context) override;
    void handleButtonInput(DisplayContext& context, char input) override;

private:
    void drawTemperatureBox();
    void drawTimeBox();
    void drawProgressBarOutline();
    void getTemperature();
    void updateTimers(DisplayContext& context);
    void updateLiveData(DisplayContext& context);
    bool checkTempSensor();
    void formatElapsedTime(unsigned long millis, char* buffer, size_t bufferSize);
    void setIcons();
    void updateIcons(DisplayContext& context);
    void updateProgressBar(DisplayContext& context);
    void updateProgressBarColor(float progressRatio);
    void renderProgressBar(int filledWidth);
    void handleProgressBarEnd();
    void renderProgressPercentage(int filledWidth, float progressRatio);
  

    uint16_t tempTextColor = TEMP_TITLE_COLOR;
    uint16_t tempIconColor = TEMP_ICON_DEFAULT_COLOR;
    uint16_t timeTextColor = TIME_TITLE_COLOR;
    uint16_t progressBarColor = PROGRESS_BAR_DEFAULT_COLOR;
    unsigned long currentTime;
    unsigned long progressBarLastTime = 0;
    unsigned long thermocoupleLastUpdatedTime = 0;
    bool isTempSensorWorking; 
    unsigned long lastSavedTime = 0;
    bool timesUpToggleFlag = false;
    float temperature;
    const GFXfont * TEXT_FONT = &FreeMonoBold18pt7b;
    const GFXfont * NUMERIC_FONT = &FreeMonoBoldOblique18pt7b;
};
