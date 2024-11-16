#include "gui/temperature_sensor.hpp"

// Constructor initializes the MAX6675 object with CS, SCK, and MISO pins
TemperatureSensor::TemperatureSensor(int csPin, int sckPin, int misoPin)
    : _csPin(csPin), _sckPin(sckPin), _misoPin(misoPin), _sensor(csPin, sckPin, misoPin) {}

void TemperatureSensor::begin() {
    _sensor = MAX6675(_sckPin, _csPin, _misoPin);     // Initialize the SPI interface
}

float TemperatureSensor::readTemperature() {
    float temperature = _sensor.readCelsius(); // Read the temperature in Celsius from the MAX6675 sensor
    if (isnan(temperature)) {
        Serial.println("[Error] Failed to read temperature from MAX6675!");
        return NAN;  // Return NaN if reading fails
    }    
    return temperature;  // Return the valid temperature in Celsius
}

bool TemperatureSensor::isSensorAvailable() {
    // Try reading the temperature to check if the sensor is available
    float temperature = readTemperature();
    return !isnan(temperature);  // Return true if the reading is valid, else false
}
