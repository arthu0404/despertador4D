#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

class Display {
public:
    Display(uint8_t sclPin, uint8_t sdaPin);
    bool begin(uint8_t address = 0x3C);

    void clear();
    void update();
    
    // Escreve texto
    void printText(const String& text, int x, int y, const uint8_t* font = u8g2_font_5x8_tr);
    
    // Desenha um item de menu
    void drawMenuItem(const String& text, int x, int y, bool isSelected);

    void drawFrame(int x, int y, int w, int h);
    void drawRFrame(int x, int y, int w, int h, int r);
    void drawLine(int x0, int y0, int x1, int y1);
    void drawBox(int x, int y, int w, int h);

    // Funções de interface 
    void showBootScreen();
    void showHomeScreen(const String& currentTime, uint8_t selectedTab);
    void showGPSScreen(uint8_t subTab, bool isConnected, const String& statusText, const String& searchTime, uint8_t sats, double lat, double lng, double alt, double speed, bool hasDest, const String& destName, const String& distance, const String& currentTag);
private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C _u8g2; 
};

#endif