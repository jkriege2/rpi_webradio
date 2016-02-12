#include "precomp.h"
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
#include "mpd_tools.h"
#include "global.h"



int main(int argc, char *argv[])
{
    std::cout<<"WebradioGUI -- a cairo-based GUI for a webradio using mpd for playback\n";
    std::cout<<"  (c) 2015-2016 by Jan W. Krieger\n\n\n";
    int res=0;
    {
        CGApplication app;
        if (!app.parseCommandline(argc, argv)) {
            // exit program, as e.g. "help" was encountered on the command line
            return EXIT_SUCCESS;
        }

        // init MPD library
        mpdtools& mpd=mpdtools::getInstance();

        //rpievents_registerinput_statechange(17, 17);
        //rpievents_registerinput_buttonclick(22, 22, false, true);
        //rpievents_registerinput_buttonclick(23, 23);
        //rpievents_registerinput_buttonclick(27, 27, true, false, false);
        rpievents_registerinput_rotaryscroll(ROTARY_MAIN_A,ROTARY_MAIN_B,ROTARY_MAIN);
        rpievents_registerinput_buttonclick(BTN_ROTARY_MAIN, BTN_ROTARY_MAIN);
        rpievents_registerinput_buttonclick(BTN_MAIN_EXIT, BTN_MAIN_EXIT);
        rpievents_registerinput_buttonclick(BTN_BACK, BTN_BACK);
        rpievents_registerinput_buttonclick(BTN_PLAY, BTN_PLAY);
        rpievents_registerinput_buttonclick(BTN_MAIN_CHOOSE_MODE, BTN_MAIN_CHOOSE_MODE);
        rpievents_registerinput_buttonclick(BTN_MUSIC_Q_NEXT, BTN_MUSIC_Q_NEXT);
        rpievents_registerinput_buttonclick(BTN_MUSIC_Q_PREV, BTN_MUSIC_Q_PREV);
        rpievents_registerinput_buttonclick(BTN_MUSIC_RANDOM, BTN_MUSIC_RANDOM);
        rpievents_registerinput_buttonclick(BTN_MUSIC_REPEAT, BTN_MUSIC_REPEAT);
        rpi_softblink_init();
        rpi_softblink_registerpin(LED_PLAY_BUTTON, LED_PLAY_BUTTON_OFF_AMPLITUDE, LED_PLAY_BUTTON_OFF_OFFSET, LED_PLAY_BUTTON_PERIOD_MS);




        res= app.start(new WRMainScreen(), true);
    }
    std::cout<<"finished mainloop ... exiting application ...\n";
    return res;
}




