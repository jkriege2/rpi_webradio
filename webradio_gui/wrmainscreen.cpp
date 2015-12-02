#include "wrmainscreen.h"

WRMainScreen::WRMainScreen(CGWidget* parent):
    CGTabbedMultiScreens(320,240, parent),
    m_webradio(NULL)
{
    addScreen(m_webradio=new WRRadioScreen(this), "Radio");

    setCurrentScreen(0);
}

WRMainScreen::~WRMainScreen()
{

}

