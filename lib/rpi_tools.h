#ifndef RPI_TOOLS_H
#define RPI_TOOLS_H
#include <string>

/** \brief execute the given command and read its output until teh first '\\n' character or EOF */
std::string rpit_readlineFromCommand(const char* command);

/** \brief read the current CPU temperature */
float rpit_readCPUTemperatur();


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
