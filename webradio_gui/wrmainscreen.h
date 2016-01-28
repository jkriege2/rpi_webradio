#ifndef WRMAINSCREEN_H
#define WRMAINSCREEN_H

#include "cgtabbedmultiscreens.h"
#include "wrradioscreen.h"
#include "wrmusicscreen.h"

class WRMainScreen : public CGTabbedMultiScreens
{
    public:
        explicit WRMainScreen(CGWidget* parent=NULL);
        virtual ~WRMainScreen();

    protected:
        virtual void event(CGEvent *e);
        WRRadioScreen* m_webradio;
        WRMusicScreen* m_music;
};

#endif // WRMAINSCREEN_H
