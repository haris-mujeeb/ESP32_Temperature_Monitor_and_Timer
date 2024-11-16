#include <Arduino.h>
#include <EEPROM.h>
#include "hardware_config.hpp"
#include "display/display_context.hpp"
#include "display/screens/home_screen_state.hpp"

class GUI {
public:
    explicit GUI(unsigned int frameRate = 30); // Constructor
    ~GUI();
    void run(); // Main loop function
    static void IRAM_ATTR handleEncoderInterrupt();
    static void IRAM_ATTR handleENPinPress();

private:
    // Context and timing management
    unsigned long currentTime;
    DisplayContext* displayContext;
    static GUI* instance; // Static pointer to the current instance
    const unsigned int FRAME_RATE;
    unsigned long lastFrameTime = 0;
    unsigned long lastSavedTime = 0;
    unsigned long lastInputTakenTime = 0;
    void loadSettings();
    void updateScreen();   
    char getInput();   
};
