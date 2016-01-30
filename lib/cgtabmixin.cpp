#include "cgtabmixin.h"

CGTabMixin::CGTabMixin(TabPosition tp)
{
    m_tabPosition=tp;
}

CGTabMixin::~CGTabMixin()
{

}

int CGTabMixin::tabGetActiveTab() const
{
    for (int i=0; i<tabCount(); i++) {
        if (tabIsActive(i)) return i;
    }
    return -1;
}

void CGTabMixin::paintTabBar(cairo_t *c, int m_width, int m_height, const CGFontProps *fp, cgRect<int>* remainingRect) const
{
    if (remainingRect) *remainingRect=getRemainingRect(m_width, m_height);
    if (m_tabPosition==tpTop) {
        cairo_save(c);
        cairo_rectangle(c, 0,0,m_width,m_tabheight);
        cairo_clip(c);
    } else if (m_tabPosition==tpBottom) {
        cairo_save(c);
        cairo_translate(c, 0, m_height-m_tabheight);
        cairo_rectangle(c, 0,0,m_width,m_tabheight);
        cairo_clip(c);
    } else {
        return;
    }
        int acTab=tabGetActiveTab();
        for (int j=0; j<2; j++) {
            int x=1;
            for (int i=0; i<tabCount(); i++) {
                std::string n=tabName(i);
                bool ac=(i==acTab);
                float fw=m_tabFrameWidth;
                CGColor fc=m_tabFrameColor;
                CGColor tc=m_tabColor;
                CGColor ttc=m_tabTextColor;
                if (ac) {
                    fw=m_activeTabFrameWidth;
                    fc=m_activeTabFrameColor;
                    tc=m_activeTabColor;
                    ttc=m_activeTabTextColor;
                }
                int tadd=m_tabTextSpace;
                int w=fp->getTextWidth(c, n)+2*tadd;
                int th=fp->getTextHeight(c, "qutA\"");
                int yf=(m_tabheight-th)/2.0;
                int x1=x+m_tabheight/4;
                int x2=x1+w;
                int x3=x2+m_tabheight/4;
                if ((j==0 &&!ac) || (j==1 && ac)) {
                    if (m_tabPosition==tpTop) {
                        cgFillPolygon(c, x, m_tabheight, x1, 1, x2, 1, x3, m_tabheight, tc);
                        cgDrawLines(c, x, m_tabheight, x1, 1, x2, 1, x3, m_tabheight, fc, fw);
                    } else if (m_tabPosition==tpBottom) {
                        cgFillPolygon(c, x, 1, x1, m_tabheight, x2, m_tabheight, x3, 1, tc);
                        cgDrawLines(c, x, 1, x1, m_tabheight, x2, m_tabheight, x3, 1, fc, fw);
                    }
                    fp->drawColoredText(c, x1+tadd, yf,w-2*tadd,th,n,ttc);
                }
                x=x2;
            }
        }
        cairo_restore(c);
}

cgRect<int> CGTabMixin::getRemainingRect(int m_width, int m_height) const
{
    if (m_tabPosition==tpTop) {
        return cgRect<int>(0,m_tabheight,m_width,m_height-m_tabheight-1);
    } else if (m_tabPosition==tpBottom) {
        return cgRect<int>(0,0,m_width,m_height-m_tabheight-1);
    } else {
        return cgRect<int>(0,0,m_width,m_height-1);
    }
}

void CGTabMixin::setTabPropsFromPalette(CGPalette *palette)
{
    if (palette) {
        setTabHeight(palette->size(CGPalette::srFontSize)*6/4);
        setTabTextSpace(palette->size(CGPalette::srFontSize)/2);
        setTabFrameWidth(palette->size(CGPalette::srFrameWidth));
        setActiveTabFrameWidth(palette->size(CGPalette::srFocusedFrameWidth));

        setTabColor(palette->color(CGPalette::crInactiveButton));
        setActiveTabColor(palette->color(CGPalette::crButton));
        setTabTextColor(palette->color(CGPalette::crInactiveButtonIconOrText));
        setActiveTabTextColor(palette->color(CGPalette::crButtonIconOrText));
        setTabFrameColor(palette->color(CGPalette::crInactiveButtonFrame));
        setActiveTabFrameColor(palette->color(CGPalette::crButtonFrame));


    }
}

void CGTabMixin::setTabFrameColor(CGColor col)
{
    m_tabFrameColor=col;
}

void CGTabMixin::setTabFrameWidth(float width)
{
    m_tabFrameWidth=width;
}

void CGTabMixin::setActiveTabFrameColor(CGColor col)
{
    m_activeTabFrameColor=col;
}

void CGTabMixin::setActiveTabFrameWidth(float width)
{
    m_activeTabFrameWidth=width;
}

void CGTabMixin::setActiveTabColor(CGColor col)
{
    m_activeTabColor=col;
}

void CGTabMixin::setTabColor(CGColor col)
{
    m_tabColor=col;
}

void CGTabMixin::setTabTextColor(CGColor col)
{
    m_tabTextColor=col;
}

void CGTabMixin::setActiveTabTextColor(CGColor col)
{
    m_activeTabTextColor=col;
}

