#include <ezButton.h>  // Library for handling the push button
#include "EC11.hpp"

#define ROTARY_PIN_A  27  // Clock signal pin
#define ROTARY_PIN_B   26  // Data signal pin
#define ROTARY_PIN_SW   25  // Push button pin

#define DIRECTION_CW 0   // Clockwise direction
#define DIRECTION_CCW 1  // Counter-clockwise direction


ezButton button(ROTARY_PIN_SW); // Create ezButton object for the switch pin

EC11 encoder;


void pinDidChange() {
  encoder.checkPins(digitalRead(ROTARY_PIN_A), digitalRead(ROTARY_PIN_B));
}


void prepare() {
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), pinDidChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), pinDidChange, CHANGE);
}


void setup() {
  Serial.begin(9600);

  // Configure encoder pins as inputs
  pinMode(ROTARY_PIN_A, INPUT_PULLUP);
  pinMode(ROTARY_PIN_B, INPUT_PULLUP);
  prepare();

  button.setDebounceTime(50); // Set debounce time for button
}

void loop() {
  button.loop(); // Call the loop function for the button
  // Check if the button is pressed
  if (button.isPressed()) {
      Serial.println("The button is pressed");
  }

  EC11Event e;
  if (encoder.read(&e)) {  
    if (e.type == EC11Event::StepCW) {
      Serial.println("w");
    } else {
      Serial.println("s");
    }
  // Wait quite some time to demonstrate that we can check for events fairly infrequently and still not miss them.
  delay(200);
  }
}

