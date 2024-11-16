#pragma once
#include <SPI.h>
#include "MAX6675.h"

// MAX6675 Thermocouple Pins
#define MAX6675_CS_PIN  5   // Chip Select Pin
#define MAX6675_SCK_PIN 14  // SPI Clock Pin
#define MAX6675_MISO_PIN 12 // SPI MISO Pin


// Temperature Sensor class for MAX6675
class TemperatureSensor {
public:
    // Constructor: Initializes the MAX6675 object with CS, SCK, and MISO pins
    TemperatureSensor();
    TemperatureSensor(int csPin, int sckPin, int misoPin);

    // Initializes the MAX6675 sensor
    void begin();

    // Reads the current temperature in Celsius
    float readTemperature();

    // Checks if the sensor is available
    bool isSensorAvailable();

private:
    int _csPin;  // Chip select pin
    int _sckPin; // SPI Clock pin
    int _misoPin; // SPI MISO pin
    MAX6675 _sensor;  // MAX6675 sensor object
};

// Create object
extern TemperatureSensor tempSensor;