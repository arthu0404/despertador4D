#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include <RotaryEncoder.h>
#include <OneButton.h>

// Lista de ações possíveis que o menu vai entender
enum EncoderAction {
    ENC_NONE,  // Nada aconteceu
    ENC_NEXT,  // Girou para a Direita
    ENC_PREV,  // Girou para a Esquerda
    ENC_CLICK,  // Clicou no botão
    ENC_LONG_CLICK, // Clicou por mais tempo no botão
};

class AppEncoder {
public:
    AppEncoder(uint8_t clkPin, uint8_t dtPin, uint8_t swPin);
    void begin();
    void tick(); 
    
    EncoderAction getAction();

private:
    RotaryEncoder _encoder;
    OneButton _button;
    int _lastPosition;
    
    bool _wasClicked;
    bool _wasLongClicked; 

    static void handleClick(void *ptr);
    static void handleLongPress(void *ptr);
};

#endif