#include "InputController.h"
#include "Adafruit_MCP23017.h"

InputController::InputController()
{
  // constructor
}

void InputController::setup()
{
  _mcp.begin();      // use default address 0
  _mcp.setGPIOABMode(0xFFFF); // All ports input.
  _mcp.setGPIOABPullUp(0xFFFF); // All ports pull up.

  pinMode(IC_SLIDER_PIN, INPUT);
  _lastSliderState = analogRead(IC_SLIDER_PIN);
}

void InputController::setRotaryCallback(RotaryCallback callback) {
	_rotaryCallback = callback;
}

void InputController::setButtonCallback(ButtonCallback callback){
  _buttonCallback = callback;
}

void InputController::setSliderCallback(SliderCallback callback){
  _sliderCallback = callback;
}


boolean InputController::buttonState(byte buttonIndex) {
  return !((_lastState >> buttonIndex) & 1);
}

int InputController::sliderState() {
  return _lastSliderState;
}

int InputController::sliderState(int min, int max) {
  return map(sliderState(), 0, 1023, min, max);
}

void InputController::update()
{
  int newState = _mcp.readGPIOAB();
  if (newState != _lastState) {
    boolean rotaryAState = (newState >> IC_ROTARY_A) & 1;
    boolean rotaryBState = (newState >> IC_ROTARY_B) & 1;

    // Check Rotary Encoder
    if (!rotaryAState && rotaryAState != _lastRotaryAState) {
      _rotaryCallback(!rotaryBState);
    }

    // Check All Input
    for (byte buttonIndex = 0; buttonIndex < 16; buttonIndex++) {
      boolean newButtonState = (newState >> buttonIndex) & 1;
      boolean oldButtonState = (_lastState >> buttonIndex) & 1;

      if (newButtonState != oldButtonState) {
        _buttonCallback(buttonIndex, !newButtonState);
      }
    }

    _lastRotaryAState = rotaryAState;
    _lastState = newState;
  }

  int newSliderState = analogRead(IC_SLIDER_PIN);
  if (newSliderState != _lastSliderState) {
    if (millis() - _debounceTimer > IC_SLIDER_DENOISE_TIME) {
      _lastSliderState = newSliderState;
      _sliderCallback(newSliderState);
      _debounceTimer = millis();
    }
  } else {
    _debounceTimer = millis();
  }
}


