#ifndef CGAPPLICATION_H
#define CGAPPLICATION_H

#include <atomic>
#include <string>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include "cgscreen.h"
#include<cairo.h>

struct fbcairo_context; // forward

/** \brief a singleton, summarizing basic features of an cairo framebuffer GUI application */
class CGApplication {
    public:
        explicit CGApplication();
        virtual ~CGApplication();

        /** \brief if this returns \c false, the application should be exited */
        bool parseCommandline(int argc, char *argv[]);

        /** \brief returns the main instance of the application (if it exists), or \c NULL */
        static CGApplication* getInstanceP();
        /** \brief returns a reference to the main instance of the application <b>after</b> it was instanciated!!! */
        static CGApplication& getInstance();
        /** \brief allows to add allowed program-options before instancing the application */
        static inline boost::program_options::options_description& getCmdOptionsDescription() {
            return m_optdesc;
        }
        /** \brief set the name of the framebuffer device */
        inline void setFramebuffer(const std::string & fb) {
            m_framebuffer=fb;
        }
        /** \brief return the name of the framebuffer device */
        inline std::string framebuffer() const {
            return m_framebuffer;
        }
        /** \brief set whether to use double-buffering */
        inline void setDoublebuffer(bool fb) {
            m_noDoubleBuffer=!fb;
        }
        /** \brief return whether to use double-buffering */
        inline bool doublebuffer() const {
            return !m_noDoubleBuffer;
        }

        /** \brief set the maximum framerate */
        inline void setMaxFramerate(int fr) {
            m_maxFramerate=!fr;
        }
        /** \brief return the maximum framerate */
        inline int maxFramerate() const {
            return m_maxFramerate;
        }

        /** \brief set the delay in the main-loop (thread-sleep) in milliseconds */
        inline void setMainloopDelay(int fr) {
            m_mainloopDelay=!fr;
        }
        /** \brief return the delay in the main-loop (thread-sleep) in milliseconds */
        inline int mainloopDelay() const {
            return m_mainloopDelay;
        }

        /** \brief returns the framebuffer-context */
        inline fbcairo_context* fbcontext() const {
            return m_context;
        }

        /** \brief retun the current framerate */
        inline float fps() const {
            return m_fps;
        }

        /** \brief start the application */
        int start(CGScreen* mainScreen, bool m_ownsMainScreen);

    private:
        static std::atomic<CGApplication*> fs_app;

        static boost::program_options::options_description m_optdesc;
        boost::program_options::variables_map m_optmap;

        std::string m_framebuffer;
        bool m_noDoubleBuffer;
        CGScreen* m_mainScreen;
        fbcairo_context* m_context;
        bool m_ownsMainScreen;
        float m_fps;

        int m_maxFramerate;
        int m_mainloopDelay;

    protected:
        /** \brief the actual main loop */
        virtual void mainLoop();
        /** \brief paints the GUI */
        virtual void paintGUI(cairo_t *c, float fps=0);
};

#endif // CGAPPLICATION_H
