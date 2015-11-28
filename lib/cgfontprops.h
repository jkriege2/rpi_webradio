#ifndef CGFONTPROPS_H
#define CGFONTPROPS_H

#include "cgbasics.h"
#include <string>
#include <list>
#include <vector>
#include "cgpalette.h"

/*! \brief class that represents the properties of text (fontface, fontsize, italic, bold, color)
           and provides functions for drawing text
 */
class CGFontProps
{
    public:
        inline CGFontProps() {
            m_bold=false;
            m_italic=false;
            m_fontFace="sans";
            m_fontSize=10;
            m_lineSpacing=1.2;
            setTextColor(CGColor::ccWhite);
        }

        virtual ~CGFontProps() {}

        inline CGColor textColor() const {
            return m_textColor;
        }
        inline void setTextColor(CGColor col) {
            m_textColor=col;
        }

        inline std::string fontFace() const {
            return m_fontFace;
        }
        inline void setFontFace(const std::string& val) {
            m_fontFace=val;
        }

        inline bool bold() const {
            return m_bold;
        }
        inline void setBold(bool val) {
            m_bold=val;
        }

        inline bool italic() const {
            return m_italic;
        }
        inline void setItalic(bool val) {
            m_italic=val;
        }
        inline float fontSize() const {
            return m_fontSize;
        }
        inline void setFontSize(float size) {
            m_fontSize=size;
        }
        inline float lineSpacing() const {
            return m_lineSpacing;
        }
        inline void setLineSpacing(float size) {
            m_lineSpacing=size;
        }

        virtual inline void setFontPropsFromPalette(CGPalette *palette)
        {
            if (palette) {
                setFontFace(palette->name(CGPalette::nrFontName));
                setFontSize(palette->size(CGPalette::srFontSize));
                setTextColor(palette->color(CGPalette::crText));
            }
        }
        virtual void setFontProps(cairo_t *c) const;
        virtual void setFontProps(cairo_t *c, CGColor color) const;
        virtual void drawText(cairo_t* cr, float xx, float yy, float m_width, float m_height, const std::string& m_text) const;
        virtual void drawColoredText(cairo_t* cr, float xx, float yy, float m_width, float m_height, const std::string& m_text, CGColor color) const;
        virtual void drawAlignedText(cairo_t* cr, float xx, float yy, float m_width, float m_height, const std::string& m_text, cgAlignment m_horizontalAlignment, cgAlignment m_verticalAlignment) const;
        virtual void drawAlignedColoredText(cairo_t* cr, float xx, float yy, float m_width, float m_height, const std::string& m_text, CGColor color, cgAlignment m_horizontalAlignment, cgAlignment m_verticalAlignment) const;
        virtual void drawAlignedColoredTextFillBackground(cairo_t* cr, float xx, float yy, float m_width, float m_height, const std::string& m_text, CGColor color, CGColor colorBack, cgAlignment m_horizontalAlignment, cgAlignment m_verticalAlignment) const;
        virtual std::list<std::string> splitTextIntoLines(cairo_t *cr, const std::string m_text, float* p_maxH=NULL, float* p_maxW=NULL, float* p_sumH=NULL) const;
        virtual int getTextWidth(cairo_t *cr, const std::string& text) const;
        virtual int getTextHeight(cairo_t *cr, const std::string& text) const;
        virtual int getTextXBearing(cairo_t *cr, const std::string& text) const;
        virtual int getTextYBearing(cairo_t *cr, const std::string& text) const;
        virtual int getTextXAdvance(cairo_t *cr, const std::string& text) const;
        virtual int getTextYAdvance(cairo_t *cr, const std::string& text) const;
    protected:
        CGColor m_textColor;
        float m_fontSize;
        bool m_bold;
        bool m_italic;
        std::string m_fontFace;
        float m_lineSpacing;

};

class CGPropsAlignment  {
    public:
        inline CGPropsAlignment() {
            m_verticalAlignment=cgalLeft;
            m_horizontalAlignment=cgalTop;
        }

        virtual ~CGPropsAlignment() {}

        inline cgAlignment verticalAlignment() const {
            return m_verticalAlignment;
        }
        inline void setVerticalAlignment(cgAlignment val) {
            m_verticalAlignment=val;
        }
        inline cgAlignment horizontalAlignment() const {
            return m_horizontalAlignment;
        }
        inline void setHorizontalAlignment(cgAlignment val) {
            m_horizontalAlignment=val;
        }
    protected:
        cgAlignment m_verticalAlignment;
        cgAlignment m_horizontalAlignment;


};


class CGFontPropsWithAlignment: public CGPropsAlignment {
    public:
        inline CGFontPropsWithAlignment(CGFontProps* fp): CGPropsAlignment() { this->m_fontprops=fp; }
        virtual inline ~CGFontPropsWithAlignment() {}
    protected:
        virtual void drawColoredText(cairo_t* cr, float xx, float yy, float m_width, float m_height, const std::string& m_text, CGColor color) const;
    private:
        CGFontProps* m_fontprops;

};


#endif // CGFONTPROPS_H
