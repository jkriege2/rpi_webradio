#ifndef CGEVENTS_RPI_H
#define CGEVENTS_RPI_H

#include "cgevents.h"
#include "rpi_tools.h"

void rpievents_init();
void rpievents_deinit();

/** \brief registers a button-click (and repeat-click) watcher for a given pin
 *
 * The watcher works as follows:
 *
 *   # read button state everythread loop repeat
 *   # compare to previous value (stored in rpievent_input_button_click)
 *   # look at pin state:
 *      * if \c inactive->active state change ==> event
 *      * if \c active->active and more than \c BUTTON_REPEAT_DELAY_MIN milliseconds passed since last down press ==> repeat-event (if enabled)
 *      * if \c active->active and more than \c BUTTON_REPEAT_DELAY_REPEAT milliseconds passed since last repeat-event ==> repeat-event (if enabled)
 *      .
 *   .
 * \note This function generates events of type CGButtonClickedEvent
 *
 * \note If emit_event_on_button_release ("inverted" mode), then the first event is emitted on the \c active->inactive edge, instead o the \c inactive->active edge (see setp 3)
 *
 */
void rpievents_registerinput_buttonclick(int pin, int ID, bool canRepeat=true, bool check_double_click=false, bool emit_event_on_button_release=true, bool active_state=false, rpit_pullresistor_mode resistor_pull=rpitprUP);
/** \brief registers a statechange-watcher on a specified pin
 *
 *  If pin changes state -> emit event with new state
 * \note This function generates events of type CGInputStateChanged
 */
void rpievents_registerinput_statechange(int pin, int ID, rpit_pullresistor_mode resistor_pull=rpitprUP);


/*! \brief registers a watcher for rotary encoders on the given pins


   The watcher works as follows:
\verbatim
   A:  +---+   +---+   +---
       |   |   |   |   |
     --+   +---+   +---+

   B:+   +---+   +---+   +--
     |   |   |   |   |   |
     +---+   +---+   +---+
      0 1 1 0 0 1 1 0 0 1
      0 0 1 1 0 0 1 1 0 0
      ~~~~~~~~

     ---> CW: +1
       0010   2
       1011  11
       1101  13
       0100   4

     <--- CCW: -1
       0001   1
       0111   7
       1110  14
       1000   8


    1. read both states "AB"
    2. combine old state "A'B'" and new state AB to "A'B'AB"
    3. for CW rotations, only the combination "CW" will occur
       for CCW rotation, only the combinations "CCW" will occur
    4. use number "A'B'AB" for lookup in table rpievent_rotary_table, that returns the +1, -1 or 0
          0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        { 0, -1, +1,  0, +1,  0,  0, -1, -1,  0,  0, +1,  0, +1, -1,  0 }
\endverbatim

\note For debouncing, the function rereads the pin states \c ROTARY_DEBOUNCE_DELAY_MS after any change on them.

\note This function generates events of type CGInputScroll
 */
void rpievents_registerinput_rotaryscroll(int pinA, int pinB, int ID, rpit_pullresistor_mode resistor_pull=rpitprUP, int steps_for_inc=4);


#endif // CGEVENTS_RPI_H
