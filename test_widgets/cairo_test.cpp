
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

#include <wiringPi.h>


#define SIZEX 320
#define SIZEY 240
#define MAINLOOP_DELAY_MS 10
#define MAX_FRAMERATE_FPS 25

#include "framebuffer_cairo_tools.h"
#include "cgwidget.h"
#include "cgframe.h"
#include "cglabel.h"
#include "cgprogressbar.h"
#include "rpi_tools.h"
#include "cgscreen.h"
#include "cglistwidget.h"
#include "cgmultiscreens.h"
#include "cgtreewidget.h"
#include "cgimage.h"


fbcairo_context* context;

CGScreen* mainFrame=NULL;
CGScreen* mainFrame2=NULL;
CGScreen* mainFrame3=NULL;
CGLabel* lab1=NULL;
CGProgressBar* prog1=NULL;
CGProgressBar* prog2=NULL;
CGListWidget* lst=NULL;
CGMultiScreens* multi;
CGTreeWidget* tree;
CGImage* imgs[8];




void setupGUI() {

    multi=new CGMultiScreens(context);

    {
        mainFrame=multi->addScreen();//new CGScreen(context);
        //mainFrame->setBackgroundColor(CGColor::ccBlack);

        CGFrame* innerframe=new CGFrame(2,2,100,20, mainFrame);
        innerframe->setBackgroundColor(CGColor(50));
        innerframe->setFrameColor(CGColor(255,0,0));
        CGFrame* innerframe2=new CGFrame(2,2,50,10, innerframe);
        innerframe2->setBackgroundColor(CGColor(128));
        innerframe2->setFrameColor(CGColor(0,255,0));
        CGFrame* innerframe3=new CGFrame(10,30,100,35, mainFrame);
        innerframe3->setBackgroundColor(CGColor(200));
        innerframe3->setFrameColor(CGColor(0,0,128));
        lab1=new CGLabel(0,0,80,50, "text", innerframe3);
        //lab1->setBackgroundColor(CGColor(200));
        //lab1->setFrameColor(CGColor(0,0,128));
        lab1->setTextColor(CGColor(0,0,255));
        lab1->setBold(true);
        lab1->setFontFace("serif");

        prog1=new CGProgressBar(10,70,300,20,mainFrame);
        prog1->setRange(-1,1);
        prog1->setShowText(true);

        prog2=new CGProgressBar(10,92,300,20,mainFrame);
        prog2->setRange(-1,1);
        prog2->setShowText(false);

        lst=new CGListWidget(120,2,180,65,mainFrame);
        //lst->setBackgroundColor(CGColor::ccBlack);
        lst->setFrameWidth(3);
        //lst->setFrameColor(CGColor::ccRed);
        //lst->setTextColor(CGColor::ccWhite);
        //lst->setSelectedColor(CGColor::ccGray75);
        //lst->setSelectedTextColor(CGColor::ccBlack);
        lst->addItem("item 1");
        lst->addItem("item 2");
        lst->addItem("item 3");
        lst->addItem("item 4");
        lst->addItem("item 5");
        lst->addItem("item 6");
        lst->addItem("item 7");
        lst->addItem("item 8");
        lst->setCurrentItem(0);
        lst->setFontFace("serif");
        lst->setFontSize(12);

        for (int y=0; y<3; y++) {
            for (int x=0; x<3; x++) {
                CGLabel* lab=new CGLabel(2+x*105,125+y*35,100,30, "text\ntext2!!!", mainFrame);
                lab->setBackgroundColor(CGColor::ccGray25);
                lab->setFrameColor(CGColor::ccDarkblue);
                lab->setFontSize(9);
                lab->setTextColor(CGColor(255,0,0));
                if (x==0) lab->setHorizontalAlignment(cgalLeft);
                else if (x==1) lab->setHorizontalAlignment(cgalCenter);
                else if (x==2) lab->setHorizontalAlignment(cgalRight);
                if (y==0) lab->setVerticalAlignment(cgalLeft);
                else if (y==1) lab->setVerticalAlignment(cgalCenter);
                else if (y==2) lab->setVerticalAlignment(cgalRight);
                lab->setFrameWidth(3);
            }
        }
    }
    {
        mainFrame2=multi->addScreen();//new CGScreen(context);
        tree=new CGTreeWidget(10,10,mainFrame2->width()-20, mainFrame2->height()-50, mainFrame2);
        tree->setFontSize(15);


        for (int i=0; i<20; i++) {
            tree->addItem(cgFormat("item %d",i));
            if (i%4<3) {
                for (int j=0; j<10; j++) {
                    if (j%4<2) {
                        tree->lastItem()->addChild(cgFormat("subitem %d.%d",i,j));
                        for (int k=0; k<15; k++) {
                            tree->lastItem()->lastChild()->addChild(cgFormat("subsubitem %d.%d.%d",i,j,k));
                            for (int l=0; l<15; l++) {
                                tree->lastItem()->lastChild()->lastChild()->addChild(cgFormat("subsubsubitem %d.%d.%d.%d",i,j,k,l));
                            }
                        }
                    }
                }
            }
        }


    }
    {
        mainFrame3=multi->addScreen();
        int ww=(mainFrame2->width()-20)/2.0;
        int hh=(mainFrame2->height()-40)/4.0;
        int cnt=0;
        imgs[cnt]=new CGImage(10,10+hh*(cnt/2), ww, hh, mainFrame3);
        imgs[cnt]->setImagePNG("../images/lena.png");
        cnt++;
        imgs[cnt]=new CGImage(10+ww,10+hh*(cnt/2), ww, hh, mainFrame3);
        imgs[cnt]->setImagePNG("../images/lena.png");
        imgs[cnt]->setImageScaled(CGImage::smOriginal);
        cnt++;
        imgs[cnt]=new CGImage(10,10+hh*(cnt/2), ww, hh, mainFrame3);
        imgs[cnt]->setImagePNG("../images/lena.png");
        imgs[cnt]->setImageScaled(CGImage::smShrinkOnly);
        cnt++;
        imgs[cnt]=new CGImage(10+ww,10+hh*(cnt/2), ww, hh, mainFrame3);
        imgs[cnt]->setImagePNG("../images/lena.png");
        imgs[cnt]->setImageScaled(CGImage::smExpandOnly);
        cnt++;


        imgs[cnt]=new CGImage(10,10+hh*(cnt/2), ww, hh, mainFrame3);
        imgs[cnt]->setImagePNG("../images/icon.png");
        imgs[cnt]->setImageScaled(CGImage::smOriginal);
        cnt++;
        imgs[cnt]=new CGImage(10+ww,10+hh*(cnt/2), ww, hh, mainFrame3);
        imgs[cnt]->setImagePNG("../images/icon.png");
        imgs[cnt]->setImageScaled(CGImage::smOriginal);
        cnt++;
        imgs[cnt]=new CGImage(10,10+hh*(cnt/2), ww, hh, mainFrame3);
        imgs[cnt]->setImagePNG("../images/icon.png");
        imgs[cnt]->setImageScaled(CGImage::smShrinkOnly);
        cnt++;
        imgs[cnt]=new CGImage(10+ww,10+hh*(cnt/2), ww, hh, mainFrame3);
        imgs[cnt]->setImagePNG("../images/icon.png");
        imgs[cnt]->setImageScaled(CGImage::smExpandOnly);
        cnt++;
    }
}
void destroyGUI() {
    delete multi;
}



