#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include "../screen.h"

class HomeScreen : public Screen {
public:
    HomeScreen();
    
    void onEnter() override;
    void draw(Display* display) override;
    void handleInput(EncoderAction action, ScreenManager* manager) override;

private:
    uint8_t _selectedTab; 
};

#endif