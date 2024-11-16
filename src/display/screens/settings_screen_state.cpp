#pragma once
#include <stdint.h>
#include "HardwareSerial.h"
#include "esp32-hal.h"
#include "display/display_context.hpp"
#include "display/screens/settings_screen_state.hpp"
#include "display/screens/home_screen_state.hpp"
#include "display/screens/change_temp_state.hpp"
#include "display/screens/change_time_state.hpp"


void SettingsScreen::init(DisplayContext& context) {
  tft.fillScreen(ST77XX_BLACK);
  lastActivityTime = millis();
  drawMenu();
}

void SettingsScreen::update(DisplayContext& context) {
  checkInactivityTimeout(context);
}

void SettingsScreen::exit(DisplayContext& context) {}

void SettingsScreen::handleButtonInput(DisplayContext& context, char input) {
  switch (input) {
    case 'w':
      moveSelectionUp();
      drawMenu();
      resetTimeout();
      break;
    case 's':
      moveSelectionDown();
      drawMenu();
      resetTimeout();
      break;
    case 'f':
      selectCurrentOption(context);
      resetTimeout();
      break;
    default:
      break;
  }

}

void SettingsScreen::drawMenu() {
  tft.fillScreen(ST77XX_BLACK);
  for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
    drawMenuItem(i, i == selectedIndex);
  }
}

void SettingsScreen::drawMenuItem(int index, bool isSelected) {
  int y = 5 + index * (MENU_ITEM_HEIGHT + 1);
  tft.fillRect(5, y, SCREEN_WIDTH - 10, MENU_ITEM_HEIGHT - 5, isSelected ? SELECTED_COLOR : UNSELECTED_COLOR);
  uint16_t fontColor = isSelected ? ST77XX_BLACK : ST77XX_WHITE;
  drawText(15, y + 3, menuItems[index], 1, TEXT_FONT, fontColor);
}

void SettingsScreen::moveSelectionUp() {
  selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : MENU_ITEM_COUNT - 1;
}

void SettingsScreen::moveSelectionDown() {
  selectedIndex = (selectedIndex < MENU_ITEM_COUNT - 1) ? selectedIndex + 1 : 0;
}

void SettingsScreen::selectCurrentOption(DisplayContext& context) {
  switch(selectedIndex) {
    case MENU_ITEM_BACK:
      context.setState(new HomeScreen());
      break;
    case MENU_ITEM_CHANGE_TEMP:
      context.setState(new ChangeTemperatureState());
      break;   
    case MENU_ITEM_CHANGE_TIME:
      context.setState(new ChangeTimeState());
      break;
    case MENU_ITEM_RESET_TIMER:
      context.timeElapsed = 0;
      context.saveSettings();
      context.setState(new HomeScreen());
      break;                       
  }
}

void SettingsScreen::checkInactivityTimeout(DisplayContext& context) {
  if (millis() - lastActivityTime > INACTIVITY_TIMEOUT_MS) {
    context.setState(new HomeScreen());
  }
}

void inline SettingsScreen::resetTimeout() {
  lastActivityTime = millis();
}