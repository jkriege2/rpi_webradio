#include "rpi_tools.h"
#include <stdlib.h>
#include <stdio.h>
#include <regex>
#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <chrono>
#include <atomic>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>

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
        pwmWrite(18, std::round(I/100.0*1024.0));
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
	rpi_softblink_pins.erase(std::remove_if(rpi_softblink_pins.begin(), rpi_softblink_pins.end(), [pin](const rpi_softblink_data& d) { return d.pin==pin; }));
    rpi_softblink_mutex.unlock();
}


float rpi_bmp085_readPressure(int adress)
{
    RPI_BMP180 bmp(adress);
    return 0;
}

// based on: https://github.com/dkorunic/rpi-home-sensors/blob/master/Adafruit_BMP085.py

#define __BMP085_CONTROL           0xF4
#define __BMP085_TEMPDATA          0xF6
#define __BMP085_PRESSUREDATA      0xF6
#define __BMP085_READTEMPCMD       0x2E
#define __BMP085_READPRESSURECMD   0x34
#define __BMP085_CAL_AC1           0xAA
#define __BMP085_CAL_AC2           0xAC
#define __BMP085_CAL_AC3           0xAE
#define __BMP085_CAL_AC4           0xB0
#define __BMP085_CAL_AC5           0xB2
#define __BMP085_CAL_AC6           0xB4
#define __BMP085_CAL_B1            0xB6
#define __BMP085_CAL_B2            0xB8
#define __BMP085_CAL_MB            0xBA
#define __BMP085_CAL_MC            0xBC
#define __BMP085_CAL_MD            0xBE
// Operating Modes
#define __BMP085_ULTRALOWPOWER     0
#define __BMP085_STANDARD          1
#define __BMP085_HIGHRES           2
#define __BMP085_ULTRAHIGHRES      3
#define RPI_BMP085_MODE __BMP085_STANDARD

inline uint16_t CAST_UINT16(int16_t integ) {
    return (*((uint16_t*)(&integ)));
}


RPI_BMP180::RPI_BMP180(uint8_t adress):
    m_adress(adress)
{
    readCalibrationdata();
}

int RPI_BMP180::I2CReadReg16(int fd, int reg) {
    uint16_t msb = CAST_UINT16(wiringPiI2CReadReg8(fd, reg));
    uint16_t lsb = CAST_UINT16(wiringPiI2CReadReg8(fd, reg+1));
    return (msb<<8)+lsb;
}

void RPI_BMP180::readCalibrationdata()
{
    int fd=wiringPiI2CSetup(m_adress);
    _CAL_AC1=I2CReadReg16(fd, __BMP085_CAL_AC1);
    _CAL_AC2=I2CReadReg16(fd, __BMP085_CAL_AC2);
    _CAL_AC3=I2CReadReg16(fd, __BMP085_CAL_AC3);
    _CAL_AC4=CAST_UINT16(I2CReadReg16(fd, __BMP085_CAL_AC4));
    _CAL_AC5=CAST_UINT16(I2CReadReg16(fd, __BMP085_CAL_AC5));
    _CAL_AC6=CAST_UINT16(I2CReadReg16(fd, __BMP085_CAL_AC6));
    _CAL_B1=I2CReadReg16(fd, __BMP085_CAL_B1);
    _CAL_B2=I2CReadReg16(fd, __BMP085_CAL_B2);
    _CAL_MB=I2CReadReg16(fd, __BMP085_CAL_MB);
    _CAL_MC=I2CReadReg16(fd, __BMP085_CAL_MC);
    _CAL_MD=I2CReadReg16(fd, __BMP085_CAL_MD);

    /*std::cout<<"\n _CAL_AC1="<<_CAL_AC1
            <<"\n _CAL_AC2="<<_CAL_AC2
            <<"\n _CAL_AC3="<<_CAL_AC3
            <<"\n _CAL_AC4="<<_CAL_AC4
            <<"\n _CAL_AC5="<<_CAL_AC5
            <<"\n _CAL_AC6="<<_CAL_AC6
            <<"\n _CAL_B1="<<_CAL_B1
            <<"\n _CAL_B2="<<_CAL_B2
            <<"\n _CAL_MB="<<_CAL_MB
            <<"\n _CAL_MC="<<_CAL_MC
            <<"\n _CAL_MD="<<_CAL_MD
            <<"\n\n";*/
}


