#pragma once

#include "display/display_context.hpp"
#include "display/screens/home_screen_state.hpp"


// Forward declaration to avoid circular dependencies
class HomeScreen;

class ChangeTimeState : public DisplayState {
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
  void drawTimeThreshold(DisplayContext& context);
  void formatElapsedTime(unsigned long millis, char* buffer, size_t bufferSize);
  void checkInactivityTimeout(DisplayContext& context);
  void resetTimeout();
  const GFXfont * TEXT_FONT = &FreeSansBoldOblique12pt7b;
  const GFXfont * NUMERIC_FONT = &FreeMonoBoldOblique24pt7b;
};
