#include "cgframe.h"
#include <iostream>


CGFrame::CGFrame(CGWidget *parent):
    CGWidget(parent),
    m_frameWidth(2),
    m_frameColor(255)
{
    setBackgroundColor(CGColor(0));
    m_border=m_frameWidth+1;
}

CGFrame::CGFrame(int x, int y, int width, int height, CGWidget *parent):
    CGWidget(x,y,width,height,parent),
    m_frameWidth(2),
    m_frameColor(255)

{
    setBackgroundColor(CGColor(0));
    m_border=m_frameWidth+1;
}

CGFrame::~CGFrame()
{

}


void CGFrame::setFrameColor(CGColor col)
{
    this->m_frameColor=col;
}

void CGFrame::setFrameWidth(float width)
{
    m_frameWidth=width;
}

void CGFrame::paint(cairo_t *c) const
{
    //std::cout<<"draw frame ("<<m_x<<", "<<m_y<<"; "<<m_width<<"x"<<m_height<<") -> abs: ("<<absX()<<", "<<absY()<<"; "<<m_width<<"x"<<m_height<<")\n";
    cairo_rectangle(c, absX(), absY(), m_width, m_height);
    cairo_set_line_width(c, m_frameWidth);
    cairo_set_source_rgba(c, m_frameColor.rf(), m_frameColor.gf(), m_frameColor.bf(), m_frameColor.af());
    cairo_stroke(c);

    CGWidget::paint(c);
}
