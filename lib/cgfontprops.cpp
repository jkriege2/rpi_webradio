#include "cgfontprops.h"


void CGFontProps::setFontProps(cairo_t *c) const
{
    setFontProps(c, m_textColor);
}

void CGFontProps::setFontProps(cairo_t *c, CGColor color) const
{
    cairo_select_font_face(c, m_fontFace.c_str(), (m_italic)?CAIRO_FONT_SLANT_ITALIC:CAIRO_FONT_SLANT_NORMAL, (m_bold)?CAIRO_FONT_WEIGHT_BOLD:CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(c, m_fontSize);
    color.cairo_set_source(c);

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
            cairo_text_extents(cr, std::string(l+"Aq").c_str(), &extents);
            if (extents.height>maxH) maxH=extents.height;
            sumH=sumH+extents.height;
            cairo_text_extents(cr, l.c_str(), &extents);
            if (extents.width>maxW) maxW=extents.width;
            l.clear();
        }
    }
    if (l.size()>0) {
        cairo_text_extents_t extents;
        cairo_text_extents(cr, l.c_str(), &extents);
        if (extents.width>maxW) maxW=extents.width;
        cairo_text_extents(cr, std::string(l+"Aq").c_str(), &extents);
        if (extents.height>maxH) maxH=extents.height;
        sumH=sumH+extents.height*m_lineSpacing;

        lines.push_back(l);
    }
    if (p_maxH) *p_maxH=maxH;
    if (p_maxW) *p_maxW=maxW;
    if (p_sumH) *p_sumH=sumH;

    return lines;
}


int CGFontProps::getTextHeight(cairo_t *cr, const std::string &text) const
{
    cairo_save(cr);
    setFontProps(cr);
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text.c_str(), &extents);
    cairo_restore(cr);
    return extents.height;
}

int CGFontProps::getTextXBearing(cairo_t *cr, const std::string &text) const
{
    cairo_save(cr);
    setFontProps(cr);
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text.c_str(), &extents);
    cairo_restore(cr);
    return extents.x_bearing;
}

int CGFontProps::getTextYBearing(cairo_t *cr, const std::string &text) const
{
    cairo_save(cr);
    setFontProps(cr);
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text.c_str(), &extents);
    cairo_restore(cr);
    return extents.y_bearing;
}

int CGFontProps::getTextXAdvance(cairo_t *cr, const std::string &text) const
{
    cairo_save(cr);
    setFontProps(cr);
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text.c_str(), &extents);
    cairo_restore(cr);
    return extents.x_advance;
}

int CGFontProps::getTextYAdvance(cairo_t *cr, const std::string &text) const
{
    cairo_save(cr);
    setFontProps(cr);
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text.c_str(), &extents);
    cairo_restore(cr);
    return extents.y_advance;
}

int CGFontProps::getTextWidth(cairo_t *cr, const std::string &text) const
{
    cairo_save(cr);
    setFontProps(cr);
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text.c_str(), &extents);
    cairo_restore(cr);
    return extents.width;
}


void CGFontProps::drawText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text) const
{
    drawColoredText(cr, xx, yy, m_width, m_height, m_text, m_textColor);
}

void CGFontProps::drawColoredText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text, CGColor color) const
{
    drawAlignedColoredText(cr, xx, yy, m_width, m_height, m_text, color, cgalLeft, cgalTop);
}

void CGFontProps::drawAlignedText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text, cgAlignment m_horizontalAlignment, cgAlignment m_verticalAlignment) const
{
     drawAlignedColoredText(cr, xx, yy, m_width, m_height, m_text, m_textColor, m_horizontalAlignment, m_verticalAlignment);
}

void CGFontProps::drawAlignedColoredText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text, CGColor color, cgAlignment m_horizontalAlignment, cgAlignment m_verticalAlignment) const
{
    if (color.isTransparent()) return;
    cgDrawText(cr, xx, yy, m_width, m_height, m_text, m_fontFace, m_fontSize, m_italic, m_bold, color, m_lineSpacing, m_horizontalAlignment, m_verticalAlignment);
}

void CGFontProps::drawAlignedColoredTextFillBackground(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text, CGColor color, CGColor colorBack, cgAlignment m_horizontalAlignment, cgAlignment m_verticalAlignment) const
{
    cairo_rectangle(cr, xx,yy,m_width,m_height);
    colorBack.cairo_set_source(cr);
    cairo_fill(cr);
    drawAlignedColoredText(cr, xx,yy,m_width,m_height,m_text,color, m_horizontalAlignment, m_verticalAlignment);
}



void CGFontPropsWithAlignment::drawColoredText(cairo_t *cr, float xx, float yy, float m_width, float m_height, const std::string &m_text, CGColor color) const
{
    m_fontprops->drawAlignedColoredText(cr, xx, yy, m_width, m_height, m_text, color, m_horizontalAlignment, m_verticalAlignment);
}
