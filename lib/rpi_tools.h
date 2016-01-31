#ifndef RPI_TOOLS_H
#define RPI_TOOLS_H
#include <string>

/** \brief execute the given unix command and read its output until the first '\\n' character or EOF */
std::string rpit_readlineFromCommand(const char* command);

/** \brief read the current CPU temperature */
float rpit_readCPUTemperatur();

enum rpit_pullresistor_mode {
    rpitprUP,
    rpitprDOWN,
    rpitprNONE
};

enum rpit_pin_mode {
    rpitpmDigitalInput,
    rpitpmDigitalOutput
};

/** \brief read a digital pin, using pull-up or -down resistor
 *
 *  \note this function sets the pull-up/down resistors and the pin state
 */
bool rpit_readDigital(int pin, rpit_pullresistor_mode pull_updown);
/** \brief read a digital pin, using pull-up or -down resistor
 *
 *  \note you have to configure the pin with rpit_setPinMode() before!
 */
bool rpit_readDigital(int pin);
/** \brief read a digital pin, using pull-up or -down resistor
 *
 *  \note you have to configure the pin with rpit_setPinMode() before!
 */
int rpit_readDigitalI(int pin);
/** \brief set the pull-up or -down resistor of a pin */
void rpit_setPullUpDownResistor(int pin, rpit_pullresistor_mode pull_updown=rpitprNONE);
/** \brief set the mode of a pin *
 *
 *  \note the pull-up/down resistor of an OUTPUT pin is initially always switched off! YOu can switch it on with rpit_setPullUpDownResistor().
 */
void rpit_setPinMode(int pin, rpit_pin_mode mode);
/** \brief set the mode and pull-up or -down resistor of a pin
 *
 *  \note the pull-up/down resistor of an OUTPUT pin is initially always switched off! YOu can switch it on with rpit_setPullUpDownResistor().
 */
void rpit_setPinMode(int pin, rpit_pin_mode mode, rpit_pullresistor_mode pull_updown);
/** \brief write a digital pin and set its mode to output before */
void rpit_writeDigitalSetMode(int pin, bool state);
/** \brief write a digital pin and set its mode to output before */
inline void rpit_writeDigitalSetMode(int pin, int state) {
    rpit_writeDigitalSetMode(pin, (state!=0));
}

/** \brief write a digital pin */
void rpit_writeDigital(int pin, bool state);
/** \brief write a digital pin */
inline void rpit_writeDigital(int pin, int state) {
    rpit_writeDigital(pin, (state!=0));
}
/** \brief use a pin for software-PWM output */
void rpit_initSoftPWM(int pin, int value=0, int maxVal=100);
/** \brief use a pin for software-PWM output */
void rpit_setSoftPWM(int pin, int value, int maxVal=100);

/** \brief initialize a background thread that reads the CPU temperature continuously
 *
 *  This solution is faster than rpit_readCPUTemperatur(), which can take relatively long.
 *
 *  \note This function has to be called before rpitemp_getCurrentTemperature() is used.
 */
void rpitemp_init();
/** \brief read the current CPU temperature from the background thread
 *
 *  \note You have to call rpitemp_init() before calling this function!
 */
float rpitemp_getCurrentCPUTemperature();
/** \brief deinit the reader thread for the CPU temperature */
void rpitemp_deinit();

/** \brief set the background intensity of a PiTFT 2.2" HAT display module using pin #18 in PWM mode (for value ]0..100[ or just on/off for 0 or 100 */
void pitft22hat_setBackgroundIntensity(float intensity_percent);

/** \brief has to be called before using any port-I/O functions! */
void rpit_initIO();

/** \brief initialize the soft-blink library */
void rpi_softblink_init();
/** \brief deinitialize the soft-blink library */
void rpi_softblink_deinit();
/** \brief register a pin for soft-blinking with given amplitude, offset and period (in milliseconds). the waveform is a sine, starting at the call of this function, output range is 0..100 */
void rpi_softblink_registerpin(int pin, float amplitude, float offset, float period_ms);
/** \brief set a new amplitude for an already registered pin, output range is 0..100 */
void rpi_softblink_set_amplitude(int pin, float amplitude);
/** \brief set a new offset for an already registered pin, output range is 0..100 */
void rpi_softblink_set_offset(int pin, float offset);
/** \brief set a new period (milliseconds) for an already registered pin */
void rpi_softblink_set_period(int pin, float period_ms);
/** \brief deregister a pin from soft-blinking */
void rpi_softblink_deregisterpin(int pin);

#endif // RPI_TOOLS_H
