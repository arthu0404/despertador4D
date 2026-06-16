#include "screen_manager.h"

ScreenManager::ScreenManager() {
    _currentScreen = nullptr;
}

void ScreenManager::changeScreen(Screen* newScreen) {
    _currentScreen = newScreen;
    if (_currentScreen != nullptr) {
        _currentScreen->onEnter(); 
    }
}

void ScreenManager::draw(Display* display) {
    if (_currentScreen != nullptr) {
        _currentScreen->draw(display);
    }
}

void ScreenManager::handleInput(EncoderAction action) {
    if (_currentScreen != nullptr && action != ENC_NONE) {
        _currentScreen->handleInput(action, this);
    }
}