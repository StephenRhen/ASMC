/* Code generated by asmc from file Led2Sm.sm, do not edit. */

#ifndef _LED2SM_H_
#define _LED2SM_H_

class Led2Sm {
  public:

    // State machine events
    typedef enum {
      BUTTON_PRESSED
    } event_t;

    // Return codes for run function.
    typedef enum {
      ok,
      unknown_event,
      unhandled_event
    } retstatus_t;

    Led2Sm();
    void begin();
    retstatus_t run(event_t event);

  private:

    // Possiable states.
    typedef enum {
      led_off,
      led_on
    } state_t;

    state_t state;
};

#endif /* _LED2SM_H_ */

