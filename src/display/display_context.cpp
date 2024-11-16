#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>       
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <math.h>
#include <EEPROM.h>

// Define memory addresses for each variable
constexpr int MAGIC_NUMBER_ADDR = 0;
constexpr int TEMP_THRESHOLD_ADDR = MAGIC_NUMBER_ADDR + sizeof(uint32_t);
constexpr int TIME_THRESHOLD_ADDR = TEMP_THRESHOLD_ADDR + sizeof(float);
constexpr int TIME_ELAPSED_ADDR = TIME_THRESHOLD_ADDR + sizeof(unsigned long);
// Define a unique magic number
constexpr uint32_t MAGIC_NUMBER = 0xABCD1234;

class DisplayContext; // Forward declaration

// State Interface
class DisplayState {
  public:
    virtual void init(DisplayContext& context) = 0;
    virtual void update(DisplayContext& context) = 0;
    virtual void exit(DisplayContext& context) = 0;
    virtual void handleButtonInput(DisplayContext& context, char input){};
    virtual ~DisplayState() {}
};


// Context Class
class DisplayContext {
private:
  DisplayState* currentState;

public:
  float temperature_threshold;
  float time_threshold;
  unsigned long timeElapsed;
  unsigned long lastUpdateTime = 0;
  bool timerRunning = 0;

  DisplayContext(DisplayState* initialState) : currentState(nullptr) {
    setState(initialState);
  }

  void setState(DisplayState* state) {
    if (currentState) {
      currentState->exit(*this);
      delete currentState;
    }
    currentState = state;
    currentState->init(*this);
  }

  void update() {
    if (currentState) { currentState->update(*this); }
  }

  void handleButtonInput(char input){
    if (currentState) { currentState->handleButtonInput(*this, input); }
  }

  void saveSettings() {
    // Write the magic number to indicate valid saved data
    EEPROM.put(MAGIC_NUMBER_ADDR, MAGIC_NUMBER);
    
    // Write values to EEPROM
    EEPROM.put(TEMP_THRESHOLD_ADDR, temperature_threshold);
    EEPROM.put(TIME_THRESHOLD_ADDR, time_threshold);
    EEPROM.put(TIME_ELAPSED_ADDR, timeElapsed);

    // Commit changes to persist
    if (!EEPROM.commit()) {
      Serial.println("[Warn] Failed to commit EEPROM changes");
    } else {
      Serial.println("[Log] Settings saved to EEPROM");
    }
  }

  bool loadSettings() {
    uint32_t magic;
    EEPROM.get(MAGIC_NUMBER_ADDR, magic);
    if (magic == MAGIC_NUMBER) { // Magic number matches; load saved values
      EEPROM.get(TEMP_THRESHOLD_ADDR, temperature_threshold);
      EEPROM.get(TIME_THRESHOLD_ADDR, time_threshold);
      EEPROM.get(TIME_ELAPSED_ADDR, timeElapsed);
      return true;
    } else { // Magic number mismatch; settings not saved
      return false;
    }
  }
};