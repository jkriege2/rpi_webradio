
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


#define SIZEX 320
#define SIZEY 240
#define MAINLOOP_DELAY_MS 10
#define MAX_FRAMERATE_FPS 25

#include "framebuffer_cairo_tools.h"
#include "cgwidget.h"
#include "cgframe.h"
#include "cglabel.h"
#include "rpi_tools.h"


fbcairo_context* context;

CGWidget* mainFrame=NULL;
CGLabel* lab1=NULL;

float cputemp=0;
std::thread* cputempthread=NULL;
std::mutex cputempmutex;
void cpuTempThread() {
    while(true) {
        cputempmutex.lock();
        cputemp=rpit_readCPUTemperatur();
        cputempmutex.unlock();
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }
}



void setupGUI() {

    mainFrame=new CGWidget(0,0,SIZEX,SIZEY);
    mainFrame->setBackgroundColor(CGColor::black());

    CGFrame* innerframe=new CGFrame(2,2,100,20, mainFrame);
    innerframe->setBackgroundColor(CGColor(50));
    innerframe->setFrameColor(CGColor(255,0,0));
    CGFrame* innerframe2=new CGFrame(2,2,50,10, innerframe);
    innerframe2->setBackgroundColor(CGColor(128));
    innerframe2->setFrameColor(CGColor(0,255,0));
    CGFrame* innerframe3=new CGFrame(110,30,100,30, mainFrame);
    innerframe3->setBackgroundColor(CGColor(200));
    innerframe3->setFrameColor(CGColor(0,0,128));
    lab1=new CGLabel(0,0,80,16, "text", innerframe3);
    //lab1->setBackgroundColor(CGColor(200));
    //lab1->setFrameColor(CGColor(0,0,128));
    lab1->setTextColor(CGColor(0,0,255));
    lab1->setBold(true);

    for (int y=0; y<3; y++) {
        for (int x=0; x<3; x++) {
            CGLabel* lab=new CGLabel(2+x*105,100+y*35,100,30, "text\ntext2!!!", mainFrame);
            lab->setBackgroundColor(CGColor(50));
            lab->setFrameColor(CGColor(0,0,128));
            lab->setFontSize(8);
            lab->setTextColor(CGColor(255,0,0));
            if (x==0) lab->setHorizontalAlignment(CGLabel::alLeft);
            else if (x==1) lab->setHorizontalAlignment(CGLabel::alCenter);
            else if (x==2) lab->setHorizontalAlignment(CGLabel::alRight);
            if (y==0) lab->setVerticalAlignment(CGLabel::alLeft);
            else if (y==1) lab->setVerticalAlignment(CGLabel::alCenter);
            else if (y==2) lab->setVerticalAlignment(CGLabel::alRight);
            lab->setFrameWidth(1.5);
        }
    }

}
void destroyGUI() {
    delete mainFrame;
}



void paintGUI(cairo_t *c, float fps=0) {
    char txt[1024];
    cputempmutex.lock();
    sprintf(txt, "%4.2f fps\n%3.1f degC", fps, cputemp);
    cputempmutex.unlock();
    //std::cout<<txt<<std::endl;
    lab1->setText(txt);
    mainFrame->paint(c);
}

void paint(cairo_t *c, float textpos=10, float fps=0)
{
	cairo_rectangle(c, 0.0, 0.0, SIZEX, SIZEY);
	cairo_set_source_rgb(c, 0.0, 0.0, 0.5);
	cairo_fill(c);

	cairo_move_to(c, 10.0, textpos);
	cairo_set_source_rgb(c, 1.0, 1.0, 0.0);
	cairo_show_text(c, "Hello World!");
	cairo_move_to(c, 150, 10);
	cairo_set_source_rgb(c, 1.0, 0.0, 0.0);
	char txt[1024];
	sprintf(txt, "%f fps", fps);
	cairo_show_text(c, txt);
	
	cairo_show_page(c);

	
}


