#include "Arduino.h"
#include <FastLED.h>

#define NC_NUM_LEDS 87
#define NC_DATA_PIN A1

#define NC_NUM_ARCADE_BUTTONS 3
#define NC_NUM_ROTARY_LEDS 12
#define NC_NUM_OUTER_LEDS 72
#define NC_ROTARY_FADESPEED 2
#define NC_ARCADE_FADESPEED 4
#define NC_FADESPEED 1


class NeopixelController {

    public:
        NeopixelController();
        void setup();
        void update();
        void setPixel(byte pixel);
        void rotateRotaryEncoderIndicator(boolean forward);
        void fadeArcadeButton(byte index);
        void illuminateArcadeButton(byte index);
        void flashAllLights();
        void flashRotaryEncoder();
        void effectSparkle(int speed);
        void effectRun(int speed, byte colorIndex = 1);
        void effectRandomRun(int speed);
        void illuminateLogo();

    private:
        long _tick = 0;
        byte _hue = 0;
        byte _num = 0;
        byte _pixel1 = 0;
        byte _pixel2 = 0;
        byte _rotaryEncoderPosition = 0;
        int _randomRunDirection = 1;
        CRGB _leds[NC_NUM_LEDS];
        CHSV _rotaryEncoderIndicator;
        CHSV _arcadeButtonIndicators[NC_NUM_ARCADE_BUTTONS];
        
};
