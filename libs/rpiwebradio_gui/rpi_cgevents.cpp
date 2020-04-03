#include "cgprecomp.h"
#include "rpi_cgevents.h"

#include <stdlib.h>
#include <stdio.h>
#include <regex>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include "cgeventqueue.h"
#include <unistd.h>
#include <atomic>

/* 1. read button state everythread loop repeat
 * 2. compare to previous value (stored in rpievent_input_button_click)
 * 3. if inactive->active state change ==> event
 *    if active->active and more than BUTTON_REPEAT_DELAY_MIN milliseconds passed since last down press ==> repeat-event (if enabled)
 *                      and more than BUTTON_REPEAT_DELAY_REPEAT milliseconds passed since last repeat-event ==> repeat-event (if enabled)
 *
 * !!! If inverted, then the first event is emitted on the active->inactive edge, instead o the inactive->active edge (see setp 3) !!!
 *
 */
struct rpievent_input_button_click {
    int pin;
    int ID;
    int last_state;
    bool last_wasrepeat;
    bool can_repeat;
    bool inverted;
    int active_state;
    int inactive_state;
    bool check_double_click;
    bool click_pending;
    std::chrono::steady_clock::time_point lastevent;
    double since_lastevent_ms(const std::chrono::steady_clock::time_point& tnow) const {
        return std::chrono::duration_cast<std::chrono::duration<double,std::milli> >(tnow - lastevent).count();
    }
};



const int rpievent_rotary_table[] ={ 0, -1, +1,  0, +1,  0,  0, -1, -1,  0,  0, +1,  0, +1, -1,  0 };

//const int rpievent_rotary_table[16] = {0,0,-1,0,0,0,0,1,1,0,0,0,0,-1,0,0};

struct rpievent_input_rotary_scroll {
    int pinA;
    int pinB;
    int ID;
    int last_state;
    int inc;
    int lastinc;
    //int lastinc;
    int steps_for_inc1;
    std::chrono::steady_clock::time_point lastevent;
    double since_lastevent_ms(const std::chrono::steady_clock::time_point& tnow) const {
        return std::chrono::duration_cast<std::chrono::duration<double,std::milli> >(tnow - lastevent).count();
    }
};

/* If pin changes state -> emit event with new state */
struct rpievent_input_statechange {
    int pin;
    int ID;
    int last_state;

};

std::atomic_int rpi_events_stop_thread;
std::thread* rpi_events_thread=NULL;
std::thread* rpi_events_rotary_thread=NULL;
std::mutex rpi_events_mutex;
std::mutex rpi_events_mutex_rotary;
CGEventQueue* rpi_events_queue=NULL;
std::vector<rpievent_input_button_click> rpi_events_buttons;
std::vector<rpievent_input_statechange> rpi_events_statechanges;
std::vector<rpievent_input_rotary_scroll> rpi_events_rotaryscroll;

#define BUTTON_DOWN_DELAY_MIN 20.0f
#define BUTTON_DOUBLECLICK_DELAY_MAX 300.0f
#define BUTTON_REPEAT_DELAY_MIN 300.0f
#define BUTTON_REPEAT_DELAY_REPEAT 100.0f
#define BUTTON_REPEAT_DELAY_MAX 1000.0f

#define STATECHANGE_MIN_DELAY 10.0f

#define ROTARY_MIN_DELAY 0.0f
#define ROTARY_DEBOUNCE_DELAY_US 100

#define EVENTS_THREAD_DELAY_MS 10
#define EVENTS_THREAD_ROTARY_DELAY_US 100


