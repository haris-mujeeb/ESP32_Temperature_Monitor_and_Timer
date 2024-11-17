# ESP32 Temperature Monitor and Timer
A ESP32 based Temperture monitor and timer with ST7789 TFT Display

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
# How to run:
This project can be build and uploaded to the ESP32 (or Arduino) using PlatformIO:

### 1. **Build the Project**
To compile the project:  
```bash
pio run
```

### 2. **Upload the Firmware (Optional)**
To build and upload the firmware to the board:  
```bash
pio run --target upload
```

### 3. **Monitor Serial Output**
To open the serial monitor:  
```bash
pio device monitor
```

### 4. **Combined Build and Monitor** (additional)
If you want to build, upload, and monitor in sequence:  
```bash
pio run --target upload && pio device monitor
```

### Common Serial Monitor Options (additional)
You can specify the baud rate (this project uses 9600):  
```bash
pio device monitor --baud 9600
```
