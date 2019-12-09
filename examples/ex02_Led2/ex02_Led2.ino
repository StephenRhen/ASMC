//
//  Simplest state machine example. The state machine contains two states.
//  One for the LED on and one for the LED off. Pressing the button will
//  toggle
//  between the two states.

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

void ledOn()
{
  digitalWrite(LED_BUILTIN, HIGH);
}

void ledOff()
{
  digitalWrite(LED_BUILTIN, LOW);
}
