#include "cgscreen.h"

CGScreen::CGScreen(CGWidget *parent):
    CGWidget(parent)
{
    move(0,0);
    setBackgroundColor(CGColor::ccBlack);
}

CGScreen::CGScreen(const fbcairo_context *context, CGWidget *parent):
    CGWidget(0,0,fbcairo_getWidth(context),fbcairo_getHeight(context), parent)
{
    setBackgroundColor(CGColor::ccBlack);
}

CGScreen::CGScreen(int width, int height, CGWidget *parent):
    CGWidget(0,0,width,height, parent)
{
    setBackgroundColor(CGColor::ccBlack);
    move(0,0);
}

CGScreen::~CGScreen()
{

}

void CGScreen::move(int /*x*/, int /*y*/)
{
    CGWidget::move(0,0);
}

void CGScreen::paint(cairo_t *c) const
{
    cairo_reset_clip(c);
    CGWidget::paint(c);
}

