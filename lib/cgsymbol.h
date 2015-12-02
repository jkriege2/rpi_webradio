#ifndef CGSYMBOL_H
#define CGSYMBOL_H

#include "cgbasics.h"
#include "cgfontprops.h"

/** \brief a class that represents an icon, drawn programmatically (scalably, i.e. no pixel-graphics) by cairo-instructions */
class CGSymbol
{
    public:
        enum Symbols {
            iNone=0,          /**< no symbol */
            iEmpty,           /**< an empty symbol (with a box!) */
            iPlay,            /**< a play-symbol (right-pointing rectangle) */
            iStop,            /**< a stop-symbol (box) */
        };

        explicit CGSymbol(Symbols s=iNone);

        inline bool isNoneSymbol() const {
            return m_symbol==iNone;
        }

        inline void setSymbol(Symbols s) {
            m_symbol=s;
        }
        inline Symbols symbol() const {
            return m_symbol;
        }

        inline void setLinewidth(float s) {
            m_linewidth=s;
        }
        inline float linewidth() const {
            return m_linewidth;
        }

        inline void setColor(CGColor s) {
            m_color=s;
        }
        inline CGColor color() const {
            return m_color;
        }


        inline void setBackgroundColor(CGColor s) {
            m_backgroundColor=s;
        }
        inline CGColor backgroundColor() const {
            return m_backgroundColor;
        }

        inline void setHighlightColor(CGColor s) {
            m_highlightColor=s;
        }
        inline CGColor highlightColor() const {
            return m_highlightColor;
        }

        inline void setShadowColor(CGColor s) {
            m_shadowColor=s;
        }
        inline CGColor shadowColor() const {
            return m_shadowColor;
        }

        void setPropsFromPalette(CGPalette *palette);

        void paint(cairo_t *c, int x, int y, int w, int h) const;
        int heightForWidth(int w) const;
    protected:
        Symbols m_symbol;
        CGColor m_color;
        CGColor m_backgroundColor;
        CGColor m_highlightColor;
        CGColor m_shadowColor;
        float m_linewidth;
};

#endif // CGSYMBOL_H
