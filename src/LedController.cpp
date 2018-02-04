#include "LedController.h"
#include <FastLED.h>

LedController::LedController()
{
  // constructor
}

void LedController::setup()
{
    for (byte led = 0; led < LC_LED_COUNT; led++) {
        _states[led] = stateOff;
        pinMode(_pins[led], OUTPUT);
    }
}

void LedController::fadeEffect()
{
    if (_tick % 3 == 0) {
        _fadeState += _fadeDelta;
        if (_fadeState == 250) {
            _fadeDelta = -4;
        } else if (_fadeState < 4) {
            _fadeDelta = 1;
        }
    }
}

void LedController::flashEffect()
{
    if (_tick % (_flashState ? 10 : 100) == 0) {
        _flashState = !_flashState;
    }
}

void LedController::update()
{
    _tick++;
    fadeEffect();
    flashEffect();

    for (byte led = 0; led < LC_LED_COUNT; led++) {
        switch (_states[led]) {
            case stateOff: 
                digitalWrite(_pins[led], LOW);
                break;
            case stateOn: 
                digitalWrite(_pins[led], HIGH);
                break;
            case stateFade:
                analogWrite(_pins[led], _fadeState);
                break;
            case stateFlash:
                digitalWrite(_pins[led], _flashState);
                break;
        }
    }


}

void LedController::setState(byte ledIndex, LedState state)
{
    _states[ledIndex] = state;
}

void LedController::off()
{
    for (byte pin = 0; pin < LC_LED_COUNT; pin++) digitalWrite(_pins[pin], LOW);
}
