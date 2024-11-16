#include "hardware_config.hpp"

// Create object for ST7789
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Create the TemperatureSensor object
TemperatureSensor tempSensor = TemperatureSensor(MAX6675_CS_PIN, MAX6675_SCK_PIN, MAX6675_MISO_PIN);

// Create ezButton object for the switch pin
ezButton button(ROTARY_PIN_SW); 

// Create EC11 object for the rotary encoder
EC11 encoder;

// Initialize hardware components
void initializeHardware() {

    // Initialize EEPROM
    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("[Warn] Failed to initialize EEPROM: Data will not be saved.");
    } else {
        Serial.println("[Log] EEPROM initialized successfully!");
    }

    tempSensor.begin();  // Initialize the MAX6675 sensor
    if (tempSensor.isSensorAvailable()) {
        Serial.println("Sensor is available.");
    } else {
        Serial.println("[Error] Sensor is not available!");
    }


    // Initialize TFT Screen
    tft.init(SCREEN_HEIGHT, SCREEN_WIDTH);
    tft.setRotation(1);  // Set the rotation of the TFT display
    // tft.setBrightness(MAX_BRIGHTNESS);  // Set screen brightness

    Serial.println("[Log] Hardware initialization completed.");
}


void IRAM_ATTR handleEncoderInterrupt(){
  encoder.checkPins(digitalRead(ROTARY_PIN_A), digitalRead(ROTARY_PIN_B));
}


void initializeEncoder() {
    // button.setDebounceTime(50); // Set debounce time for button
    pinMode(ROTARY_PIN_A, INPUT_PULLUP);
    pinMode(ROTARY_PIN_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), handleEncoderInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), handleEncoderInterrupt, CHANGE);
}