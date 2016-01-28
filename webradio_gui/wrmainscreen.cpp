#include "wrmainscreen.h"
#include "cgapplication.h"

WRMainScreen::WRMainScreen(CGWidget* parent):
    CGTabbedMultiScreens(320,240, parent),
    m_webradio(NULL),
    m_music(NULL)
{
    addScreen(m_webradio=new WRRadioScreen(this), "Radio");
    addScreen(m_music=new WRMusicScreen(this), "Music");

    setCurrentScreen(0);
}

WRMainScreen::~WRMainScreen()
{

}


void WRMainScreen::event(CGEvent *e)
{
    CGButtonClickedEvent* clk=dynamic_cast<CGButtonClickedEvent*>(e);
    CGInputScroll* rot=dynamic_cast<CGInputScroll*>(e);
    std::cout<<"WRMainScreen::event: "<<e->toString()<<", "<<clk<<", "<<rot<<"\n";
    if (clk && clk->button()==BTN_MAIN_EXIT) {
        std::cout<<"  BTN_MAIN_EXIT-clicked\n";
        CGApplication::getInstance().exit();
        clk->accept();
    } else if (clk && clk->button()==BTN_MAIN_CHOOSE_MODE) {
        std::cout<<"  BTN_MAIN_CHOOSE_MODE-clicked\n";
        setCurrentScreen((currentScreenID()+1)%count());
        clk->accept();
    } else {
        CGTabbedMultiScreens::event(e);
    }
}
