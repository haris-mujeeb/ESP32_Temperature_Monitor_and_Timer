#include "ezButton.h"
#include "EC11.hpp"

// Rotary Encoder Pins
#define ROTARY_PIN_A  27  // Signal pin A
#define ROTARY_PIN_B   26  // Signal pin B
#define ROTARY_PIN_SW   25  // Push button pin

constexpr int DEBOUNCE_TIME_1 = 200;
constexpr int DEBOUNCE_TIME_2 = 40;

extern ezButton button;
extern EC11 encoder;
