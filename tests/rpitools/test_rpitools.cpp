
#include <cmath>
#include <iostream>       
#include <string>

#include "rpi_tools.h"



int main(int argc, char *argv[])
{
    std::cout<<"\n\n======================================================\n";
    std::cout<<"= TEST RPI_TOOLS Library                             =\n";
    std::cout<<"======================================================\n";
    std::cout<<"CPU-temp: "<<rpit_readCPUTemperatur()<<" degC\n";
    std::cout<<"------------------------------------------------------\n";
    RPI_BMP180 bmp;
    std::cout<<"rpi_bmp085.readPressure() = "<<bmp.readPressurePa()/100.0<<" hPa\n";
    std::cout<<"rpi_bmp085.readTemperature() = "<<bmp.readTemperature()<<" degC\n";
    std::cout<<"======================================================\n\n\n";
}


