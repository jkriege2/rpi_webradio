
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <getopt.h>
#include <iostream>       
#include <thread>         
#include <chrono> 
#include <thread>
#include <mutex>
#include<cairo.h>

#include "framebuffer_cairo_tools.h"
#include "rpi_tools.h"
#include "rpi_cgevents.h"
#include "cgeventqueue.h"
#include "cgapplication.h"
#include "wrmainscreen.h"



int main(int argc, char *argv[])
{
    std::cout<<"WebradioGUI -- a cairo-based GUI for a webradio\n";
    std::cout<<"  (c) 2015-2016 by Jan W. Krieger\n\n\n";
    CGApplication app;
    if (!app.parseCommandline(argc, argv)) {
        // exit program, as e.g. "help" was encountered on the command line
        return EXIT_SUCCESS;
    }

    rpievents_registerinput_statechange(17, 17);
    rpievents_registerinput_buttonclick(22, 22, false, true);
    rpievents_registerinput_buttonclick(23, 23);
    rpievents_registerinput_buttonclick(27, 27, true, false, false);
    rpievents_registerinput_rotaryscroll(5,6,1);


    return app.start(new WRMainScreen(), true);
}




