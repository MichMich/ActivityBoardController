#include "Arduino.h"

class SevenSegmentController {
  public:
    SevenSegmentController();
    void setup();
    void update();
    void clear();
    void setPowerState(boolean state);
    void on();
    void off();
    void showNumber(long number, byte pos = 0);
};
