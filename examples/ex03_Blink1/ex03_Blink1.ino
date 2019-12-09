//
//  Simplest state machine example. The state machine contains two states.
//  One for the LED on and one for the LED off. Pressing the button will
//  toggle
//  between the two states.

#include <Button.h>

#include "Blink1Sm.h"
#include "Blink1.h"

#define BUTTON_PIN 2

Blink1Sm sm;

Button button(BUTTON_PIN);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  button.begin();
  sm.begin();
}

void loop() {

  if (button.pressed()) {
    // Send event to state machine
    sm.run(sm.BUTTON_PRESSED);
  }
  if (checkTimer()) {
     sm.run(sm.TIMEOUT);
  }

}

void startTimer(long timeout)
{
 
}

void stopTimer()
{

}

int checkTimer()
{

}
