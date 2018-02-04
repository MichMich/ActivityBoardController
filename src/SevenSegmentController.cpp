#include "SevenSegmentController.h"
#include <LedControl.h>


LedControl lc = LedControl(5, 4, 6, 1);
int num = 0;

SevenSegmentController::SevenSegmentController()
{
  // constructor
}

void SevenSegmentController::showNumber(long number, byte pos = 0) {
    byte digit = number % 10;
    lc.setDigit(0, pos, digit, false);

    long remainingDigits = number / 10;
    if (remainingDigits > 0) {
        showNumber(remainingDigits, pos + 1);
    } else {
      while (pos < 7) {
        pos++;
        lc.setChar(0, pos, ' ', false);
      }
    }
}

void SevenSegmentController::setPowerState(boolean state)
{
  lc.shutdown(0, !state);
}

void SevenSegmentController::on()
{
  setPowerState(true);
}

void SevenSegmentController::off()
{
  setPowerState(false);
}

void SevenSegmentController::clear()
{
  lc.clearDisplay(0); // Clear the display
}

void SevenSegmentController::setup()
{
  lc.setIntensity(0,15); // Set the display to full brightness
  lc.clearDisplay(0); // Clear the display
}

void SevenSegmentController::update()
{
  num++;
  showNumber(num);
}



