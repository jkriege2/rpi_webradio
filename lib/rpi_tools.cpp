#include "rpi_tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <regex>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

std::string rpit_readlineFromCommand(const char *command)
{
    FILE *lsofFile_p = popen(command, "r");

    if (!lsofFile_p)
    {
      return std::string();
    }

    char buffer[4096];
    char *line_p = fgets(buffer, sizeof(buffer), lsofFile_p);
    pclose(lsofFile_p);
    return std::string(line_p);
}


float rpit_readCPUTemperatur()
{
    std::string t=rpit_readlineFromCommand("vcgencmd measure_temp");
    std::string num;
    bool state=0;
    for (size_t i=0; i<t.size(); i++) {
        if (state==0) {
            switch (t[i]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state=1;
                    num.push_back(t[i]);
                    break;
                default: break;
            }
        } else if (state==1) {
            switch (t[i]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case'.':
                    num.push_back(t[i]);
                    break;
                default:
                    state=2;
                    break;
            }
        } else {
            break;
        }
    }
    //std::cout<<t<<"  => "<<num<<" => "<<atof(num.c_str())<<"\n\n\n";
    return atof(num.c_str());

}


float rpi_temperature_cputemptemperature=0;
bool rpi_temperature_stop_thread=false;
std::thread* rpi_temperature_cputempthread=NULL;
std::mutex rpi_temperature_cputempmutex;

void rpi_temperature_cpuTempThread() {
    bool done=false;
    while(!done) {
        // read temperature every 500ms
        rpi_temperature_cputempmutex.lock();
        rpi_temperature_cputemptemperature=rpit_readCPUTemperatur();
        rpi_temperature_cputempmutex.unlock();

        // check for DONE-signal every 50ms
        for (int i=0; i<10; i++) {
            std::this_thread::sleep_for (std::chrono::milliseconds(50));
            rpi_temperature_cputempmutex.lock();
            if (rpi_temperature_stop_thread) done=true;
            rpi_temperature_cputempmutex.unlock();
            if (done) break;
        }
    }
}


void rpitemp_init()
{
    if (!rpi_temperature_cputempthread) {
        rpi_temperature_cputemptemperature=rpit_readCPUTemperatur();
        rpi_temperature_cputempthread=new std::thread(rpi_temperature_cpuTempThread);
    }
}


float rpitemp_getCurrentCPUTemperature()
{
    if (!rpi_temperature_cputempthread) rpitemp_init();
    rpi_temperature_cputempmutex.lock();
    float res=rpi_temperature_cputemptemperature;
    rpi_temperature_cputempmutex.unlock();
    return res;
}


void rpitemp_deinit()
{
    if (rpi_temperature_cputempthread) {
        rpi_temperature_cputempmutex.lock();
        rpi_temperature_stop_thread=true;
        rpi_temperature_cputempmutex.unlock();
        rpi_temperature_cputempthread->join();
        delete rpi_temperature_cputempthread;
        rpi_temperature_cputempthread=NULL;
        rpi_temperature_cputemptemperature=0.0f;
    }
}


void pitft22hat_setBackgroundIntensity(float intensity_percent)
{
    float I=intensity_percent;
    if (I<0.0) I=0.0;
    if (I>100.0) I=100.0;
    if (I==0.0) {
        pinMode(18, OUTPUT);
        digitalWrite(18, 0);
    } else if (I==100.0) {
        pinMode(18, OUTPUT);
        digitalWrite(18, 1);
    } else {
        pinMode(18, PWM_OUTPUT);
        pwmWrite(18, round(I/100.0*1024.0));
    }

}


bool rpit_readDigital(int pin, rpit_pullresistor_mode pull_updown)
{
    pinMode(pin, INPUT);
    if (pull_updown==rpitprNONE) pullUpDnControl(pin, PUD_OFF);
    else if (pull_updown==rpitprUP) pullUpDnControl(pin, PUD_UP);
    else if (pull_updown==rpitprDOWN) pullUpDnControl(pin, PUD_DOWN);
    return (digitalRead(pin)!=0);
}





void rpit_setPullUpDownResistor(int pin, rpit_pullresistor_mode pull_updown)
{
    if (pull_updown==rpitprNONE) pullUpDnControl(pin, PUD_OFF);
    else if (pull_updown==rpitprUP) pullUpDnControl(pin, PUD_UP);
    else if (pull_updown==rpitprDOWN) pullUpDnControl(pin, PUD_DOWN);
}


void rpit_setPinMode(int pin, rpit_pin_mode mode)
{
    if (mode==rpitpmDigitalInput) pinMode(pin, INPUT);
    else if (mode==rpitpmDigitalOutput) {
        pullUpDnControl(pin, PUD_OFF);
        pinMode(pin, OUTPUT);
    }
}


void rpit_setPinMode(int pin, rpit_pin_mode mode, rpit_pullresistor_mode pull_updown)
{
    if (mode==rpitpmDigitalInput) pinMode(pin, INPUT);
    else if (mode==rpitpmDigitalOutput) pinMode(pin, OUTPUT);
    if (mode==rpitpmDigitalInput) {
        if (pull_updown==rpitprNONE) pullUpDnControl(pin, PUD_OFF);
        else if (pull_updown==rpitprUP) pullUpDnControl(pin, PUD_UP);
        else if (pull_updown==rpitprDOWN) pullUpDnControl(pin, PUD_DOWN);
    }

}


int rpit_readDigitalI(int pin)
{
    return digitalRead(pin);
}


bool rpit_readDigital(int pin)
{
    return (digitalRead(pin)==1);
}


