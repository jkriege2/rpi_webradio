#include "cgprecomp.h"
#include "cgframe.h"
#include <iostream>


CGFrame::CGFrame(CGWidget *parent):
    CGWidget(parent),
    m_frameWidth(1),
    m_frameColor(255)
{
    m_border=m_frameWidth+1;
    setPropsFromDefaultPalette();
}

CGFrame::CGFrame(int x, int y, int width, int height, CGWidget *parent):
    CGWidget(x,y,width,height,parent),
    m_frameWidth(1),
    m_frameColor(255)

{
    setBackgroundColor(CGColor(0));
    m_border=m_frameWidth+1;
    setPropsFromDefaultPalette();
}

CGFrame::~CGFrame()
{

}

void CGFrame::setPropsFromPalette(CGPalette *palette)
{
    CGWidget::setPropsFromPalette(palette);
    if (palette) {
        setFrameWidth(palette->size(CGPalette::srFrameWidth));
        setFrameColor(palette->color(CGPalette::crFrame));
        setFocusedFrameWidth(palette->size(CGPalette::srFocusedFrameWidth));
        setFocusedFrameColor(palette->color(CGPalette::crFocusedFrame));
    }
}


void CGFrame::setFrameColor(CGColor col)
{
    this->m_frameColor=col;
}

void CGFrame::setFrameWidth(float width)
{
    m_frameWidth=width;
    m_border=m_frameWidth+1;
}

void CGFrame::setFocusedFrameColor(CGColor col)
{
    m_focusedFrameColor=col;
}

void CGFrame::setFocusedFrameWidth(float width)
{
    m_focusedFrameWidth=width;
}

void CGFrame::paint(cairo_t *c)
{
    //std::cout<<"draw frame ("<<m_x<<", "<<m_y<<"; "<<m_width<<"x"<<m_height<<") -> abs: ("<<absX()<<", "<<absY()<<"; "<<m_width<<"x"<<m_height<<")\n";
    CGWidget::paint(c);
    if (m_frameWidth>0 && !m_frameColor.isTransparent()) {
        cairo_rectangle(c, m_frameWidth/2.0, m_frameWidth/2.0, m_width-m_frameWidth, m_height-m_frameWidth);
        if (mayReceiveFocus() && hasFocus()) {
            cairo_set_line_width(c, m_focusedFrameWidth);
            m_focusedFrameColor.cairo_set_source(c);
        } else {
            cairo_set_line_width(c, m_frameWidth);
            m_frameColor.cairo_set_source(c);
        }
        cairo_stroke(c);
    }
}
