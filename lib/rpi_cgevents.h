#ifndef CGEVENTS_RPI_H
#define CGEVENTS_RPI_H

#include "cgevents.h"
#include "rpi_tools.h"

void rpievents_init();
void rpievents_deinit();
void rpievents_registerinput_buttonclick(int pin, int ID, bool canRepeat=true, bool emit_event_on_button_release=true, bool active_state=false);
void rpievents_registerinput_statechange(int pin, int ID);

#endif // CGEVENTS_RPI_H
