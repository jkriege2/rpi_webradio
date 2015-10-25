#include "cgscrollbar.h"

CGScrollBarMixin::CGScrollBarMixin()
{
    m_scrollbarColor=CGColor::ccGray25;
    m_scrollbarBackgroundColor=CGColor::ccGray10;
    m_scrollbarButtonColor=CGColor::ccGray50;
    m_scrollbarButtonIconColor=CGColor::ccGray10;
    m_scrollbarRelHeight=0.5;
    m_scrollbarFixedRelHeight=false;
    m_showScrollbarButtons=true;
    setScrollbarRange(0,1);
    setScrollbarPos(0);
    setScrollbarPropsFromPalette(CGPalette::defaultPalette());
}

CGScrollBarMixin::~CGScrollBarMixin()
{

}

void CGScrollBarMixin::paintScrollbar(cairo_t *c, int x, int y, int width, int height) const
{
    paintScrollbar(c,  x,  y,  width,  height,  m_scrollbarMin,  m_scrollbarMax,  m_scrollbarPos,  m_scrollbarPosSize);
}

void CGScrollBarMixin::paintScrollbar(cairo_t *c, int x, int y, int width, int height, float m_scrollbarMin, float m_scrollbarMax, float m_scrollbarPos, float m_scrollbarPosSize) const
{
    cairo_save(c);
        float sbh=float(height)-4.0;
        float ystart=y;
        float button_width=width;
        float arrow_width=button_width-2;
        if (m_showScrollbarButtons) {
            sbh=sbh-2.0*button_width;
            ystart=y+button_width;
        }
        float m_scrollbarWidth=width;
        float sh=m_scrollbarRelHeight*sbh;
        if (!m_scrollbarFixedRelHeight) {
            sh=std::min(sbh,std::max(m_scrollbarWidth, sbh*m_scrollbarPosSize/(m_scrollbarMax-m_scrollbarMin)));
        }
        float sh_start=ystart+(sbh-sh)*float(m_scrollbarPos)/float(m_scrollbarMax-m_scrollbarMin-m_scrollbarPosSize);

        //std::cout<<"cur="<<m_currentItem<<" start="<<m_startVisible<<" sbh="<<sbh<<" sh="<<sh<<" sh_start="<<sh_start<<" w="<<w<<"\n";

        cairo_rectangle(c, x, y, width, height);
        m_scrollbarBackgroundColor.cairo_set_source(c);
        cairo_fill(c);

        cairo_rectangle(c, x, sh_start+1, m_scrollbarWidth, sh);
        m_scrollbarColor.cairo_set_source(c);
        cairo_fill(c);

        if (m_showScrollbarButtons) {
            cairo_rectangle(c, x, y, button_width, button_width);
            m_scrollbarButtonColor.cairo_set_source(c);
            cairo_fill(c);

            cairo_move_to(c, x+button_width/2.0, y+button_width/2.0-arrow_width/2.0);
            cairo_rel_line_to(c, arrow_width/2.0, arrow_width);
            cairo_rel_line_to(c, -arrow_width, 0);
            cairo_close_path(c);
            m_scrollbarButtonIconColor.cairo_set_source(c);
            cairo_fill(c);

            cairo_rectangle(c, x, y+height-button_width-2, button_width, button_width);
            m_scrollbarButtonColor.cairo_set_source(c);
            cairo_fill(c);

            cairo_move_to(c, x+button_width/2.0, y+height-2-button_width/2.0+arrow_width/2.0);
            cairo_rel_line_to(c, arrow_width/2.0, -arrow_width);
            cairo_rel_line_to(c, -arrow_width, 0);
            cairo_close_path(c);
            m_scrollbarButtonIconColor.cairo_set_source(c);
            cairo_fill(c);


        }
        //std::cout<<"m_scrollbarBackgroundColor="<<m_scrollbarBackgroundColor<<"  m_scrollbarColor="<<m_scrollbarColor<<"  m_scrollbarButtonColor="<<m_scrollbarButtonColor<<"  m_scrollbarButtonIconColor="<<m_scrollbarButtonIconColor<<std::endl;

    cairo_restore(c);
}



void CGScrollBarMixin::setScrollbarPropsFromPalette(CGPalette *palette)
{
    if (palette) {
        setScrollbarBackgroundColor(palette->color(CGPalette::crDark));
        setScrollbarButtonColor(palette->color(CGPalette::crButton));
        setScrollbarButtonIconColor(palette->color(CGPalette::crButtonIconOrText));
        SetScrollbarColor(palette->color(CGPalette::crButton));

    }
}
