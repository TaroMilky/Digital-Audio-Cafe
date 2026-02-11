#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 38 

#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(115200);
    // Wait for USB (Timeout 3s)
    int t=0; while(!Serial && t<3000) { delay(1); t++; }

    Serial.println("\n--- LED TESTER ---");
    Serial.printf("Testing GPIO %d... Watch the board!\n", LED_PIN);

    pixels.begin();
    pixels.setBrightness(50); // Increased brightness to be sure
}

void loop() {
    // RED
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
    Serial.println("Color: RED");
    delay(500);

    // GREEN
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();
    Serial.println("Color: GREEN");
    delay(500);

    // BLUE
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.show();
    Serial.println("Color: BLUE");
    delay(500);

    // OFF
    pixels.clear();
    pixels.show();
    Serial.println("OFF");
    delay(1000);
}