#include "cgsymbol.h"
#include <cmath>

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
    const std::chrono::steady_clock::time_point tnow=std::chrono::steady_clock::now();
    const double since_last = std::chrono::duration_cast<std::chrono::duration<double,std::milli> >(tnow - lastpaint).count();


    cairo_save(c);
        cairo_translate(c, x, y)    ;
        cgDrawFilledRectangle(c, 0,0,w,h, m_backgroundColor);
        if (m_symbol==CGSymbol::iPlay) {
            cgFillPolygon(c, offx, offy, offx+sx, offy+sy/2, offx, offy+sy, m_color);
            cgDrawPolygon(c, offx, offy, offx+sx, offy+sy/2, offx, offy+sy, m_shadowColor, m_linewidth);
            cgDrawLine(c, offx, offy, offx+sx, offy+sy/2, m_highlightColor, m_linewidth);
        } else if (m_symbol==CGSymbol::iPlayAnimated) {
            int ssx=sx/2;
            int ssy=sy/2;
            int offxx=offx+sx/2-ssx/2;
            int offyy=offy+sy/2-ssy/2;
            cgFillPolygon(c, offxx, offyy, offxx+ssx, offyy+ssy/2, offxx, offyy+ssy, m_color);
            cgDrawPolygon(c, offxx, offyy, offxx+ssx, offyy+ssy/2, offxx, offyy+ssy, m_shadowColor, m_linewidth);
            cgDrawLine(c, offxx, offyy, offxx+ssx, offyy+ssy/2, m_highlightColor, m_linewidth);
            cairo_save(c);
                int Nmax=20;
                float alpha=since_last/1000.0*2.0*M_PI;
                for (int i=Nmax-1; i>=0; i--) {
                    CGColor col=m_highlightColor.linearColor(float(i)/float(Nmax-1), m_backgroundColor);
                    col.cairo_set_source(c);
                    cairo_set_line_width(c, 2.0*m_linewidth);
                    cairo_arc(c, offx+sx/2, offy+sy/2, 7*sy/12, alpha, alpha+2.0*M_PI/float(Nmax));
                    cairo_stroke(c);
                    alpha+=(2.0*M_PI/float(Nmax));
                }

            cairo_restore(c);
        } else if (m_symbol==CGSymbol::iStop) {
            cgDrawFilledRectangle(c, offx, offy, sx, sy, m_color);
            cgDrawLines(c, offx, offy, offx, offy+sy, offx+sx, offy+sy, m_shadowColor, m_linewidth);
            cgDrawLines(c, offx, offy, offx+sx, offy, offx+sx, offy+sy, m_highlightColor, m_linewidth);
        } else if (m_symbol==CGSymbol::iPause) {
            int offxx=offx;
            int offyy=offy;
            cgDrawFilledRectangle(c, offxx, offyy, sx/3, sy, m_color);
            cgDrawLines(c, offxx, offyy, offxx, offyy+sy, offxx+sx/3, offyy+sy, m_shadowColor, m_linewidth);
            cgDrawLines(c, offxx, offyy, offxx+sx/3, offyy, offxx+sx/3, offyy+sy, m_highlightColor, m_linewidth);
            offxx+=(2*sx/3);
            cgDrawFilledRectangle(c, offxx, offyy, sx/3, sy, m_color);
            cgDrawLines(c, offxx, offyy, offxx, offyy+sy, offxx+sx/3, offyy+sy, m_shadowColor, m_linewidth);
            cgDrawLines(c, offxx, offyy, offxx+sx/3, offyy, offxx+sx/3, offyy+sy, m_highlightColor, m_linewidth);
        }
    cairo_restore(c);
    //lastpaint=tnow;
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
