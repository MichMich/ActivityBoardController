#include <Arduino.h>
#include "InputController.h"
#include "SevenSegmentController.h"
#include "NeopixelController.h"
#include <elapsedMillis.h>

#define AUTO_OFF_TIME 60000

InputController inputController;
SevenSegmentController sevenSegmentController;
NeopixelController neopixelController;

elapsedMillis autoOffTimer;

void rotaryCallback(boolean direction) {
    neopixelController.rotateRotaryEncoderIndicator(direction);
}
void buttonCallback(byte buttonIndex, boolean state) {
    autoOffTimer = 0;
    sevenSegmentController.on();
}
void sliderCallback(int value) {
    sevenSegmentController.showNumber(value);
}

void setup() {
    sevenSegmentController.setup();
    neopixelController.setup();
    inputController.setup();
    inputController.setRotaryCallback(rotaryCallback);
    inputController.setButtonCallback(buttonCallback);
    inputController.setSliderCallback(sliderCallback);
}

void loop() {
    inputController.update();
    if (autoOffTimer < AUTO_OFF_TIME) {
        if (inputController.buttonState(IC_ROTARY_BUTTON)) neopixelController.flashAllLights();

        if (inputController.buttonState(IC_ARCADE_1)) neopixelController.illuminateArcadeButton(0);
        if (inputController.buttonState(IC_ARCADE_2)) neopixelController.illuminateArcadeButton(1);
        if (inputController.buttonState(IC_ARCADE_3)) neopixelController.illuminateArcadeButton(2);

        if (inputController.buttonState(IC_TRIPLE_SW_1)) neopixelController.effectSparkle(100 - inputController.sliderState(0, 99));
        if (inputController.buttonState(IC_TRIPLE_SW_2)) neopixelController.effectRun(100 - inputController.sliderState(0, 99));
        if (inputController.buttonState(IC_TRIPLE_SW_3)) neopixelController.effectRandomRun(100 - inputController.sliderState(0, 99));
    } else {
        sevenSegmentController.off();
    }

    neopixelController.update();
    // sevenSegmentController.update();
}
