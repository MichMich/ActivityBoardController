#include <Arduino.h>
#include "InputController.h"
#include "SevenSegmentController.h"
#include "NeopixelController.h"
#include "LedController.h"
#include "CommunicationController.h"
#include <elapsedMillis.h>

#define AUTO_OFF_TIME 300000

InputController inputController;
SevenSegmentController sevenSegmentController;
NeopixelController neopixelController;
LedController ledController;
CommunicationController communicationController;

elapsedMillis autoOffTimer;
boolean autoOffTriggered = false;
long tick = 0;
long countDown = 99999999;

void rotaryCallback(boolean direction) {
    neopixelController.rotateRotaryEncoderIndicator(direction);
}

void buttonCallback(byte buttonIndex, boolean state) {
    if (autoOffTriggered) {
        autoOffTimer = 0;
        communicationController.sendCommand("auto_off", 0);
        autoOffTriggered = false;
    }

    sevenSegmentController.setPowerState(inputController.buttonState(IC_MAIN_SW_1));
    communicationController.sendCommand("buttons", inputController.buttonState());  
}

void sliderCallback(int value) {
    communicationController.sendCommand("slider", inputController.sliderState());
}

void setup() {
    communicationController.setup(115200);
    communicationController.sendCommand("status", "booting");

    sevenSegmentController.setup();
    sevenSegmentController.off();
    neopixelController.setup();
    ledController.setup();
    inputController.setup();
    inputController.setRotaryCallback(rotaryCallback);
    inputController.setButtonCallback(buttonCallback);
    inputController.setSliderCallback(sliderCallback);

    communicationController.setup(115200);
    communicationController.sendCommand("status", "booted");
    communicationController.sendCommand("auto_off", 0);
}

void arcadeButtonLoop() {
    if (inputController.buttonState(IC_ARCADE_1)) {
        neopixelController.fadeArcadeButton(0);
        neopixelController.effectRun(10 - inputController.sliderState(0, 9), 0);
    }
    if (inputController.buttonState(IC_ARCADE_2)) {
        neopixelController.fadeArcadeButton(1);
        neopixelController.effectRun(10 - inputController.sliderState(0, 9), 1);
    }
    if (inputController.buttonState(IC_ARCADE_3)) {
        neopixelController.fadeArcadeButton(2);
        neopixelController.effectRun(10 - inputController.sliderState(0, 9), 2);
    }
}

void trippleButtonLoop() {
    if (inputController.buttonState(IC_TRIPLE_SW_1)) neopixelController.illuminateArcadeButton(0);
    if (inputController.buttonState(IC_TRIPLE_SW_2)) neopixelController.illuminateArcadeButton(1);
    if (inputController.buttonState(IC_TRIPLE_SW_3)) neopixelController.illuminateArcadeButton(2);
}

void rotaryEncoderLoop() {
    if (inputController.buttonState(IC_ROTARY_BUTTON)) neopixelController.flashAllLights();
}

void mainSwitchLoop() {
    ledController.setState(LC_MAIN_SW_1_LED, (inputController.buttonState(IC_MAIN_SW_1)) ? stateFlash : stateFade );
    ledController.setState(LC_MAIN_SW_2_LED, (inputController.buttonState(IC_MAIN_SW_2)) ? stateFlash : stateFade );

    if (inputController.buttonState(IC_MAIN_SW_2)) neopixelController.flashRotaryEncoder();
}

void rockerButtonLoop() {
    if (inputController.buttonState(IC_ROCKER_GR_1)) neopixelController.illuminateLogo();
    if (inputController.buttonState(IC_ROCKER_GR_2)) neopixelController.effectSparkle(10 - inputController.sliderState(0, 9));
    if (inputController.buttonState(IC_ROCKER_RD_1)) neopixelController.effectRun(10 - inputController.sliderState(0, 9));
    if (inputController.buttonState(IC_ROCKER_RD_2)) neopixelController.effectRandomRun(10 - inputController.sliderState(0, 9));
    ledController.setState(LC_ROCKER_GR_1_LED, (inputController.buttonState(IC_ROCKER_GR_1)) ? stateOn : stateOff );
    ledController.setState(LC_ROCKER_GR_2_LED, (inputController.buttonState(IC_ROCKER_GR_2)) ? stateOn : stateOff );
    ledController.setState(LC_ROCKER_RD_1_LED, (inputController.buttonState(IC_ROCKER_RD_1)) ? stateOn : stateOff );
    ledController.setState(LC_ROCKER_RD_2_LED, (inputController.buttonState(IC_ROCKER_RD_2)) ? stateOn : stateOff );
}

void ledLoop() {
    ledController.update();
}

void loop() {
    tick++;
    countDown--;
    inputController.update();
    if (autoOffTimer < AUTO_OFF_TIME) {
        if (tick % 10 == 0) sevenSegmentController.showNumber(countDown);
        mainSwitchLoop();
        arcadeButtonLoop();
        trippleButtonLoop();
        rockerButtonLoop();
        rotaryEncoderLoop();
        ledLoop();
    } else {
        if (!autoOffTriggered) {
            sevenSegmentController.off();
            ledController.off();
            communicationController.sendCommand("auto_off", 1);
            autoOffTriggered = true;
        }
    }

    neopixelController.update();
}