void rpit_writeDigital(int pin, bool state)
{
    digitalWrite(pin, state?HIGH:LOW);
}



void rpit_writeDigitalSetMode(int pin, bool state)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, state?HIGH:LOW);
}


void rpit_initIO()
{
    if (!getuid()) {
        printf("running WiringLIB with root priviledges!\n");
        wiringPiSetupGpio();
    } else {
        printf("running WiringLIB in user mode!\n");
        wiringPiSetupSys ();
    }
}


void rpit_initSoftPWM(int pin, int value, int maxVal)
{
    if (value<0) value=0;
    if (value>maxVal) value=maxVal;
    softPwmCreate(pin, value, maxVal);
}


void rpit_setSoftPWM(int pin, int value, int maxVal)
{
    if (value<0) value=0;
    if (value>maxVal) value=maxVal;
    softPwmWrite (pin, value);
}







#define SOFTBLINK_FACTOR 1

struct rpi_softblink_data {
    int pin;
    float offset;
    float amplitude;
    float period_ms;
    std::chrono::steady_clock::time_point start;
    float since_start_ms(const std::chrono::steady_clock::time_point& tnow) const {
        return std::chrono::duration_cast<std::chrono::duration<float,std::milli> >(tnow - start).count();
    }
};
std::thread* rpi_softblink_thread=NULL;
std::mutex rpi_softblink_mutex;
std::vector<rpi_softblink_data> rpi_softblink_pins;
std::atomic<bool> rpi_softblink_stop;

void rpi_softblink_threadfunc() {
    bool done=false;
    while(!done) {
        rpi_softblink_mutex.lock();
        const std::chrono::steady_clock::time_point tnow=std::chrono::steady_clock::now();
        for (rpi_softblink_data& it: rpi_softblink_pins) {
            int value=float(SOFTBLINK_FACTOR)*(it.offset+it.amplitude*cos(2.0*M_PI*it.since_start_ms(tnow)/it.period_ms));
            if (value<0) value=0;
            if (value>SOFTBLINK_FACTOR*100) value=SOFTBLINK_FACTOR*100;
            rpit_setSoftPWM(it.pin, value, SOFTBLINK_FACTOR*100);
        }
        rpi_softblink_mutex.unlock();

        // check for DONE-signal every XXms
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (rpi_softblink_stop.load()) {
            done=true;
        }
        if (done) break;
    }
}


void rpi_softblink_init()
{
    if (!rpi_softblink_thread) {
        rpi_softblink_thread=new std::thread(rpi_softblink_threadfunc);
    }
}


void rpi_softblink_deinit()
{
    if (rpi_softblink_thread) {
        rpi_softblink_stop=true;
        rpi_softblink_thread->join();
        delete rpi_softblink_thread;
        rpi_softblink_thread=NULL;
    }
}

void rpi_softblink_registerpin(int pin, float amplitude, float offset, float period_ms)
{
    rpi_softblink_mutex.lock();
    int idx=-1;
    for (size_t i=0; i<rpi_softblink_pins.size(); i++) {
        if (rpi_softblink_pins[i].pin==pin) {
            idx=i;
            break;
        }
    }
    if (idx<0) {
        rpi_softblink_pins.push_back(rpi_softblink_data());
        idx=rpi_softblink_pins.size()-1;
    }
    rpit_initSoftPWM(pin, 0, SOFTBLINK_FACTOR*100);
    rpi_softblink_pins[idx].start=std::chrono::steady_clock::now();
    rpi_softblink_pins[idx].pin=pin;
    rpi_softblink_pins[idx].amplitude=amplitude;
    rpi_softblink_pins[idx].offset=offset;
    rpi_softblink_pins[idx].period_ms=period_ms;
    rpi_softblink_mutex.unlock();
}

void rpi_softblink_set_amplitude(int pin, float amplitude)
{
    rpi_softblink_mutex.lock();
    int idx=-1;
    for (size_t i=0; i<rpi_softblink_pins.size(); i++) {
        if (rpi_softblink_pins[i].pin==pin) {
            idx=i;
            break;
        }
    }
    if (idx>=0) {
        rpi_softblink_pins[idx].amplitude=amplitude;
    }
    rpi_softblink_mutex.unlock();
}

void rpi_softblink_set_offset(int pin, float offset)
{
    rpi_softblink_mutex.lock();
    int idx=-1;
    for (size_t i=0; i<rpi_softblink_pins.size(); i++) {
        if (rpi_softblink_pins[i].pin==pin) {
            idx=i;
            break;
        }
    }
    if (idx>=0) {
        rpi_softblink_pins[idx].offset=offset;
    }
    rpi_softblink_mutex.unlock();
}

void rpi_softblink_set_period(int pin, float period_ms)
{
    rpi_softblink_mutex.lock();
    int idx=-1;
    for (size_t i=0; i<rpi_softblink_pins.size(); i++) {
        if (rpi_softblink_pins[i].pin==pin) {
            idx=i;
            break;
        }
    }
    if (idx>=0) {
        rpi_softblink_pins[idx].period_ms=period_ms;
    }
    rpi_softblink_mutex.unlock();
}

void rpi_softblink_deregisterpin(int pin)
{
    rpi_softblink_mutex.lock();
    int idx=-1;
    for (size_t i=0; i<rpi_softblink_pins.size(); i++) {
        if (rpi_softblink_pins[i].pin==pin) {
            idx=i;
            break;
        }
    }
    if (idx>=0) {
        rpi_softblink_pins.erase(rpi_softblink_pins.begin()+idx);
    }
    rpi_softblink_mutex.unlock();
}