uint16_t RPI_BMP180::readRawTemp() {
    //"Reads the raw (uncompensated) temperature from the sensor"
    int fd=wiringPiI2CSetup(m_adress);
    wiringPiI2CWriteReg8(fd, __BMP085_CONTROL, __BMP085_READTEMPCMD);
    std::this_thread::sleep_for (std::chrono::milliseconds(5)); // Wait 5ms
    uint16_t msb = CAST_UINT16(wiringPiI2CReadReg8(fd, __BMP085_TEMPDATA));
    uint16_t lsb = CAST_UINT16(wiringPiI2CReadReg8(fd, __BMP085_TEMPDATA+1));
    return (msb<<8)+lsb;
}

uint32_t RPI_BMP180::readRawPressure() {
    // "Reads the raw (uncompensated) pressure level from the sensor"
    int fd=wiringPiI2CSetup(m_adress);
    wiringPiI2CWriteReg8(fd, __BMP085_CONTROL, __BMP085_READPRESSURECMD+(RPI_BMP085_MODE<<6));
    std::this_thread::sleep_for (std::chrono::milliseconds(10+RPI_BMP085_MODE*10)); // Wait 5ms
    CAST_UINT16(I2CReadReg16(fd, __BMP085_TEMPDATA));

    uint16_t msb = CAST_UINT16(wiringPiI2CReadReg8(fd, __BMP085_PRESSUREDATA));
    uint16_t lsb = CAST_UINT16(wiringPiI2CReadReg8(fd, __BMP085_PRESSUREDATA+1));
    uint16_t xlsb = CAST_UINT16(wiringPiI2CReadReg8(fd, __BMP085_PRESSUREDATA+2));
    uint32_t raw = ((msb << 16) + (lsb << 8) + xlsb) >> (8 - RPI_BMP085_MODE);
    return raw;
}

float RPI_BMP180::readTemperature() {
    //"Gets the compensated temperature in degrees celcius"

    //# Read raw temp before aligning it with the calibration values
    int32_t UT = readRawTemp();
    int32_t X1 = ((UT - _CAL_AC6) * _CAL_AC5) >> 15;
    int32_t X2 = (_CAL_MC << 11) / (X1 + _CAL_MD);
    int32_t B5 = X1 + X2;
    //std::cout<<"\n\nUT="<<UT<<"  X1="<<X1<<"  X2="<<X2<<"  B5="<<B5<<"\n\n";
    return float((B5 + 8) >> 4) / 10.0;
}

float RPI_BMP180::readPressurePa() {
    //"Gets the compensated pressure in pascal"
    int32_t UT = 0;
    int32_t UP = 0;
    int32_t B3 = 0;
    int32_t B5 = 0;
    int32_t B6 = 0;
    int32_t X1 = 0;
    int32_t X2 = 0;
    int32_t X3 = 0;
    int32_t p = 0;
    uint32_t B4 = 0;
    int32_t B7 = 0;

    UT = readRawTemp();
    UP = readRawPressure();
    //std::cout<<"\n\nUT="<<UT<<"  UP="<<UP<<"\n\n";

    // True Temperature Calculations
    X1 = ((UT - _CAL_AC6) * _CAL_AC5) >> 15;
    X2 = (_CAL_MC << 11) / (X1 + _CAL_MD);
    B5 = X1 + X2;

    //# Pressure Calculations
    B6 = B5 - 4000;
    X1 = (_CAL_B2 * (B6 * B6) >> 12) >> 11;
    X2 = (_CAL_AC2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = (((_CAL_AC1 * 4 + X3) << RPI_BMP085_MODE) + 2) / 4;

    X1 = (_CAL_AC3 * B6) >> 13;
    X2 = (_CAL_B1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = (_CAL_AC4 * (X3 + 32768)) >> 15;
    B7 = (UP - B3) * (50000 >> RPI_BMP085_MODE);

    if (B7 < 0x80000000) {
      p = (B7 * 2) / B4;
    } else {
      p = (B7 / B4) * 2;
    }

    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;

    return p + ((X1 + X2 + 3791) >> 4);
}
