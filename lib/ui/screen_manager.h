#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "screen.h"

class ScreenManager {
public:
    ScreenManager();

    // Muda a tela ativa
    void changeScreen(Screen* newScreen);

    // Repassa o comando de desenho para a tela ativa
    void draw(Display* display);

    // Repassa o comando do encoder para a tela ativa
    void handleInput(EncoderAction action);

private:
    Screen* _currentScreen;
};

#endif