#include "Arduino.h"

class SevenSegmentController {
  public:
    SevenSegmentController();
    void setup();
    void update();
    void clear();
    void on();
    void off();
    void showNumber(long number, byte pos = 0);
};
