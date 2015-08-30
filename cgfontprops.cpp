#include "cgfontprops.h"


void CGFontProps::setFontProps(cairo_t *c) const
{
    setFontProps(c, m_textColor);
}

void CGFontProps::setFontProps(cairo_t *c, CGColor color) const
{
    cairo_select_font_face(c, m_fontFace.c_str(), (m_italic)?CAIRO_FONT_SLANT_ITALIC:CAIRO_FONT_SLANT_NORMAL, (m_bold)?CAIRO_FONT_WEIGHT_BOLD:CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(c, m_fontSize);
    cairo_set_source_rgba(c, color.redf(), color.greenf(), color.bluef(), color.alphaf());

}


std::list<std::string> CGFontProps::splitTextIntoLines(cairo_t *cr, const std::string m_text, float *p_maxH, float *p_maxW, float *p_sumH) const
{
    std::list<std::string> lines;
    std::string l;
    float maxH=0, maxW=0, sumH=0;
    for (size_t i=0; i<m_text.size(); i++) {
        if (m_text[i]!='\n') {
            l.push_back(m_text[i]);
        } else {
            lines.push_back(l);
            cairo_text_extents_t extents;
            cairo_text_extents(cr, l.c_str(), &extents);
            if (extents.width>maxW) maxW=extents.width;
            if (extents.height>maxH) maxH=extents.height;
            sumH=sumH+extents.height;
            l.clear();
        }
    }
    if (l.size()>0) {
        cairo_text_extents_t extents;
        cairo_text_extents(cr, l.c_str(), &extents);
        if (extents.width>maxW) maxW=extents.width;
        if (extents.height>maxH) maxH=extents.height;
        sumH=sumH+extents.height*m_lineSpacing;

        lines.push_back(l);
    }
    if (p_maxH) *p_maxH=maxH;
    if (p_maxW) *p_maxW=maxW;
    if (p_sumH) *p_sumH=sumH;

    return lines;
}


void CGFontProps::drawText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text) const
{
    drawColoredText(cr, xx, yy, m_width, m_height, m_text, m_textColor);
}

void CGFontProps::drawColoredText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text, CGColor color) const
{
    drawAlignedColoredText(cr, xx, yy, m_width, m_height, m_text, color, cgalLeft, cgalTop);
//    setFontProps(cr, color);
//    cairo_text_extents_t extents;
//    float maxH=0, maxW=0, sumH=0;
//    std::list<std::string> lines=splitTextIntoLines(cr, m_text, &maxH, &maxW, &sumH);
//    if (lines.size()>0) {
//        cairo_text_extents (cr, lines.begin()->c_str(), &extents);


//        float y = yy- extents.y_bearing;

//        for (std::list<std::string>::const_iterator it=lines.begin(); it!=lines.end(); ++it) {
//            cairo_text_extents (cr, (*it).c_str(), &extents);
//            float x = xx;

//            cairo_move_to (cr, x,y);
//            cairo_show_text (cr, (*it).c_str());
//            y=y+extents.height*m_lineSpacing;
//        }
//    }

}

void CGFontProps::drawAlignedText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text, cgAlignment m_horizontalAlignment, cgAlignment m_verticalAlignment) const
{
     drawAlignedColoredText(cr, xx, yy, m_width, m_height, m_text, m_textColor, m_horizontalAlignment, m_verticalAlignment);
}

void CGFontProps::drawAlignedColoredText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text, CGColor color, cgAlignment m_horizontalAlignment, cgAlignment m_verticalAlignment) const
{
    cgDrawText(cr, xx, yy, m_width, m_height, m_text, m_fontFace, m_fontSize, m_italic, m_bold, color, m_lineSpacing, m_horizontalAlignment, m_verticalAlignment);
}



void CGFontPropsWithAlignment::drawColoredText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text, CGColor color) const
{
    drawAlignedColoredText(cr, xx, yy, m_width, m_height, m_text, color, m_horizontalAlignment, m_verticalAlignment);
//    setFontProps(cr, color);
//    cairo_text_extents_t extents;
//    float maxH=0, maxW=0, sumH=0;
//    std::list<std::string> lines=splitTextIntoLines(cr, m_text, &maxH, &maxW, &sumH);
//    if (lines.size()>0) {
//        cairo_text_extents (cr, lines.begin()->c_str(), &extents);

//        float y = yy- extents.y_bearing;
//        if (m_verticalAlignment==cgalBottom) {
//            y = (yy+m_height)-sumH - extents.y_bearing;
//        } else if (m_verticalAlignment==cgalCenter) {
//            y = (yy+m_height)/2-sumH/2 - extents.y_bearing;
//        }

//        for (std::list<std::string>::const_iterator it=lines.begin(); it!=lines.end(); ++it) {
//            cairo_text_extents (cr, (*it).c_str(), &extents);
//            float x = xx;
//            if (m_horizontalAlignment==cgalRight) {
//                x=xx+m_width-extents.width;
//            } else if (m_horizontalAlignment==cgalCenter) {
//                x=(xx+m_width)/2-extents.width/2;
//            }


//            cairo_move_to (cr, x,y);
//            cairo_show_text (cr, (*it).c_str());
//            y=y+extents.height*m_lineSpacing;

//        }
//    }
}
