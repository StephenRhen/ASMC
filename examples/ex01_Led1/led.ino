//
//  Simplest state machine example. The state machine contains two states.
//  One for the LED on and one for the LED off. Pressing the button will
//  toggle between the two states.

#include <Button.h>

#include "LedSm.h"

#define BUTTON_PIN 2

LedSm sm;
Button button(BUTTON_PIN);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  button.begin();
  
  sm.begin();
}

void loop() {

  // Send an event to the state machine every time the button is pressed.
  if (button.pressed()) {
    sm.run(sm.BUTTON_PRESSED);
  }

}

