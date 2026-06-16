#ifndef SCREEN_H
#define SCREEN_H

#include "display.h"
#include "encoder.h"

class ScreenManager; 

class Screen {
public:
    virtual ~Screen() {} 
    virtual void onEnter() {} 
    virtual void draw(Display* display) = 0; 
    virtual void handleInput(EncoderAction action, ScreenManager* manager) = 0; 
};

#endif