#include "cgprecomp.h"
#include "cgapplication.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include "framebuffer_cairo_tools.h"
#include "rpi_tools.h"
#include "rpi_cgevents.h"
#include "cgeventqueue.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <pwd.h>
#include <iostream>
#include <chrono>
#include <thread>

std::atomic<CGApplication*> CGApplication::fs_app(NULL);
boost::program_options::options_description CGApplication::m_optdesc("Allowed options");


CGApplication::CGApplication():
    m_optmap(),
    m_close_flag(false),
    m_framebuffer("/dev/fb1"),
    m_noDoubleBuffer(false),
    m_mainScreen(NULL),
    m_context(NULL),
    m_ownsMainScreen(false),
    m_fps(0),
    m_maxFramerate(25),
    m_mainloopDelay(10),
    m_exename("cgapp"),
    m_rotated(false)
{
    if (m_optdesc.find_nothrow("help", true)==NULL) {
        m_optdesc.add_options()
            ("help,?",            "produce help message")
            ("framebuffer,f",     boost::program_options::value<std::string>(&m_framebuffer)->default_value(m_framebuffer),   "set the framebuffer-file to use for the GUI")
            ("no-doublebuffer,s", boost::program_options::bool_switch(&m_noDoubleBuffer)->default_value(false), "don't use double-buffering")
            ("rotated,r",         boost::program_options::bool_switch(&m_rotated)->default_value(false), "rotate screen")
            ("mainloop-delay-ms", boost::program_options::value<int>(&m_mainloopDelay)->default_value(m_mainloopDelay), "delay after paint in the main-loop (in milliseconds)")
            ("max-framerate",     boost::program_options::value<int>(&m_maxFramerate)->default_value(m_maxFramerate), "maximum framerate for GUI (actual framerate may be lower!)")
        ;
    }



    rpit_initIO();
    rpievents_init();

    if (fs_app.load()==NULL) {
        CGApplication* newp=this;
        CGApplication* oldp=NULL;
        fs_app.compare_exchange_strong(oldp, newp);
    }
}

CGApplication::CGApplication(bool rotated):
    CGApplication()
{
    m_rotated=rotated;
}

CGApplication::~CGApplication()
{
    saveINIFile("~/."+m_exename+"/"+m_exename+".ini");
    CGEventQueue::registerMainWidget(NULL);
    if (fs_app.load()==this) {
        fs_app=NULL;
    }
    if (m_ownsMainScreen && m_mainScreen) {
        delete m_mainScreen;
        m_mainScreen=NULL;
    }
}

bool CGApplication::parseCommandline(int argc, char *argv[])
{
    if (argc>0) {
        boost::filesystem::path p(argv[0]);
        m_exename=p.filename().string();
    }
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, m_optdesc), m_optmap);
        boost::program_options::notify(m_optmap);
    } catch (...) {
        std::cout << "ERROR WHILE PARSING COMMAND-LINE PARAMETERS\n";
        std::cout << m_optdesc << "\n";
        return false;
    }

    if (m_optmap.count("help")) {
        std::cout <<"Allowed command-line options\n";
        std::cout << m_optdesc << "\n";
        return false;
    }

    parseINIFile("~/."+m_exename+"/"+m_exename+".ini");
    return true;
}


CGApplication *CGApplication::getInstanceP()
{
    return fs_app.load();
}

CGApplication &CGApplication::getInstance()
{
    return *(fs_app.load());
}

void CGApplication::saveINI()
{
    saveINIFile("~/."+m_exename+"/"+m_exename+".ini");
}

int CGApplication::start(CGScreen *mainScreen, bool ownsMainScreen)
{
    this->m_ownsMainScreen=ownsMainScreen;
    m_mainScreen=mainScreen;
    printf("binding framebuffer '%s' to cairo ...\n", m_framebuffer.c_str());
    if (!m_noDoubleBuffer) printf("   using double-buffering\n");
    else                   printf("   using direct drawing (no double-buffering)\n");

    // init framebuffer and application
    if (m_context) {
        fbcairo_unbind(m_context);
        m_context=NULL;
    }
    m_context = fbcairo_bind(m_framebuffer.c_str(), m_noDoubleBuffer?FBC_DIRECT:FBC_DOUBLEBUFFER, m_rotated);
    if (m_context) {
        int xres=-1, yres=-1;
        char RGB[100];
        fbcairo_getInfo(m_context, &xres, &yres, NULL, RGB);
        printf("Device Info:\n   %dx%d pixels, %s\n\n", xres, yres, RGB);
        if (m_mainScreen) {
            m_mainScreen->resizeFromContext(m_context);
            CGEventQueue::registerMainWidget(m_mainScreen);
            m_mainScreen->showScreen();
        }

        // main loop
        mainLoop();

        if (m_mainScreen) {
            m_mainScreen->hideScreen();
        }

        // de-init after mainloop
        rpievents_deinit();
        rpitemp_deinit();
        fbcairo_unbind(m_context);
        m_context=NULL;
        saveINIFile("~/."+m_exename+"/"+m_exename+".ini");
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "ERROR: could not open framebuffer for cairo!\n");
        return EXIT_FAILURE;
    }
}

