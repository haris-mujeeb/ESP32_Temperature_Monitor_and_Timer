# ESP32 Temperature Monitor and Timer

https://github.com/user-attachments/assets/7d30d928-8f08-4236-9cfe-6035c38b2132

## Components:
- [ESP WROOM 32](https://www.espressif.com/en/producttype/esp32-wroom-32)
- [ST7789 TFT Display](https://github.com/libdriver/st7789)
- [MAX6677 Thermocouple module](https://github.com/adafruit/MAX6675-library)

## Pinout Configuration:
### ST7789 TFT Display:
```c
#define TFT_MOSI 23   //  Master Out Slave In pin
#define TFT_SCLK 18   // Serial Clock Pin
#define TFT_CS 15     // Chip select pin
#define TFT_DC 2      // Data/Command pin
#define TFT_RST 4     // Reset pin
#define TFT_BLK 32    // Backlight (BLK) pin
```

### MAX6675 Thermocouple:
```c
#define MAX6675_CS_PIN  5   // Chip Select Pin
#define MAX6675_SCK_PIN 14  // SPI Clock Pin
#define MAX6675_MISO_PIN 12 // SPI MISO Pin
```

### Rotary Encoder:
```c
#define ROTARY_PIN_A  27  // Signal pin A
#define ROTARY_PIN_B   26  // Signal pin B
#define ROTARY_PIN_SW   25  // Push button pin
```
