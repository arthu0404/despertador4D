#include "display.h"
#include "assets.h"

Display::Display(uint8_t sclPin, uint8_t sdaPin)
    : _u8g2(U8G2_R0, U8X8_PIN_NONE, sclPin, sdaPin) {}

bool Display::begin(uint8_t address) {
    _u8g2.setI2CAddress(address * 2);
    return _u8g2.begin();
}

void Display::clear() { _u8g2.clearBuffer(); }
void Display::update() { _u8g2.sendBuffer(); }

// === FUNÇÕES DE DESENHO GEOMÉTRICO ===
void Display::drawFrame(int x, int y, int w, int h) {
    _u8g2.drawFrame(x, y, w, h);
}

void Display::drawRFrame(int x, int y, int w, int h, int r) {
    _u8g2.drawRFrame(x, y, w, h, r);
}

void Display::drawLine(int x0, int y0, int x1, int y1) {
    _u8g2.drawLine(x0, y0, x1, y1);
}

void Display::drawBox(int x, int y, int w, int h) {
    _u8g2.drawBox(x, y, w, h);
}


void Display::printText(const String& text, int x, int y, const uint8_t* font) {
    _u8g2.setFont(font);
    _u8g2.setCursor(x, y);
    _u8g2.print(text);
}

void Display::drawMenuItem(const String& text, int x, int y, bool isSelected) {
    if (isSelected) {
        printText(">", x - 2, y); 
        printText(text, x + 5, y); 
    } else {
        printText(text, x, y);
    }
}

// === TELA DE BOOT ===
void Display::showBootScreen() {
    clear();
    
    int x_pos = (128 - BOOT_LOGO_WIDTH) / 2;
    int y_pos = 0;

    _u8g2.drawXBMP(x_pos, y_pos, BOOT_LOGO_WIDTH, BOOT_LOGO_HEIGHT, boot_logo);
    
    update();
}


// === TELA HOME ===
void Display::showHomeScreen(const String& currentTime, uint8_t selectedTab) {
    clear();
    _u8g2.setFont(u8g2_font_5x8_tr);
    
    // Relógio - Canto Superior Direito
    _u8g2.drawFrame(85, 0, 43, 14);
    printText(currentTime, 92, 10);

    // caixa de Status - Canto Superior Direito
    _u8g2.drawFrame(0, 0, 80, 40); 
    printText("Status:", 5, 12);
    printText("Aguardando", 5, 24);
    printText("GPS...", 5, 34);

    // Caixa de Menus 
    _u8g2.drawFrame(0, 42, 128, 22);
    _u8g2.drawFrame(2, 44, 124, 18); 

    drawMenuItem("GPS", 12, 57, selectedTab == 0);
    drawMenuItem("CONFIG", 65, 57, selectedTab == 1);
    
    update();
}


// === TELA GPS ===
void Display::showGPSScreen(uint8_t subTab, bool isConnected, const String& statusText, const String& searchTime, uint8_t sats, double lat, double lng, double alt, double speed, bool hasDest, const String& destName, const String& distance, const String& currentTag) {
    clear();
    
    _u8g2.drawBox(0, 0, 128, 12);
    _u8g2.setDrawColor(0);
    printText("GPS MENU", 2, 9);
    printText("[" + statusText + "]", 78, 9); 
    _u8g2.setDrawColor(1);
    
    _u8g2.drawLine(40, 14, 40, 64);
    drawMenuItem("Locais", 4, 26, subTab == 0);
    drawMenuItem("Status", 4, 41, subTab == 1);
    drawMenuItem("Marcar", 4, 56, subTab == 2);

    int contentX = 46;
    
    if (subTab == 0) {
        printText("Local Alvo:", contentX, 23);
        if (hasDest) {
            printText(destName, contentX, 36);
            printText("Dist: " + distance, contentX, 50);
        } else {
            printText("Clique p/ escolher", contentX, 36);
        }
    } 
    else if (subTab == 1) {
        printText("Mod: " + statusText, contentX, 22);
        
        if (!isConnected && searchTime != "") {
            printText("Tempo: " + searchTime, contentX, 36);
        } else {
            printText("Sat: " + String(sats), contentX, 32);
            printText("Alt: " + String(alt, 0) + "m", contentX, 42);
            printText("Vel: " + String(speed, 0) + "km/h", contentX, 52);
            String coords = String(lat, 2) + "," + String(lng, 2);
            printText(coords, contentX, 62);
        }
    } 
    else if (subTab == 2) {
        printText("Salvar Ponto?", contentX, 22);
        printText("Tag: [" + currentTag + "]", contentX, 38);
        
        _u8g2.drawRFrame(contentX, 46, 60, 14, 2);
        printText("CONFIRMAR", contentX + 6, 56); 
    }
    update();
}
