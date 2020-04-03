#include "cgprecomp.h"
#include "cgscreen.h"
#include "cgtabbedmultiscreens.h"
#include "framebuffer_cairo_tools.h"

CGScreen::CGScreen(CGWidget *parent):
    CGWidget(parent),
    CGFontPropsWithAlignment(this)
{
    m_isVirgin=true;
    move(0,0);
    setBackgroundColor(CGColor::ccBlack);
    setPropsFromDefaultPalette();
    CGTabbedMultiScreens* tscreen=dynamic_cast<CGTabbedMultiScreens*>(parent);
    if (tscreen) resize(tscreen->size());
    else {
        CGScreen* screen=dynamic_cast<CGScreen*>(parent);
        if (screen) resize(screen->size());
    }
}

CGScreen::CGScreen(const fbcairo_context *context, CGWidget *parent):
    CGWidget(0,0,fbcairo_getWidth(context),fbcairo_getHeight(context), parent),
    CGFontPropsWithAlignment(this)
{
    m_isVirgin=true;
    setBackgroundColor(CGColor::ccBlack);
    setPropsFromDefaultPalette();
}

CGScreen::CGScreen(int width, int height, CGWidget *parent):
    CGWidget(0,0,width,height, parent),
    CGFontPropsWithAlignment(this)
{
    m_isVirgin=true;
    setBackgroundColor(CGColor::ccBlack);
    move(0,0);
    setPropsFromDefaultPalette();
}

CGScreen::~CGScreen()
{
    hideScreen();
}

void CGScreen::move(int /*x*/, int /*y*/)
{
    CGWidget::move(0,0);
}

void CGScreen::paint(cairo_t *c)
{
    if (m_isVirgin) {
        showScreen();
    }
    cairo_reset_clip(c);
    if (!m_backgroundColor.isTransparent()) {
        cairo_rectangle(c,-2,-2,m_width+5,m_height+5);
        m_backgroundColor.cairo_set_source(c);
        cairo_fill(c);
    }
    cairo_save(c);
        float offsety=0;
        if (m_title.size()>0) {
            float p_maxH=0;
            float p_maxW=0;
            float p_sumH=0;
            splitTextIntoLines(c, m_title, &p_maxH, &p_maxW, &p_sumH);
            offsety=p_maxH+4;
            cairo_rectangle(c,0,0,m_width,offsety-1);
            m_titleBackground.cairo_set_source(c);
            cairo_fill(c);
            drawAlignedColoredText(c,1,2,m_width-2,offsety-4.0,m_title,m_textColor,m_horizontalAlignment,m_verticalAlignment);
        }
        cairo_save(c);
            cairo_translate(c, 0,offsety);
            cairo_rectangle(c,0,0,m_width,m_height-offsety);
            cairo_clip(c);
            CGWidget::paint(c);
        cairo_restore(c);
    cairo_restore(c);
}


void CGScreen::setPropsFromPalette(CGPalette *palette)
{
    CGWidget::setPropsFromPalette(palette);
    if (palette) {
        setTitleBackgroundColor(palette->color(CGPalette::crTitleBackground));
        setTextColor(palette->color(CGPalette::crTitleText));
    }
}

void CGScreen::resizeFromContext(const fbcairo_context *context)
{
    //std::cout<<"GScreen::resizeFromContext("<<context<<"): "<<fbcairo_getWidth(context)<<","<<fbcairo_getHeight(context)<<"\n";
    if (context) resize(fbcairo_getWidth(context),fbcairo_getHeight(context));
}

void CGScreen::showScreen()
{
    //std::cout<<"CGScreen::showScreen(): m_isVirgin="<<m_isVirgin<<"\n";
    if (m_isVirgin) {
        m_isVirgin=false;
        onShow();
    }
    //std::cout<<"CGScreen::showScreen(): m_isVirgin="<<m_isVirgin<<"\n";
}

void CGScreen::hideScreen()
{
    //std::cout<<"CGScreen::hideScreen(): m_isVirgin="<<m_isVirgin<<"\n";
    if (!m_isVirgin) {
        m_isVirgin=true;
        onHide();
    }
    //std::cout<<"CGScreen::hideScreen(): m_isVirgin="<<m_isVirgin<<"\n";
}

void CGScreen::onShow()
{

}

void CGScreen::onHide()
{

}
