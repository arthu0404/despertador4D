#include "encoder.h"

AppEncoder::AppEncoder(uint8_t clkPin, uint8_t dtPin, uint8_t swPin)
    : _encoder(clkPin, dtPin, RotaryEncoder::LatchMode::TWO03),
      _button(swPin, true) 
{
    _lastPosition = 0;
    _wasClicked = false;
    _wasLongClicked = false;;
}

void AppEncoder::begin() {
    // Configura o evento de clique do botão
    _button.attachClick(handleClick, this);
    _button.attachLongPressStart(handleLongPress, this);
}

void AppEncoder::tick() {
    // Lê constantemente o estado físico das portas
    _encoder.tick();
    _button.tick();
}

EncoderAction AppEncoder::getAction() {
    if (_wasLongClicked) {
        _wasLongClicked = false;
        return ENC_LONG_CLICK;
    }

    // Verifica se houve clique no botão
    if (_wasClicked) {
        _wasClicked = false; 
        return ENC_CLICK;
    }

    // Verifica se girou
    int currentPosition = _encoder.getPosition();
    if (currentPosition > _lastPosition) {
        _lastPosition = currentPosition;
        return ENC_NEXT;
    } 
    else if (currentPosition < _lastPosition) {
        _lastPosition = currentPosition;
        return ENC_PREV;
    }

    return ENC_NONE;
}

void AppEncoder::handleClick(void *ptr) {
    AppEncoder *instance = (AppEncoder *)ptr;
    instance->_wasClicked = true;
}

void AppEncoder::handleLongPress(void *ptr) {
    AppEncoder *instance = (AppEncoder *)ptr;
    instance->_wasLongClicked = true;
}