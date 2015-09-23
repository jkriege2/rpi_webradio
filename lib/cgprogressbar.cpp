#include "cgprogressbar.h"
#include "cgbasics.h"
#include <iostream>


CGProgressBar::CGProgressBar(CGWidget *parent):
    CGFrame(parent)
{
    m_bold=false;
    m_italic=false;
    m_fontFace="sans";
    m_fontSize=10;
    m_showText=true;
    setProgressColor(CGColor::ccRed);
    setTextColor(CGColor::ccGrey75);
    setPropsFromDefaultPalette();
}

CGProgressBar::CGProgressBar(int x, int y, int width, int height, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    m_bold=false;
    m_italic=false;
    m_fontFace="sans";
    m_fontSize=10;
    m_showText=true;
    setProgressColor(CGColor::ccRed);
    setTextColor(CGColor::ccGrey75);
    setPropsFromDefaultPalette();
}

CGProgressBar::~CGProgressBar()
{

}

void CGProgressBar::paint(cairo_t *c) const
{
    CGFrame::paint(c);
    float w=(m_value-m_min)/(m_max-m_min);
    float ww=m_width-2.0*m_border;

    cairo_rectangle(c, m_border,m_border,w*ww,m_height-2.0*m_border);
    m_progressColor.cairo_set_source(c);
    cairo_fill(c);

    if (m_showText) {
        drawAlignedText(c, 0, 0, m_width, m_height, progressText(), cgalCenter, cgalCenter);
        //cgDrawText(c, 0, 0, m_width, m_height, progressText(), m_fontFace, m_fontSize, m_italic, m_bold, m_textColor);
    }
}

std::string CGProgressBar::progressText() const
{
    float w=(m_value-m_min)/(m_max-m_min);
    return cgFormat("%.0f %%", w*100.0);
}

void CGProgressBar::setPropsFromPalette(CGPalette *palette)
{
    CGFrame::setPropsFromPalette(palette);
    if (palette) {
        setFontPropsFromPalette(palette);
        setProgressColor(palette->color(CGPalette::crHighlight));
        setTextColor(palette->color(CGPalette::crTextOnHighlight));
    }
}
