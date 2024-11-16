#pragma once
#include "display/display_context.hpp"


// Forward declaration to avoid circular dependencies
class HomeScreen;

class ChangeTemperatureState : public DisplayState {
public:
    // Lifecycle methods
    void init(DisplayContext& context) override;
    void update(DisplayContext& context) override;
    void exit(DisplayContext& context) override;
    // Handle user input
    void handleButtonInput(DisplayContext& context, char input) override;

private:
    unsigned long lastActivityTime;
    
    // Helper methods
    void drawTitle();
    void drawTemperatureThreshold(DisplayContext& context);
    void resetTimeout();
    void checkInactivityTimeout(DisplayContext& context);
    const GFXfont * TEXT_FONT = &FreeSansBoldOblique12pt7b;
    const GFXfont * NUMERIC_FONT = &FreeMonoBoldOblique24pt7b;
};