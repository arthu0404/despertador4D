#ifndef GPS_SCREEN_H
#define GPS_SCREEN_H

#include "../screen.h"

class GPSScreen : public Screen {
public:
    GPSScreen();
    
    void onEnter() override;
    void draw(Display* display) override;
    void handleInput(EncoderAction action, ScreenManager* manager) override;

private:
    uint8_t _subTab; 
    bool _isSelecting;    
    uint8_t _localIndex;  
    bool _isSelectingTag; 
    uint8_t _tagIndex;
};
#endif