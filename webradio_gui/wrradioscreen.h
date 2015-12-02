#ifndef WRRADIOSCREEN_H
#define WRRADIOSCREEN_H

#include "cgscreen.h"
#include "cglistwidget.h"
#include "cglayout.h"
#include "cglabel.h"
#include "cgtwostatimage.h"

/** \brief a screen for webradio */
class WRRadioScreen : public CGScreen
{
    public:
        WRRadioScreen(CGWidget* parent=NULL);
        ~WRRadioScreen();

        virtual void paint(cairo_t *c) const;
    protected:
        CGListWidget* m_stationList;
        CGImage* m_playState;
        CGLabel* m_label;
};

#endif // WRRADIOSCREEN_H
