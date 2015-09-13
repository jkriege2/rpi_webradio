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

/** \brief read a digital pin, using pull-up or -down resistor */
bool rpit_readDigital(int pin, rpit_pullresistor_mode pull_updown=rpitprNONE);
/** \brief write a digital pin */
void rpit_writeDigital(int pin, bool state);


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



#endif // RPI_TOOLS_H
