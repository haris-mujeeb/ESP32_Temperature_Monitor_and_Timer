#include "gui/gui.hpp"

// Initialize the static member
GUI* GUI::instance = nullptr;

// Constructor
GUI::GUI(unsigned int frameRate) : FRAME_RATE(frameRate) {
    // Set the static pointer to this instance
    instance = this;
    currentTime = millis();

    initializeHardware();
    
    // Initialize Rotary Encoder
    initializeEncoder();

    // Initialize TFT display
    initializeTFT();

    // Initialize the Display Context with the HomeScreen state
    displayContext = new DisplayContext(new HomeScreen());
    // pinMode(ROTARY_PIN_B, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(BOOT_PIN), handleENPinPress, FALLING); // Trigger on falling edge
    // delay(2000);

    // Load settings or set defaults
    loadSettings();

    delay(500);  // Allow initialization
}

 GUI::~GUI(){
    delete displayContext; // Free allocated memory
 }

// Main run loop
void GUI::run() {
    currentTime = millis();
    updateScreen();
    displayContext->handleButtonInput(getInput());
}

void GUI::loadSettings() {
    if (displayContext->loadSettings()) {
        Serial.println("[Log] Saved data successfully loaded.");
    } else {
        Serial.println("[Warn] Failed to load any saved data. Setting default values.");
        displayContext->temperature_threshold = 100;  // 100°C default threshold
        displayContext->time_threshold = 20 * 1000;   // 20 seconds
        displayContext->timeElapsed = 0;
    }
}

void GUI::updateScreen(){
    // Update the display context based on frame rate
    if (currentTime - lastFrameTime >= 1000 / FRAME_RATE) {
        displayContext->update();
        lastFrameTime = currentTime;
    }
}


char GUI::getInput() {
  char input = '\0';
  button.loop(); // Call the loop function for the button
  if (button.isPressed()) {
      input = 'f';
      Serial.println("[Log] The button is pressed");    
  }
  EC11Event e;
  if (encoder.read(&e)) {  
      if (e.type == EC11Event::StepCW) {
          input = 'w';
          Serial.println("[Log] The encoder is rotated CCW");
      } else {
          input = 's';
          Serial.println("[Log] The encoder is rotated CW");
      }
}

  // Handle button or encoder inputs from Serial Monitor
  if (Serial.available()) {
      input = Serial.read();
  }

  return input;
}

void IRAM_ATTR GUI::handleENPinPress() {
    if (instance->displayContext) {
        instance->displayContext->clearEEPROM(); // Call the clearEEPROM method
    }
}