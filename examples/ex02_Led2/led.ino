//
//  Simplest state machine example. The state machine contains two states.
//  One for the LED on and one for the LED off. Pressing the button will
//  toggle
//  between the two states.

#include <Button.h>

#include "Led2Sm.h"

#define BUTTON_PIN 2
#define LED_PIN 3

Led2Sm sm;

Button button(BUTTON_PIN);

void setup() {
  button.begin();
  sm.begin();
}

void loop() {

  if (button.pressed()) {
    // Send event to state machine
    sm.run(sm.BUTTON_PRESSED);
  }

}

void ledOn()
{
 
}

void ledOff()
{

}
