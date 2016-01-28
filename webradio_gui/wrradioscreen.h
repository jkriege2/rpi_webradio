#ifndef WRRADIOSCREEN_H
#define WRRADIOSCREEN_H

#include "cgscreen.h"
#include "cglistwidget.h"
#include "cglayout.h"
#include "cglabel.h"
#include "cgtwostatimage.h"
#include "global.h"

/** \brief a screen for webradio */
class WRRadioScreen : public CGScreen
{
    public:
        WRRadioScreen(CGWidget* parent=NULL);
        ~WRRadioScreen();

        virtual void paint(cairo_t *c);

        void addWebradiosFromCONF(const std::string& filename);
        void updateList();
        virtual void event(CGEvent* e);


    protected:
        CGListWidget* m_stationList;
        CGImage* m_playState;
        CGLabel* m_label;
        struct radiostation {
            std::string name;
            std::string uri;
        };

        std::vector<radiostation> m_stations;
        bool m_playing;
        int m_playingItem;

        void stop();
        void play(int index);

        virtual void onShow();
        virtual void onHide();
};

#endif // WRRADIOSCREEN_H