void prepareForMainloop() {
    cputempthread=new std::thread(cpuTempThread);
}

void cleanupAfterMainloop() {
    delete cputempthread;
}

void startMainLoop() {
	int y=10;
	
	// get cairo surface to draw onto
    cairo_surface_t* cs=fbcairo_getSurface(context);
	cairo_t *c=cairo_create(cs);


	std::chrono::steady_clock::time_point tlastpaint = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point tstart = std::chrono::steady_clock::now();
	double fcnt=0;
	while (true) { // endless event loop
	
	    // get current time
		std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
	
	    // paint the screen
		std::chrono::duration<double> timespan_since_last_paint = std::chrono::duration_cast<std::chrono::duration<double>>(t - tlastpaint);
		if (timespan_since_last_paint.count()>1.0/double(MAX_FRAMERATE_FPS)) {
			std::chrono::duration<double> timespan_since_start = std::chrono::duration_cast<std::chrono::duration<double>>(t - tstart);
			fcnt++;
            paintGUI(c, fcnt/timespan_since_start.count());
            fbcairo_copyDoubleBuffer(context);
			tlastpaint = std::chrono::steady_clock::now();
			if (fcnt>0xFFFFFF) {
				fcnt=0;
				tstart = std::chrono::steady_clock::now();
			}

		}
		
		
		// maintenance
		y++;
		if (y>SIZEY) y=10;
		
		// sleep a bit, so not 100% processor time are used ...
		std::this_thread::sleep_for (std::chrono::milliseconds(MAINLOOP_DELAY_MS));
	}
	cairo_destroy(c);
}

void print_usage() {
    printf("Usage: cairo_test [options]\n");
    printf("Options: \n");
    printf("    --help -?:                            help message \n");
    printf("    --framebuffer -f FRAMEBUFFER_DEVICE:  use specific framebufer for output\n");
    printf("    --no-doublebuffer:                    don't use double-buffering\n");
    printf("\n");
}

int main(int argc, char *argv[])
{
	int opt= 0;
	
	char fbname[1024]="/dev/fb1";
	strcpy(fbname, getenv("FRAMEBUFFER"));
	if (strlen(fbname)<=0) strcpy(fbname, "/div/fb0");
    int mode=FBC_DOUBLEBUFFER;
	
	

    //Specifying the expected options
    //The two options l and b expect numbers as argument
    static struct option long_options[] = {
        {"help",           no_argument,       0,  '?' },
        {"framebuffer",    required_argument, 0,  'f' },
        {"no-doublebuffer",no_argument,       0,  's' },
        {0,           0,                      0,  0   }
    };

    int long_index =0;
    while ((opt = getopt_long(argc, argv,"?sf:", long_options, &long_index )) != -1) {
        switch (opt) {
            case '?' : 
			    print_usage(); 
                exit(EXIT_SUCCESS);
                break;
            case 'f' : strcpy(fbname, optarg);
                break;
            case 's' : mode=FBC_DIRECT;
                break;
            default: print_usage();
                exit(EXIT_FAILURE);
        }
    }
 	
	
	
	
	
	
	
	// bind framebuffer to cairo
	printf("binding framebuffer '%s' to cairo ...\n", fbname);
    if (mode==FBC_DOUBLEBUFFER) printf("   using double-buffering\n");
    else printf("   using direct drawing (no double-buffering)\n");
    context = fbcairo_bind(fbname, mode);
	
    if (context) {
		int xres=-1, yres=-1;
		char RGB[100];
        fbcairo_getInfo(context, &xres, &yres, NULL, RGB);
		printf("Device Info:\n   %dx%d pixels, %s\n\n", xres, yres, RGB);
        prepareForMainloop();
        setupGUI();
		startMainLoop();
        destroyGUI();
        cleanupAfterMainloop();
        fbcairo_unbind(context);
	} else {
		fprintf(stderr, "ERROR: could not open framebuffer for cairo!\n");
	}

	return 0;
}