void rpi_events_thread_func() {
    bool done=false;
    while(!done) {
        rpi_events_mutex.lock();
        for (size_t i=0; i<rpi_events_buttons.size(); i++) {
            rpievent_input_button_click b=rpi_events_buttons[i];
            const int s=rpit_readDigital(b.pin);
            const int olds=b.last_state;
            const std::chrono::steady_clock::time_point tnow=std::chrono::steady_clock::now();
            const double since_last = b.since_lastevent_ms(tnow);
            if (b.check_double_click && b.click_pending && since_last>BUTTON_DOUBLECLICK_DELAY_MAX) {
                rpi_events_queue->addEvent(new CGButtonClickedEvent(b.ID));
                b.click_pending=false;
            } else  if (((b.inverted && s==b.active_state && olds==b.inactive_state) || (!b.inverted && s==b.inactive_state && olds==b.active_state)) && since_last>BUTTON_DOWN_DELAY_MIN) {
                if (!b.last_wasrepeat) {
                    if (b.check_double_click && b.click_pending) {
                        if (since_last<=BUTTON_DOUBLECLICK_DELAY_MAX) { // double-click
                            rpi_events_queue->addEvent(new CGButtonDoubleClickedEvent(b.ID));
                            b.click_pending=false;
                        } else { // no double-click, so we need two clicks
                            rpi_events_queue->addEvent(new CGButtonClickedEvent(b.ID));
                            rpi_events_queue->addEvent(new CGButtonClickedEvent(b.ID));
                            b.click_pending=false;
                        }
                    } else if (b.check_double_click && !b.click_pending) { // wait a bit and see whether we get a double-click
                        b.click_pending=true;
                        //rpi_events_queue->addEvent(new CGButtonClickedEvent(b.ID));
                    } else if (!b.check_double_click ) { // single-click only, as we don't check for double-clicks
                        rpi_events_queue->addEvent(new CGButtonClickedEvent(b.ID));
                        b.click_pending=false;
                    }
                }
                b.lastevent=tnow;
                b.last_wasrepeat=false;
            } else if(b.can_repeat && ((!b.last_wasrepeat && since_last>BUTTON_REPEAT_DELAY_MIN) || (b.last_wasrepeat && since_last>BUTTON_REPEAT_DELAY_REPEAT))) {
                if (((b.inverted && s==b.inactive_state && olds==b.active_state) || (!b.inverted && s==b.active_state && olds==b.inactive_state))) {
                    b.lastevent=tnow;
                    //rpi_events_queue->addEvent(new CGButtonEvent(b.ID));
                } else if (s==b.active_state && olds==b.active_state && since_last<BUTTON_REPEAT_DELAY_MAX) {
                    b.lastevent=tnow;
                    rpi_events_queue->addEvent(new CGButtonClickedEvent(b.ID));
                    b.click_pending=false;
                    b.last_wasrepeat=true;
                }
            }


            b.last_state=s;
            rpi_events_buttons[i]=b;
        }

        for (size_t i=0; i<rpi_events_statechanges.size(); i++) {
            const int s=rpit_readDigital(rpi_events_statechanges[i].pin);
            const int olds=rpi_events_statechanges[i].last_state;
            if ((s==1 && olds==0) || (s==0 && olds==1)) {
                rpi_events_queue->addEvent(new CGInputStateChanged(rpi_events_statechanges[i].ID, s));
            }
            rpi_events_statechanges[i].last_state=s;
        }
        rpi_events_mutex.unlock();

        // check for DONE-signal every 5ms
        std::this_thread::sleep_for(std::chrono::milliseconds(EVENTS_THREAD_DELAY_MS));
        if (rpi_events_stop_thread!=0) done=true;
        if (done) break;
    }
}


void rpi_events_rotary_thread_func() {
    bool done=false;
    while(!done) {
        rpi_events_mutex_rotary.lock();
        std::vector<rpievent_input_rotary_scroll> local_events_rotaryscroll=rpi_events_rotaryscroll;
        rpi_events_mutex_rotary.unlock();
        for (size_t i=0; i<local_events_rotaryscroll.size(); i++) {
            rpievent_input_rotary_scroll b=local_events_rotaryscroll[i];
            const std::chrono::steady_clock::time_point tnow=std::chrono::steady_clock::now();
            const double since_last = b.since_lastevent_ms(tnow);
            if (true) {
                //int cnt[4]={0,0,0,0};
                int s=rpit_readDigitalI(b.pinA)|(rpit_readDigitalI(b.pinB)*2);
                if (b.last_state<0) {
                    b.last_state=s;
                } else if (s!=b.last_state) {
                    // if we have a state change, wait ROTARY_DEBOUNCE_DELAY_US and measure again (--> debounce)
                    if (ROTARY_DEBOUNCE_DELAY_US>0) {
                        std::this_thread::sleep_for(std::chrono::microseconds(ROTARY_DEBOUNCE_DELAY_US));
                        s=rpit_readDigitalI(b.pinA)|(rpit_readDigitalI(b.pinB)*2);
                    }



                    const int olds=b.last_state;
                    const int lookup=((olds*4)+s)&0x0F;
                    const int inc=rpievent_rotary_table[lookup];
                    b.inc+=inc;
                    //std::cout<<b.inc<<"\n";

                    if ((abs(b.inc)>=b.steps_for_inc1) && (ROTARY_MIN_DELAY<=0 || since_last>ROTARY_MIN_DELAY)) {
                        int ii=b.inc/b.steps_for_inc1;
                        b.lastinc=b.inc;
                        rpi_events_queue->addEvent(new CGInputScroll(b.ID, ii));
                        b.inc=0;
                        b.lastevent=tnow;

                    }
                    b.last_state=s;
                }
                local_events_rotaryscroll[i]=b;
            }
        }
        rpi_events_mutex_rotary.lock();
        rpi_events_rotaryscroll=local_events_rotaryscroll;
        rpi_events_mutex_rotary.unlock();

        // check for DONE-signal every 5ms
        std::this_thread::sleep_for(std::chrono::microseconds(EVENTS_THREAD_ROTARY_DELAY_US));
        if (rpi_events_stop_thread!=0) done=true;
        if (done) break;
    }
}


