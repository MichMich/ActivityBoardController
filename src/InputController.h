#include "Arduino.h"
#include "Adafruit_MCP23017.h"

#define IC_SLIDER_PIN A0
#define IC_SLIDER_DENOISE_TIME 100

#define IC_ARCADE_1 0
#define IC_ARCADE_2 1
#define IC_ARCADE_3 2

#define IC_ROCKER_GR_1 3
#define IC_ROCKER_GR_2 4
#define IC_ROCKER_RD_1 5
#define IC_ROCKER_RD_2 6

#define IC_ROTARY_A 8
#define IC_ROTARY_B 9

#define IC_MAIN_SW_1 10
#define IC_MAIN_SW_2 11
#define IC_ROTARY_BUTTON 12
#define IC_TRIPLE_SW_3 13
#define IC_TRIPLE_SW_2 14
#define IC_TRIPLE_SW_1 15

class InputController {

  typedef void (*RotaryCallback)(boolean direction);
  typedef void (*ButtonCallback)(byte buttonIndex, boolean state);
  typedef void (*SliderCallback)(int value);


  public:
    InputController();
    void setup();
    void update();
    void setRotaryCallback(RotaryCallback callback);
    void setButtonCallback(ButtonCallback callback);
    void setSliderCallback(SliderCallback callback);
    boolean buttonState(byte buttonIndex);
    int sliderState();
    int sliderState(int min, int max);
  
  private:
    int _lastState = 0;
    int _lastSliderState = 0;
    boolean _lastRotaryAState = true;
    Adafruit_MCP23017 _mcp;
    RotaryCallback _rotaryCallback;
    ButtonCallback _buttonCallback;
    SliderCallback _sliderCallback;
    long _debounceTimer;
};
