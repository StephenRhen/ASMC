//
//  This state machine demnostrates how to add variables to a state
//  machine. It is similar to Blink1 but the only LED blinks four times
//  when the button has been pressed.
// 

#include <Button.h>

#include "Blink2Sm.h"
#include "Blink2.h"

// For some reason the Arduino make tools can't find limits.h when
// building from the command line.
#ifndef ULONG_MAX
#define ULONG_MAX   4294967295
#endif

#define BUTTON_PIN 2

Blink2Sm sm;

Button button(BUTTON_PIN);

unsigned long timeout = ULONG_MAX;

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

void startTimer(unsigned long msecs)
{
  timeout = millis() + msecs;
}

void stopTimer()
{
  timeout = ULONG_MAX;
}

int checkTimer()
{
  if (timeout <= millis()) {
    timeout = ULONG_MAX;
    return 1;
  }
  return 0;
}
