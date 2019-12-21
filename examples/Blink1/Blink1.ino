//
//  Simplest state machine example. The state machine contains two states.
//  One for the LED on and one for the LED off. Pressing the button will
//  toggle between the two states.

#include <Button.h>

#include "Blink1Sm.h"
#include "Blink1.h"

// For some reason the Arduino command line make tools can't find limits.h
#ifndef ULONG_MAX
#define ULONG_MAX   4294967295
#endif ULONG_MAX

#define BUTTON_PIN 2
Button button(BUTTON_PIN);

Blink1Sm sm;

// Value of millis() when the timer expires.
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

// Start the timer and set it to expire msecs milliseconds from now.
void startTimer(unsigned long msecs)
{
  timeout = millis() + msecs;
}

// Effectivally stop the timer by setting it to expire 50 days from
// now. 
void stopTimer()
{
  timeout = ULONG_MAX;
}

// Check the timer against millis() to see if it has expired. If
// so cancel the timer and return 1.
int checkTimer()
{
  if (timeout <= millis()) {
    timeout = ULONG_MAX;
    return 1;
  }
  return 0;
}
