//
//  The same state machine as Led1, but move the user code from the
//  transitions to demonstrate the state %entry and %exit features.

#include <Button.h>

#include "Led2Sm.h"

#define BUTTON_PIN 2

Led2Sm sm;
Button button(BUTTON_PIN);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  button.begin();
  sm.begin();
}

void loop()
{
  if (button.pressed()) {
    // Send event to state machine
    sm.run(sm.BUTTON_PRESSED);
  }
}

