# Tutorial

Several example files are provide to progressively introduce `asmc` features.

* ## [Led1](./Led1/README.md)
Introduction to the complier, it's usage and file format. Implements simple
state machine using a push button to control the on board LED

* ## [Led2](./Led2/README.md)
The same functionality as Led1, but uses state exit and entry actions to
control the LED.

* ## [Blink1](./Blink1/README.md)
A simple blinking LED demonstrating timed events and how to call functions
defined in the `.ino` file.

* ## [Blink2](./Blink2/README.md)
A blinking LED program where the LED will blink 4 times when the button is
pressed. Introduces the use of state variables.

* ## Blink3
Shows how to use event data to make the LED blink from 1 to 9 time in response
to serial input.

* ## Calc
A simple 4 function calculator using hierarchical state machines. (Bet you were
getting pretty sick of flashing LEDs)

* ## Clock
An alarm clock. The clock shows how to connect the state machine up to hardware
interrupts and how to implement complicate UI tasks using a state machine.



