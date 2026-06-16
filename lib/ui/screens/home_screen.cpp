#include "home_screen.h"
#include "../screen_manager.h"
#include "gps_screen.h" 

extern GPSScreen gpsScreen;

HomeScreen::HomeScreen() {
    _selectedTab = 0;
}

void HomeScreen::onEnter() {
    _selectedTab = 0; 
}

void HomeScreen::draw(Display* display) {
    display->clear();
    
    display->drawFrame(85, 0, 43, 14); 
    display->printText("12:00", 92, 10); // Hora fixa por enquanto

    display->drawFrame(0, 0, 80, 40); 
    display->printText("Status:", 5, 12);
    display->printText("Aguardando", 5, 24);
    display->printText("GPS...", 5, 34);

    display->drawFrame(0, 42, 128, 22); 
    display->drawFrame(2, 44, 124, 18); 

    display->drawMenuItem("GPS", 12, 57, _selectedTab == 0);
    display->drawMenuItem("CONFIG", 65, 57, _selectedTab == 1);
    
    display->update();
}

void HomeScreen::handleInput(EncoderAction action, ScreenManager* manager) {
    if (action == ENC_NEXT) {
        _selectedTab = (_selectedTab + 1) % 2; 
    } 
    else if (action == ENC_PREV) {
        _selectedTab = (_selectedTab == 0) ? 1 : 0;
    } 
    else if (action == ENC_CLICK) {
        if (_selectedTab == 0) {
            manager->changeScreen(&gpsScreen);
            Serial.println("Abrindo GPS...");
        } else {
            // manager->changeScreen(&configScreen);
            Serial.println("Abrindo Config...");
        }
    }
    else if (action == ENC_CLICK) {
        if (_selectedTab == 0) {
            manager->changeScreen(&gpsScreen); 
        } else {
            Serial.println("Abrindo Config...");
        }
    }
}