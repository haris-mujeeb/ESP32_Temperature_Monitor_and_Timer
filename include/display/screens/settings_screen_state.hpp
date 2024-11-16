#pragma once
#include <stdint.h>
#include "HardwareSerial.h"
#include "esp32-hal.h"
#include "display/display_context.hpp"


// Menu settings
constexpr int MENU_ITEM_HEIGHT = ((SCREEN_HEIGHT)/4) - 4;
constexpr uint16_t SELECTED_COLOR = ST77XX_WHITE;
constexpr uint16_t UNSELECTED_COLOR = 0x8410;


typedef enum {
    MENU_ITEM_BACK,
    MENU_ITEM_CHANGE_TEMP,
    MENU_ITEM_CHANGE_TIME,
    MENU_ITEM_RESET_TIMER,
    MENU_ITEM_COUNT
} MenuItems;


class SettingsScreen : public DisplayState {
public:
  void init(DisplayContext& context) override;
  void update(DisplayContext& context) override;
  void exit(DisplayContext& context) override;
  void handleButtonInput(DisplayContext& context, char input) override;
private:
  const char* menuItems[MENU_ITEM_COUNT] = {"Back", "Change Temp.", "Change Time", "Reset Timer"};
  int selectedIndex = 0;
  unsigned long lastActivityTime;
  void drawMenu();
  void drawMenuItem(int index, bool isSelected);
  void moveSelectionUp(); 
  void moveSelectionDown();
  void selectCurrentOption(DisplayContext& context);
  void checkInactivityTimeout(DisplayContext& context);
  void resetTimeout();
  const GFXfont * TEXT_FONT = &FreeSansBoldOblique18pt7b;
  const GFXfont * NUMERIC_FONT = &FreeMonoBoldOblique18pt7b;
};