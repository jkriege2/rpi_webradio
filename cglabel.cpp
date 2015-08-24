#include "cglabel.h"
#include <iostream>


CGLabel::CGLabel(CGWidget *parent):
    CGFrame(parent)
{
    m_verticalAlignment=alLeft;
    m_horizontalAlignment=alTop;
    m_lineSpacing=1.2;
    m_bold=false;
    m_italic=false;
    m_fontFace="sans";
    m_fontSize=10;
    m_textOffset=1;
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
}

CGLabel::CGLabel(int x, int y, int width, int height, const std::string& text, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    m_verticalAlignment=alLeft;
    m_horizontalAlignment=alTop;
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
}

CGLabel::CGLabel(int x, int y, int width, int height, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    m_verticalAlignment=alLeft;
    m_horizontalAlignment=alTop;
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
}

CGLabel::CGLabel(const std::string &text, CGWidget *parent):
    CGFrame(parent)
{
    m_verticalAlignment=alLeft;
    m_horizontalAlignment=alTop;
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
}

CGLabel::~CGLabel()
{

}

void CGLabel::setText(const std::string &text)
{
    m_text=text;
}

void CGLabel::setTextColor(CGColor col)
{
    m_textColor=col;
}

void CGLabel::paint(cairo_t *cr) const
{
    CGFrame::paint(cr);

    cairo_text_extents_t extents;
    cairo_select_font_face (cr, m_fontFace.c_str(), (m_italic)?CAIRO_FONT_SLANT_ITALIC:CAIRO_FONT_SLANT_NORMAL, (m_bold)?CAIRO_FONT_WEIGHT_BOLD:CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, m_fontSize);

    std::list<std::string> lines;
    std::string l;
    float maxH=0, maxW=0, sumH=0;
    for (size_t i=0; i<m_text.size(); i++) {
        if (m_text[i]!='\n') {
            l.push_back(m_text[i]);
        } else {
            lines.push_back(l);
            cairo_text_extents(cr, l.c_str(), &extents);
            if (extents.width>maxW) maxW=extents.width;
            if (extents.height>maxH) maxH=extents.height;
            sumH=sumH+extents.height;
            l.clear();
        }
    }
    if (l.size()>0) {
        cairo_text_extents(cr, l.c_str(), &extents);
        if (extents.width>maxW) maxW=extents.width;
        if (extents.height>maxH) maxH=extents.height;
        sumH=sumH+extents.height*m_lineSpacing;

        lines.push_back(l);
    }


    cairo_set_source_rgba(cr, m_textColor.redf(), m_textColor.greenf(), m_textColor.bluef(), m_textColor.alphaf());


    float y = m_border- extents.y_bearing+m_textOffset;
    if (m_verticalAlignment==alBottom) {
        y = (m_border+m_height-m_frameWidth*2-m_textOffset*2)-sumH - extents.y_bearing;
    } else if (m_verticalAlignment==alCenter) {
        y = (m_border+m_height-m_frameWidth*2-m_textOffset*2)/2-sumH/2 - extents.y_bearing;
    }

    for (std::list<std::string>::const_iterator it=lines.begin(); it!=lines.end(); ++it) {
        cairo_text_extents (cr, (*it).c_str(), &extents);
        float x = m_border+m_textOffset;//+(float)m_width-(extents.width/2 + extents.x_bearing);
        if (m_horizontalAlignment==alRight) {
            x=m_border+m_width-m_frameWidth*2-m_textOffset*2-extents.width;
        } else if (m_horizontalAlignment==alCenter) {
            x=(m_border+m_width-m_frameWidth*2-m_textOffset*2)/2-extents.width/2;
        }


        //std::cout<<"draw label line ("<<m_x<<", "<<m_y<<"; "<<m_width<<"x"<<m_height<<") -> abs: ("<<x<<"["<<absX()<<"], "<<y<<"["<<absY()<<"]; "<<m_width<<"x"<<m_height<<")  text:"<<(*it)<<"  extents.height="<<extents.height<<"  extents.y_bearing="<<extents.y_bearing<<"\n";
        cairo_move_to (cr, x,y);
        cairo_show_text (cr, (*it).c_str());
        y=y+extents.height*m_lineSpacing;
    }
}
