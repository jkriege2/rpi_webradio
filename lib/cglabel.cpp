#include "cgprecomp.h"
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
    setText(text);
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
    setText(text);
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

#define CGMarqueeLabel_PIXELS_PER_SECOND 20.0
#define CGMarqueeLabel_DEFAULT_DURATION_MS 1000.0/CGMarqueeLabel_PIXELS_PER_SECOND

CGMarqueeLabel::CGMarqueeLabel(CGWidget *parent):
    CGLabel(parent),
    m_stepDurationMS(CGMarqueeLabel_DEFAULT_DURATION_MS),
    m_lastOffset(0),
    m_lastCalcWidth(0),
    m_lastDirection(-1)
{

}

CGMarqueeLabel::CGMarqueeLabel(int x, int y, int width, int height, const std::string &text, CGWidget *parent):
    CGLabel(x,y,width,height,text,parent),
    m_stepDurationMS(CGMarqueeLabel_DEFAULT_DURATION_MS),
    m_lastOffset(0),
    m_lastCalcWidth(0),
    m_lastDirection(-1)
{

}

CGMarqueeLabel::CGMarqueeLabel(int x, int y, int width, int height, CGWidget *parent):
    CGLabel(x,y,width,height,parent),
    m_stepDurationMS(CGMarqueeLabel_DEFAULT_DURATION_MS),
    m_lastOffset(0),
    m_lastCalcWidth(0),
    m_lastDirection(-1)
{

}

CGMarqueeLabel::CGMarqueeLabel(const std::string &text, CGWidget *parent):
    CGLabel(text, parent),
    m_stepDurationMS(CGMarqueeLabel_DEFAULT_DURATION_MS),
    m_lastOffset(0),
    m_lastCalcWidth(0),
    m_lastDirection(-1)
{

}

void CGMarqueeLabel::setText(const std::string &text)
{
    if (text!=m_text) {
        m_lastOffset=0;
        m_start=std::chrono::steady_clock::now();
        m_lastDirection=-1;
        CGLabel::setText(text);
    }
}

void CGMarqueeLabel::paint(cairo_t *c)
{
    CGFrame::paint(c);
    cairo_save(c);
        cairo_translate(c, m_border, m_border);
        cairo_rectangle(c, 0,0, m_width-2.0*m_border, m_height-2.0*m_border);
        cairo_clip (c);



        if (m_text!=m_lastCalcText) {
            m_lastCalcWidth=cgSingleLineTextExtent(c, m_text, m_fontFace, m_fontSize, m_italic, m_bold).width;
        }

        int deltaMS=std::chrono::duration_cast<std::chrono::duration<float,std::milli> >(std::chrono::steady_clock::now() - m_start).count();
        if (deltaMS>m_stepDurationMS) {
            m_start=std::chrono::steady_clock::now();
            if (m_lastCalcWidth>(long)m_width) {
                m_lastOffset = m_lastOffset + m_lastDirection*std::max<int>(1, ceil(float(deltaMS)/float(m_stepDurationMS)));
                if (m_lastOffset>15 || m_lastOffset<-fabs(m_lastCalcWidth-m_width)-15) {
                    m_lastDirection=-1*m_lastDirection;
                }
                //std::cout<<"   SET   m_lastOffset="<<m_lastOffset<<"\n\n";
            } else {
                m_lastOffset=0;
                //std::cout<<"   RESET m_lastOffset="<<m_lastOffset<<"\n\n";
            }

        }
        //std::cout<<"deltaMS="<<deltaMS<<" m_stepDurationMS="<<m_stepDurationMS<<"   m_lastOffset="<<m_lastOffset<<"   m_lastDirection="<<m_lastDirection<<" m_lastCalcWidth="<<m_lastCalcWidth<<" m_width="<<m_width<<"\n";

        float offx=m_textOffset;
        float offy=m_textOffset;
        if (m_horizontalAlignment!=cgalLeft) offx=0;
        if (m_verticalAlignment!=cgalTop) offy=0;
        //drawText(cr, m_border+offx, m_border+offy, m_width-m_frameWidth*2-offx*2, m_height-m_frameWidth*2-offy*2, m_text);
        cairo_save(c);
            cairo_translate(c, m_lastOffset, 0);
            cgDrawText(c, offx, offy, m_width-m_frameWidth*2-offx*2, m_height-m_frameWidth*2-offy*2, m_text, m_fontFace, m_fontSize, m_italic, m_bold, m_textColor, m_lineSpacing, m_horizontalAlignment, m_verticalAlignment);
        cairo_restore(c);

    cairo_restore(c);

}
