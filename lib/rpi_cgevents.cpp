#include "rpi_cgevents.h"

#include <stdlib.h>
#include <stdio.h>
#include <regex>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <wiringPi.h>
#include <vector>
#include "cgeventqueue.h"
#include <unistd.h>

struct rpievent_input_button_click {
    int pin;
    int ID;
    int last_state;
    bool last_wasrepeat;
    bool can_repeat;
    bool inverted;
    int active_state;
    int inactive_state;
    std::chrono::steady_clock::time_point lastevent;
    double since_lastevent_ms(const std::chrono::steady_clock::time_point& tnow) const {
        return std::chrono::duration_cast<std::chrono::duration<double,std::milli> >(tnow - lastevent).count();
    }
};


struct rpievent_input_statechange {
    int pin;
    int ID;
    int last_state;
};

bool rpi_events_stop_thread=false;
std::thread* rpi_events_thread=NULL;
std::mutex rpi_events_mutex;
CGEventQueue* rpi_events_queue=NULL;
std::vector<rpievent_input_button_click> rpi_events_buttons;
std::vector<rpievent_input_statechange> rpi_events_statechanges;

#define BUTTON_DOWN_DELAY_MIN 20.0f
#define BUTTON_REPEAT_DELAY_MIN 300.0f
#define BUTTON_REPEAT_DELAY_REPEAT 100.0f
#define BUTTON_REPEAT_DELAY_MAX 1000.0f

#define STATECHANGE_MIN_DELAY 10.0f

#define EVENTS_THREAD_DELAY_MS 10


void rpi_events_thread_func() {
    bool done=false;
    while(!done) {
        rpi_events_mutex.lock();
        for (size_t i=0; i<rpi_events_buttons.size(); i++) {
            rpievent_input_button_click b=rpi_events_buttons[i];
            const int s=digitalRead(b.pin);
            const int olds=b.last_state;
            const std::chrono::steady_clock::time_point tnow=std::chrono::steady_clock::now();
            const double since_last = b.since_lastevent_ms(tnow);
            if (((b.inverted && s==b.active_state && olds==b.inactive_state) || (!b.inverted && s==b.inactive_state && olds==b.active_state)) && since_last>BUTTON_DOWN_DELAY_MIN) {
                b.lastevent=tnow;
                if (!b.last_wasrepeat) rpi_events_queue->addEvent(CGButtonClickedEvent(b.ID));
                b.last_wasrepeat=false;
            } else if(b.can_repeat && ((!b.last_wasrepeat && since_last>BUTTON_REPEAT_DELAY_MIN) || (b.last_wasrepeat && since_last>BUTTON_REPEAT_DELAY_REPEAT))) {
                if (((b.inverted && s==b.inactive_state && olds==b.active_state) || (!b.inverted && s==b.active_state && olds==b.inactive_state))) {
                    b.lastevent=tnow;
                    //rpi_events_queue->addEvent(CGButtonEvent(b.ID));
                } else if (s==b.active_state && olds==b.active_state && since_last<BUTTON_REPEAT_DELAY_MAX) {
                    b.lastevent=tnow;
                    rpi_events_queue->addEvent(CGButtonClickedEvent(b.ID));
                    b.last_wasrepeat=true;
                }
            }


            b.last_state=s;
            rpi_events_buttons[i]=b;
        }

        for (size_t i=0; i<rpi_events_statechanges.size(); i++) {
            const int s=digitalRead(rpi_events_statechanges[i].pin);
            const int olds=rpi_events_statechanges[i].last_state;
            if ((s==1 && olds==0) || (s==0 && olds==1)) {
                rpi_events_queue->addEvent(CGInputStateChanged(rpi_events_statechanges[i].ID, s));
            }
            rpi_events_statechanges[i].last_state=s;
        }
        rpi_events_mutex.unlock();

        // check for DONE-signal every 5ms
        std::this_thread::sleep_for(std::chrono::milliseconds(EVENTS_THREAD_DELAY_MS));
        rpi_events_mutex.lock();
        if (rpi_events_stop_thread) done=true;
        rpi_events_mutex.unlock();
        if (done) break;
    }
}


void rpievents_init()
{
    if (!rpi_events_queue) rpi_events_queue=CGEventQueue::instance();
    if (!rpi_events_thread) {
        if (!getuid()) {
            printf("running WiringLIB with root priviledges!\n");
            wiringPiSetupGpio();
        } else {
            printf("running WiringLIB in user mode!\n");
            wiringPiSetupSys ();
        }
        rpi_events_thread=new std::thread(rpi_events_thread_func);
    }
}



void rpievents_deinit()
{
    if (rpi_events_thread) {
        rpi_events_mutex.lock();
        rpi_events_stop_thread=true;
        rpi_events_mutex.unlock();
        rpi_events_thread->join();
        delete rpi_events_thread;
        rpi_events_thread=NULL;
    }
}



void rpievents_registerinput_buttonclick(int pin, int ID, bool canRepeat, bool emit_event_on_button_release, bool active_state)
{
    rpievent_input_button_click b;
    b.pin=pin;
    b.ID=ID;
    b.last_state=1;
    b.lastevent=std::chrono::steady_clock::now();
    b.last_wasrepeat=false;
    b.can_repeat=canRepeat;
    b.inverted=!emit_event_on_button_release;
    if (active_state){
        b.active_state=1;
        b.inactive_state=0;
    } else {
        b.active_state=0;
        b.inactive_state=1;
    }
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);
    rpi_events_mutex.lock();
    rpi_events_buttons.push_back(b);
    rpi_events_mutex.unlock();
}


void rpievents_registerinput_statechange(int pin, int ID)
{
    rpievent_input_statechange b;
    b.pin=pin;
    b.ID=ID;
    b.last_state=1;
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);
    rpi_events_mutex.lock();
    rpi_events_statechanges.push_back(b);
    rpi_events_mutex.unlock();
}
