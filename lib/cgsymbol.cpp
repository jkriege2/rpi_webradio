#include "cgsymbol.h"


CGSymbol::CGSymbol(CGSymbol::Symbols s):
    m_symbol(s)
{
    setPropsFromPalette(CGPalette::defaultPalette());
}

void CGSymbol::setPropsFromPalette(CGPalette *palette)
{
    if (palette) {
        setLinewidth(palette->size(CGPalette::srIconLineWidth));
        setColor(palette->color(CGPalette::crIcon));
        setBackgroundColor(palette->color(CGPalette::crIconBackground));
        setHighlightColor(palette->color(CGPalette::crIconHighlight));
        setShadowColor(palette->color(CGPalette::crIconShadow));
    }
}

void CGSymbol::paint(cairo_t *c, int x, int y, int w, int h) const
{
    //std::cout<<"CGSymbol::paint("<<x<<","<<y<<", "<<w<<","<<h<<") "<<m_symbol<<" "<<m_color<<"\n";
    if (m_symbol==CGSymbol::iNone) return;

    int divider=6;
    int offx=w/divider;
    int offy=h/divider;
    int sx=w-(2*offx);
    int sy=h-(2*offy);
    // fill background


    cairo_save(c);
        cairo_translate(c, x, y)    ;
        cgDrawFilledRectangle(c, 0,0,w,h, m_backgroundColor);
        if (m_symbol==CGSymbol::iPlay) {
            cgFillPolygon(c, offx, offy, offx+sx, offy+sy/2, offx, offy+sy, m_color);
            cgDrawPolygon(c, offx, offy, offx+sx, offy+sy/2, offx, offy+sy, m_shadowColor, m_linewidth);
            cgDrawLine(c, offx, offy, offx+sx, offy+sy/2, m_highlightColor, m_linewidth);
        } else if (m_symbol==CGSymbol::iStop) {
            cgDrawFilledRectangle(c, offx, offy, sx, sy, m_color);
            cgDrawLines(c, offx, offy, offx, offy+sy, offx+sx, offy+sy, m_shadowColor, m_linewidth);
            cgDrawLines(c, offx, offy, offx+sx, offy, offx+sx, offy+sy, m_highlightColor, m_linewidth);
        }
        cairo_restore(c);
}

int CGSymbol::heightForWidth(int w) const
{
    if (m_symbol==CGSymbol::iPlay) {
        return w;
    } else if (m_symbol==CGSymbol::iStop) {
        return w;
    }
    return w;
}
