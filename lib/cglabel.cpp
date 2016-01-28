#include "cglabel.h"
#include <iostream>


CGLabel::CGLabel(CGWidget *parent):
    CGFrame(parent), CGFontPropsWithAlignment(this)
{
    m_verticalAlignment=cgalLeft;
    m_horizontalAlignment=cgalTop;
    m_textOffset=1;
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setTextColor(CGColor::ccBlack);
    setPropsFromDefaultPalette();
}

CGLabel::CGLabel(int x, int y, int width, int height, const std::string& text, CGWidget *parent):
    CGFrame(x,y,width,height,parent), CGFontPropsWithAlignment(this)
{
    m_verticalAlignment=cgalLeft;
    m_horizontalAlignment=cgalTop;
    m_lineSpacing=1.2;
    m_bold=false;
    m_italic=false;
    m_fontFace="sans";
    m_fontSize=10;
    m_textOffset=1;
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setTextColor(CGColor::ccBlack);
    m_text=text;
    setPropsFromDefaultPalette();
}

CGLabel::CGLabel(int x, int y, int width, int height, CGWidget *parent):
    CGFrame(x,y,width,height,parent), CGFontPropsWithAlignment(this)
{
    m_verticalAlignment=cgalLeft;
    m_horizontalAlignment=cgalTop;
    m_lineSpacing=1.2;
    m_bold=false;
    m_italic=false;
    m_fontFace="sans";
    m_fontSize=10;
    m_textOffset=1;
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setTextColor(CGColor::ccBlack);
    setPropsFromDefaultPalette();
}

CGLabel::CGLabel(const std::string &text, CGWidget *parent):
    CGFrame(parent), CGFontPropsWithAlignment(this)
{
    m_verticalAlignment=cgalLeft;
    m_horizontalAlignment=cgalTop;
    m_lineSpacing=1.2;
    m_bold=false;
    m_italic=false;
    m_fontFace="sans";
    m_fontSize=10;
    m_textOffset=1;
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setTextColor(CGColor::ccBlack);
    m_text=text;
    setPropsFromDefaultPalette();
}

CGLabel::~CGLabel()
{

}

void CGLabel::setText(const std::string &text)
{
    m_text=text;
}


void CGLabel::paint(cairo_t *cr)
{
    CGFrame::paint(cr);

    float offx=m_textOffset;
    float offy=m_textOffset;
    if (m_horizontalAlignment!=cgalLeft) offx=0;
    if (m_verticalAlignment!=cgalTop) offy=0;
    //drawText(cr, m_border+offx, m_border+offy, m_width-m_frameWidth*2-offx*2, m_height-m_frameWidth*2-offy*2, m_text);
    cgDrawText(cr, m_border+offx, m_border+offy, m_width-m_frameWidth*2-offx*2, m_height-m_frameWidth*2-offy*2, m_text, m_fontFace, m_fontSize, m_italic, m_bold, m_textColor, m_lineSpacing, m_horizontalAlignment, m_verticalAlignment);

}

void CGLabel::setPropsFromPalette(CGPalette *palette)
{
    CGFrame::setPropsFromPalette(palette);
    if (palette) {
        setFrameWidth(0);
        setBackgroundColor(CGColor::ccTransparent);

    }
}
