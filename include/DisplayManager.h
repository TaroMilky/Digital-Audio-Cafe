#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h> // Required for Hardware SPI

// Screen Dimensions
#define S_WIDTH  128
#define S_HEIGHT 128

// Colors (16-bit 5-6-5 format)
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Pin Definitions
#define SCLK_PIN 6
#define MOSI_PIN 7
#define DC_PIN   4
#define CS_PIN   5
#define RST_PIN  15

class DisplayManager {
private:
    // Pointer to the driver object
    Adafruit_SSD1351* tft = nullptr;
    
    // To track UI updates
    int _lastDrawnVolume = -1;

public:
    void init();
    void drawInterface();
    void updateVolume(int volume);
    void drawTest();
};

#endif