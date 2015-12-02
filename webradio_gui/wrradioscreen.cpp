#include "wrradioscreen.h"

WRRadioScreen::WRRadioScreen(CGWidget *parent):
    CGScreen(parent)
{
    //std::cout<<"WRRadioScreen::paint size="<<size()<<"\n";
    //setBackgroundColor(CGColor::ccDarkgray);
    CGLinearLayout* vlay=new CGLinearLayout(this, cgdVertical);
    setLayout(vlay);


    m_stationList=new CGListWidget(this);

    CGWidget* wibhlay=new CGWidget(this);
    CGLinearLayout* hlay=new CGLinearLayout(wibhlay, cgdHorizontal);
    wibhlay->setLayout(hlay);
    m_playState=new CGImage(0,0,24,24, wibhlay);
    m_playState->setImageSymbol(CGSymbol::iPlay);
    m_label=new CGLabel(0,0,24,24,wibhlay);
    m_label->setText("line 1 ...\nplaying ...\nline 3 ... ");
    m_label->setFontSize(12);
    hlay->addWidget(m_playState, -3);
    hlay->addWidget(new CGWidget(wibhlay), -1);
    hlay->addWidget(m_label, -15);

    vlay->addWidget(m_stationList, -4);
    vlay->addWidget(wibhlay, -1);
    hlay->layoutWidgets();
    vlay->layoutWidgets();
}

WRRadioScreen::~WRRadioScreen()
{

}

void WRRadioScreen::paint(cairo_t *c) const
{
    CGScreen::paint(c)   ;
    //std::cout<<"WRRadioScreen::paint size="<<size()<<"\n";
}