void paintGUI(cairo_t *c, float fps=0) {
    char txt[1024];
    static float txtBackgroundI=0;
    static int globcnt=400;
    static int cur=0;
    static int curInc=1;
    sprintf(txt, "%4.2f fps\n%3.1f degC\n%dXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", fps, rpitemp_getCurrentCPUTemperature(), globcnt);
    lab1->setText(txt);
    multi->paint(c);
    //pitft22hat_setBackgroundIntensity(((1.0+sin(2.0*M_PI*txtBackgroundI/50.0))/2.0)*900.0+100.0);
    //printf("%f\n", ((1.0+sin(2.0*M_PI*txtBackgroundI/50.0))/4.0+0.5)*1024.0);
    prog1->setValue(sin(2.0*M_PI*txtBackgroundI/50.0));
    prog2->setValue(cos(2.0*M_PI*txtBackgroundI/50.0));
    txtBackgroundI+=1;

    lst->setCurrentItem(cur/5);

    cur+=curInc;
    if (cur>=(int)lst->count()*5-1 || cur<=0) curInc*=-1;

    globcnt++;
    multi->setCurrentScreen(0);

    if (globcnt<=100) {
    } else if (globcnt>100 && globcnt<=400) {
        multi->setCurrentScreen(1);
        if (globcnt%5==0) {
            int rng=rand()%10;
            if (rng==0) {
                tree->upLevel();
            } else if (rng==9) {
                tree->downLevel();
            } else if (rng>=5) {
                tree->nextItem();
            } else {
                tree->prevItem();
            }
        }
    } else if (globcnt>400 && globcnt<=450) {
        multi->setCurrentScreen(2);

    } else {
        globcnt=0;
    }
    mainFrame->setTitle(cgFormat("screen %d/%d: %d", multi->currentScreenID()+1, multi->count(), globcnt));
    mainFrame2->setTitle(cgFormat("screen %d/%d: %d", multi->currentScreenID()+1, multi->count(), globcnt));

}


void prepareForMainloop() {
    if (!getuid()) {
        printf("running with root priviledges!\n");
        wiringPiSetupGpio();
    } else {
        printf("running in user mode!\n");
        wiringPiSetupSys ();
    }
    rpitemp_init();

    //std::cout<<"COLOR TEST:\n  ccBlack "<<CGColor(CGColor::ccBlack)<<"\n  ccWhite "<<CGColor(CGColor::ccWhite)<<"\n  ccRed "<<CGColor(CGColor::ccRed)<<"\n  ccGreen "<<CGColor(CGColor::ccGreen)<<"\n  ccBlue "<<CGColor(CGColor::ccBlue);
}

void cleanupAfterMainloop() {
    rpitemp_deinit();
}

void startMainLoop() {
	int y=10;
	
	// get cairo surface to draw onto
    cairo_surface_t* cs=fbcairo_getSurface(context);


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
            cairo_t *c=cairo_create(cs);
            paintGUI(c, fcnt/timespan_since_start.count());
            cairo_destroy(c);
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
    if (getenv("FRAMEBUFFER")) strcpy(fbname, getenv("FRAMEBUFFER"));
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




