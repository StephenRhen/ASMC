//
//  Simplest state machine example. The state machine contains two states.
//  One for the LED on and one for the LED off. Pressing the button will
//  toggle
//  between the two states.

#include <Button.h>

#include "Blink3Sm.h"
#include "Blink3.h"

// For some reason the Arduino command line make tools can't find limits.h
#define ULONG_MAX   4294967295

#define BUTTON_PIN 2

Blink3Sm sm;

unsigned long timeout = ULONG_MAX;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  sm.begin();
}

void loop()
{
  if (checkTimer()) {
     sm.run(sm.TIMEOUT);
  }
}

void serialEvent()
{
  while(Serial.available()) {
    int ch = Serial.read();
    if (ch >= '1' && ch <= '9') {
      sm.run(sm.COUNT, ch - '0');
    }
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
