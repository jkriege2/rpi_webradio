#ifndef WRMAINSCREEN_H
#define WRMAINSCREEN_H

#include "cgtabbedmultiscreens.h"
#include "wrradioscreen.h"

class WRMainScreen : public CGTabbedMultiScreens
{
    public:
        explicit WRMainScreen(CGWidget* parent=NULL);
        virtual ~WRMainScreen();

    protected:
        WRRadioScreen* m_webradio;
};

#endif // WRMAINSCREEN_H
