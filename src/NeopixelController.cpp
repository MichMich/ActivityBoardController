#include "NeopixelController.h"
#include <FastLED.h>

NeopixelController::NeopixelController()
{
  // constructor
}

void NeopixelController::setup()
{
    FastLED.addLeds<NEOPIXEL, NC_DATA_PIN>(_leds, NC_NUM_LEDS);
    _rotaryEncoderIndicator = CHSV(255, 255, 255);
    for (byte i = 0; i < NC_NUM_ARCADE_BUTTONS; i++) {
        _arcadeButtonIndicators[i] = CHSV(255, 255, 255);
    }
}

void NeopixelController::illuminateArcadeButton(byte index)
{
    _arcadeButtonIndicators[index].hue++;
    _leds[NC_NUM_ROTARY_LEDS + index] = _arcadeButtonIndicators[index];
}

void NeopixelController::rotateRotaryEncoderIndicator(boolean forward)
{
    if (!forward && _rotaryEncoderPosition == 0) _rotaryEncoderPosition = NC_NUM_ROTARY_LEDS;
    _rotaryEncoderPosition += (forward) ? 1 : -1;
    _rotaryEncoderPosition = _rotaryEncoderPosition % NC_NUM_ROTARY_LEDS;

    _rotaryEncoderIndicator.hue += NC_ROTARY_FADESPEED;
    _leds[_rotaryEncoderPosition] = _rotaryEncoderIndicator;
}


void NeopixelController::effectSparkle(int speed) {
    if (_tick % speed == 0) {
        byte index = random(0, NC_NUM_OUTER_LEDS);
        _leds[NC_NUM_ROTARY_LEDS + NC_NUM_ARCADE_BUTTONS + index] += _arcadeButtonIndicators[0];
    }   
}

void NeopixelController::flashAllLights() {
    for(byte i = 0; i < NC_NUM_OUTER_LEDS; i++) {
        _leds[NC_NUM_ROTARY_LEDS + NC_NUM_ARCADE_BUTTONS + i] = _rotaryEncoderIndicator;
    }
}

void NeopixelController::effectRun(int speed) {
    if (_tick % speed == 0) {
        _pixel1 = (_pixel1 + 1) % NC_NUM_OUTER_LEDS;
        _leds[NC_NUM_ROTARY_LEDS + NC_NUM_ARCADE_BUTTONS + _pixel1] += _arcadeButtonIndicators[1];
    }   
}

void NeopixelController::effectRandomRun(int speed) {
    if (_tick % speed == 0) {
        if (_tick % (speed * 10) == 0) {
            _randomRunDirection = (random(0, 2) == 1) ? 1 : -1;
        }

        if (_pixel2 == 0 && _randomRunDirection == - 1) _pixel2 = NC_NUM_OUTER_LEDS;
        _pixel2 = (_pixel2 + _randomRunDirection) % NC_NUM_OUTER_LEDS;
        _leds[NC_NUM_ROTARY_LEDS + NC_NUM_ARCADE_BUTTONS + _pixel2] += _arcadeButtonIndicators[2];
    }   
}


void NeopixelController::update()
{
    FastLED.show();

    for (byte led = 0; led < NC_NUM_LEDS; led++) {
        _leds[led].fadeToBlackBy(NC_FADESPEED);
    }

    _tick++;
}


