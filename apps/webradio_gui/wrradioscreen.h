#ifndef WRRADIOSCREEN_H
#define WRRADIOSCREEN_H

#include "cgscreen.h"
#include "cglistwidget.h"
#include "cglayout.h"
#include "cglabel.h"
#include "cgtwostatimage.h"
#include "global.h"
#include "cgprogressbar.h"

/** \brief a screen for webradio */
class WRRadioScreen : public CGScreen
{
    public:
        WRRadioScreen(CGWidget* parent=NULL);
        ~WRRadioScreen();

        virtual void paint(cairo_t *c);

        void addWebradiosFromCONF(const std::string& filename);
        virtual void event(CGEvent* e);


    protected:
        struct radiostation {
            std::string name;
            std::string uri;
        };
        CGListWidget<radiostation>* m_stationList;
        CGImage* m_playState;

        CGMarqueeLabel* m_labelInfo;
        CGMarqueeLabel* m_labelName;
        CGLabel* m_labelElapsed;

        bool m_playing;
        int m_playingItem;

        void stop();
        void play(int index);

        virtual void onShow();
        virtual void onHide();
};

#endif // WRRADIOSCREEN_H
