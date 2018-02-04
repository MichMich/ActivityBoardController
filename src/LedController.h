#include "Arduino.h"


#define LC_LED_COUNT 6

#define LC_MAIN_SW_1_LED 0
#define LC_MAIN_SW_2_LED 1
#define LC_ROCKER_GR_1_LED 2
#define LC_ROCKER_GR_2_LED 3
#define LC_ROCKER_RD_1_LED 4
#define LC_ROCKER_RD_2_LED 5

enum LedState : byte { stateOff, stateOn, stateFade, stateFlash } ;


class LedController {
    public:
        LedController();
        void setup();
        void update();
        void off();
        void setState(byte ledIndex, LedState state);

    private:
        byte _pins[LC_LED_COUNT] = {10, 9, 7, 8, 11, 12};
        LedState _states[LC_LED_COUNT];
        long _tick = 0;
        boolean _flashState = false;
        byte _fadeState = 0;
        int _fadeDelta = 1;
        void fadeEffect();
        void flashEffect();
};