void rpievents_init()
{
    if (!rpi_events_queue) rpi_events_queue=CGEventQueue::instance();
    rpit_initIO();
    rpi_events_stop_thread=0;
    if (!rpi_events_thread) {
        rpi_events_thread=new std::thread(rpi_events_thread_func);
    }
    if (!rpi_events_rotary_thread) {
        rpi_events_rotary_thread=new std::thread(rpi_events_rotary_thread_func);
    }
}



void rpievents_deinit()
{
    rpi_events_stop_thread=1;
    if (rpi_events_thread) {
        rpi_events_thread->join();
        delete rpi_events_thread;
        rpi_events_thread=NULL;
    }
    if (rpi_events_rotary_thread) {
        rpi_events_rotary_thread->join();
        delete rpi_events_rotary_thread;
        rpi_events_rotary_thread=NULL;
    }
    rpi_events_stop_thread=1;
}



void rpievents_registerinput_buttonclick(int pin, int ID, bool canRepeat, bool check_double_click, bool emit_event_on_button_release, bool active_state, rpit_pullresistor_mode resistor_pull)
{
    rpievent_input_button_click b;
    b.pin=pin;
    b.ID=ID;
    b.last_state=1;
    b.lastevent=std::chrono::steady_clock::now();
    b.last_wasrepeat=false;
    b.can_repeat=canRepeat;
    b.inverted=!emit_event_on_button_release;
    b.check_double_click=check_double_click;
    b.click_pending=false;
    if (active_state){
        b.active_state=1;
        b.inactive_state=0;
    } else {
        b.active_state=0;
        b.inactive_state=1;
    }
    rpit_setPinMode(pin, rpitpmDigitalInput, resistor_pull);
    rpi_events_mutex.lock();
    rpi_events_buttons.push_back(b);
    rpi_events_mutex.unlock();
}


void rpievents_registerinput_statechange(int pin, int ID, rpit_pullresistor_mode resistor_pull)
{
    rpievent_input_statechange b;
    b.pin=pin;
    b.ID=ID;
    b.last_state=1;
    rpit_setPinMode(pin, rpitpmDigitalInput, resistor_pull);
    rpi_events_mutex.lock();
    rpi_events_statechanges.push_back(b);
    rpi_events_mutex.unlock();
}


void rpievents_registerinput_rotaryscroll(int pinA, int pinB, int ID, rpit_pullresistor_mode resistor_pull, int steps_for_inc)
{
    rpievent_input_rotary_scroll b;
    b.pinA=pinA;
    b.pinB=pinB;
    b.ID=ID;
    b.last_state=-1;
    b.lastinc=0;
    b.steps_for_inc1=steps_for_inc;
    b.inc=0;
    b.lastevent=std::chrono::steady_clock::now();
    rpit_setPinMode(pinA, rpitpmDigitalInput, resistor_pull);
    rpit_setPinMode(pinB, rpitpmDigitalInput, resistor_pull);
    rpi_events_mutex_rotary.lock();
    rpi_events_rotaryscroll.push_back(b);
    rpi_events_mutex_rotary.unlock();
}