void CGApplication::exit()
{
    m_close_flag=true;
}

void CGApplication::parseINIFile(const std::string &fn)
{
    std::string filename=fn;
    if (filename.size()>0 && filename[0]=='~') {
        const char* home=std::getenv("HOME");
        if (!home) home = getpwuid(getuid())->pw_dir;
        if (home) {

            filename.erase(0,1);
            filename=std::string(home)+"/"+filename;
            std::cout<<"  homedir is: "<<home<<"\n";
        }
    }
    if (!boost::filesystem::exists(boost::filesystem::path(filename))) return;
    std::cout<<"parsing ini-file from '"<<filename<<"' ... \n";
    try {
        using boost::property_tree::ptree;

        read_ini(filename, m_props);
    } catch (std::exception& E) {
        std::cout<<"  error: "<<E.what()<<"\n";
    }
    std::cout<<"parsing ini-file from '"<<filename<<"' ... DONE!\n";
}

void CGApplication::saveINIFile(const std::string &fn)
{
    std::string filename=fn;
    if (filename.size()>0 && filename[0]=='~') {
        const char* home=std::getenv("HOME");
        if (!home) home = getpwuid(getuid())->pw_dir;
        if (home) {
            filename.erase(0,1);
            filename=std::string(home)+"/"+filename;
            std::cout<<"  homedir is: "<<home<<"\n";
        }
    }

    std::cout<<"saving ini-file to '"<<filename<<"' ... \n";
    try {
        using boost::property_tree::ptree;
        boost::filesystem::path p(filename);
        std::string fn=p.string();
        p.remove_filename();
        create_directories(p);
        write_ini(fn, m_props);
        std::cout<<"   "<<fn<<"\n";
    } catch (std::exception& E) {
        std::cout<<"  error: "<<E.what()<<"\n";
    }
    std::cout<<"saving ini-file to '"<<filename<<"' ... DONE!\n";
}

void CGApplication::mainLoop()
{
    m_close_flag=false;

    // get cairo surface to draw onto
    //cairo_surface_t* cs=fbcairo_getSurface(m_context);


    std::chrono::steady_clock::time_point tlastpaint = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point tstart = std::chrono::steady_clock::now();
    double fcnt=0;
    while (!m_close_flag.load()) { // endless event loop

        // get current time
        std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();

        // deploy events
        CGEventQueue::deployEvents();


        // paint the screen
        std::chrono::duration<double> timespan_since_last_paint = std::chrono::duration_cast<std::chrono::duration<double>>(t - tlastpaint);
        if (timespan_since_last_paint.count()>1.0/double(m_maxFramerate)) {
            std::chrono::duration<double> timespan_since_start = std::chrono::duration_cast<std::chrono::duration<double>>(t - tstart);
            fcnt++;
            // create cairo_t object for drawing operations
            cairo_t *c=fbcairo_create(m_context);//cairo_create(cs);
            m_fps=fcnt/timespan_since_start.count();
            paintGUI(c, m_fps);
            fbcairo_destroy(m_context, c);
            fbcairo_copyDoubleBuffer(m_context);
            tlastpaint = std::chrono::steady_clock::now();
            if (fcnt>=0xFFFFFF) {
                fcnt=0;
                tstart = std::chrono::steady_clock::now();
            }

        }

        // sleep a bit, so not 100% processor time are used ...
        std::this_thread::sleep_for (std::chrono::milliseconds(m_mainloopDelay));
    }

}

void CGApplication::paintGUI(cairo_t *c, float fps)
{
    if (m_mainScreen) m_mainScreen->paint(c);
}

