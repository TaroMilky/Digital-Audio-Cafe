#include "DisplayManager.h"

void DisplayManager::init() {
    Serial.println("[Display] Init Hardware SPI...");

    // 1. Configure the ESP32's Hardware SPI Bus
    // Signature: SPI.begin(SCK, MISO, MOSI, SS);
    // MISO = -1 (Screen is write-only)
    // SS   = -1 (CRITICAL: pass -1 so the system driver doesn't lock the CS pin.
    //            The Adafruit library will handle Pin 5 manually.)
    SPI.begin(SCLK_PIN, -1, MOSI_PIN, -1);
    
    // 2. Create the object using the HARDWARE SPI constructor
    // Signature: (width, height, &SPI_POINTER, cs, dc, rst)
    tft = new Adafruit_SSD1351(S_WIDTH, S_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);
    
    if (tft == nullptr) {
        Serial.println("[Display] Allocation Failed");
        return;
    }

    // 3. Start the screen
    tft->begin();

    // 4. Boost Speed (Optional)
    // If the screen looks glitchy, comment this out to use default speed.
    // 20MHz is usually safe.
    tft->setSPISpeed(20000000); 

    tft->setRotation(0); 
    tft->fillScreen(BLACK);
    Serial.println("[Display] Online (HW SPI).");
}

void DisplayManager::drawInterface() {
    if (!tft) return;
    tft->fillScreen(BLACK);
    
    // Header Bar
    tft->fillRect(0, 0, 128, 20, BLUE);
    tft->setTextColor(WHITE);
    tft->setTextSize(1);
    tft->setCursor(15, 6);
    tft->print("DIGITAL AUDIO CAFE");
    
    // Volume Bar Outline
    tft->drawRect(10, 100, 108, 14, WHITE);
}

void DisplayManager::updateVolume(int volume) {
    if (!tft) return;
    if (volume == _lastDrawnVolume) return;
    
    // Calculate bar width (Map 0-100% to 0-104 pixels)
    int barWidth = map(volume, 0, 100, 0, 104);
    
    // Draw Filled Part (Green)
    if (barWidth > 0) tft->fillRect(12, 102, barWidth, 10, GREEN);
    
    // Draw Empty Part (Black) to erase old bar
    if (barWidth < 104) tft->fillRect(12 + barWidth, 102, 104 - barWidth, 10, BLACK);
    
    // Update Number Text (Partial Clear)
    tft->fillRect(50, 85, 40, 10, BLACK); // Erase box
    
    tft->setCursor(50, 85);
    tft->setTextColor(YELLOW);
    tft->print(volume);
    tft->print("%");

    _lastDrawnVolume = volume;
}

void DisplayManager::drawTest() {
    if (!tft) return;
    tft->fillScreen(RED);
    delay(100);
    tft->fillScreen(BLACK);
}