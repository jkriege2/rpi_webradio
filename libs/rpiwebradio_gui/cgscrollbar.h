#ifndef CGSCROLLBAR_H
#define CGSCROLLBAR_H

#include "cgbasics.h"
#include "cgpalette.h"

/** \brief a mix-in that add scrollbars to a widget */
class CGScrollBarMixin
{
    public:
        CGScrollBarMixin();
        virtual ~CGScrollBarMixin();




        inline CGColor scrollbarColor() const {
            return m_scrollbarColor;
        }
        inline void SetScrollbarColor(CGColor v) {
            m_scrollbarColor=v;
        }

        inline CGColor scrollbarBackgroundColor() const {
            return m_scrollbarBackgroundColor;
        }
        inline void setScrollbarBackgroundColor(CGColor v) {
            m_scrollbarBackgroundColor=v;
        }

        inline CGColor scrollbarButtonColor() const {
            return m_scrollbarButtonColor;
        }
        inline void setScrollbarButtonColor(CGColor v) {
            m_scrollbarButtonColor=v;
        }

        inline CGColor scrollbarButtonIconColor() const {
            return m_scrollbarButtonIconColor;
        }
        inline void setScrollbarButtonIconColor(CGColor v) {
            m_scrollbarButtonIconColor=v;
        }

       inline float scrollbarRelHeight() const {
           return m_scrollbarRelHeight;
       }
       inline void setscrollbarRelHeight(float v) {
           m_scrollbarRelHeight=v;
           if (m_scrollbarRelHeight<0.01) m_scrollbarRelHeight=0.01;
           if (m_scrollbarRelHeight>1) m_scrollbarRelHeight=1;
       }

       inline bool scrollbarFixedRelHeight() const {
           return m_scrollbarFixedRelHeight;
       }
       inline void setScrollbarFixedRelHeight(bool v) {
           m_scrollbarFixedRelHeight=v;
       }

       virtual void setScrollbarPropsFromPalette(CGPalette *palette);
    protected:

        virtual void paintScrollbar(cairo_t *c, int x, int y, int width, int height) const;
        virtual void paintScrollbar(cairo_t *c, int x, int y, int width, int height, float m_scrollbarMin, float m_scrollbarMax, float m_scrollbarPos, float m_scrollbarPosSize) const;


        inline float scrollbarMin() const {
            return m_scrollbarMin;
        }
        inline void setScrollbarMin(float v) {
            m_scrollbarMin=v;
            if (m_scrollbarMax<m_scrollbarMin) std::swap(m_scrollbarMin, m_scrollbarMax);
        }
        inline float scrollbarMax() const {
            return m_scrollbarMax;
        }
        inline void setScrollbarMax(float v) {
            m_scrollbarMax=v;
            if (m_scrollbarMax<m_scrollbarMin) std::swap(m_scrollbarMin, m_scrollbarMax);
        }
        inline void setScrollbarRange(float min, float max) {
            m_scrollbarMin=min;
            m_scrollbarMax=max;
            if (m_scrollbarMax<m_scrollbarMin) std::swap(m_scrollbarMin, m_scrollbarMax);
        }
        inline float scrollbarPos() const {
            return m_scrollbarPos;
        }
        inline void setScrollbarPos(float v) {
            m_scrollbarPos=v;
            if (m_scrollbarPos<m_scrollbarMin) m_scrollbarPos=m_scrollbarMin;
            if (m_scrollbarPos>m_scrollbarMax) m_scrollbarPos=m_scrollbarMax;
        }
        inline float scrollbarPosSize() const {
            return m_scrollbarPosSize;
        }
        inline void setScrollbarPosSize(float v) {
            m_scrollbarPosSize=v;
            if (m_scrollbarPosSize<0.001) m_scrollbarPosSize=0.001;
        }

    protected:
        CGColor m_scrollbarColor;
        CGColor m_scrollbarBackgroundColor;
        CGColor m_scrollbarButtonColor;
        CGColor m_scrollbarButtonIconColor;

        float m_scrollbarMin;
        float m_scrollbarMax;
        float m_scrollbarPos;
        float m_scrollbarPosSize;
        bool m_showScrollbarButtons;
        float m_scrollbarRelHeight;
        bool m_scrollbarFixedRelHeight;

};

#endif // CGSCROLLBAR_H
