#include "cgtreebase.h"


CGTreeBase::CGTreeBase(CGWidget *parent):
    CGFrame(parent)
{
    m_textColor=CGColor::ccGray50;
    m_selectedColor=CGColor::ccGray25;
    m_selectedTextColor=CGColor::ccWhite;
    m_scrollbarColor=CGColor::ccGray25;
    m_scrollbarBackgroundColor=CGColor::ccGray10;
    m_subindicatorWidth=8;
    m_showScrollbar=true;
    m_showUpperLevels=true;
    m_currentItem=0;
    m_startVisible=0;
    m_scrollbarWidth=10;
    m_treeIndent=10;
    setPropsFromDefaultPalette();
}

CGTreeBase::CGTreeBase(int x, int y, int width, int height, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    m_textColor=CGColor::ccGray50;
    m_selectedColor=CGColor::ccGray25;
    m_selectedTextColor=CGColor::ccWhite;
    m_scrollbarColor=CGColor::ccGray25;
    m_scrollbarBackgroundColor=CGColor::ccGray10;
    m_subindicatorWidth=8;
    m_treeIndent=10;
    m_showScrollbar=true;
    m_showUpperLevels=true;
    m_currentItem=0;
    m_startVisible=0;
    m_scrollbarWidth=10;
    setPropsFromDefaultPalette();
}

CGTreeBase::~CGTreeBase()
{
    clear();
}


void CGTreeBase::updateState()
{
    int cnt=count();
    int level=currentLevel();
    if (m_startVisible>=cnt) m_startVisible=cnt-1;
    if (m_currentItem>=cnt) m_currentItem=cnt-1;
    if (m_currentItem<=0) m_currentItem=0;
    if (cnt<=0) m_currentItem=0;
    if (m_startVisible<=0) m_startVisible=0;
    if (cnt<=0) m_startVisible=0;

    if (m_currentItem>=0) {
        int i=m_startVisible;
        float lh=itemHeight();
        float y=m_border+2.0;
        if (m_showUpperLevels) {
            if (level==2) {
                y+=lh;
            } else if (level==3) {
                y+=(2.0*lh);
            } else if (level>3) {
                y+=(3.0*lh);
            }
        }
        int ifirst=-1;
        int ilast=-1;
        while (y<m_height && i<cnt) {
            if (i>=0 && i<cnt) {
                if (ifirst<0) ifirst=i;
                if (y+lh<m_height) ilast=i;
            }
            y=y+lh;
            i++;
        }

        if (ifirst<0) ifirst=0;
        if (ilast<0) ilast=0;
        if (ilast==ifirst) ilast=ifirst+1;

        if (m_currentItem<ifirst) {
            m_startVisible=m_currentItem;
        } else if (m_currentItem>ilast) {
            m_startVisible=m_currentItem-(ilast-ifirst);
        }
        if (m_startVisible<0) m_startVisible=0;
    }

}

void CGTreeBase::paint(cairo_t *c)
{
    CGFrame::paint(c);

    int cnt=count();
    int level=currentLevel();

    float w=m_width-2.0*m_frameWidth-2;
    if (m_showScrollbar) {
        w=w-m_scrollbarWidth;
    }

    cairo_save(c);

        cairo_rectangle(c, m_frameWidth, m_frameWidth, w, m_height-2.0*m_frameWidth);
        cairo_clip (c);
        int i=m_startVisible;
        float x=m_border+1.0;
        float xtxt=x;
        float y=m_border+2.0;
        float lh=itemHeight();
        if (m_showUpperLevels) {
            if (level==2) {
                std::string txt1=parentItemName();
                CGColor cv=m_selectedTextColor.colorLinearTo(0.5, m_textColor);
                CGColor cb=m_selectedColor.colorLinearTo(0.5, m_backgroundColor);
                cairo_rectangle(c, x, y, w, lh);
                cb.cairo_set_source(c);
                cairo_fill(c);
                drawAlignedColoredText(c, xtxt+m_subindicatorWidth+2, y+3, w-m_subindicatorWidth-2, lh, txt1, cv, cgalLeft, cgalTop);
                drawIndicator(c,xtxt,y,lh,cv);
                y+=lh;
                xtxt+=m_treeIndent;
            } else if (level==3) {
                std::string txt1, txt2;
                std::vector<std::string> txts=parentItemNames(2);
                if (txts.size()>0) txt1=txts[0];
                if (txts.size()>1) txt2=txts[1];
                CGColor cv=m_selectedTextColor.colorLinearTo(0.33, m_textColor);
                CGColor cb=m_selectedColor.colorLinearTo(0.33, m_backgroundColor);
                cairo_rectangle(c, x, y, w, lh);
                cb.cairo_set_source(c);
                cairo_fill(c);
                drawAlignedColoredText(c, xtxt+m_subindicatorWidth+2, y+3, w-m_subindicatorWidth-2, lh, txt2, cv, cgalLeft, cgalTop);
                drawIndicator(c,xtxt,y,lh,cv);
                y+=lh;
                xtxt+=m_treeIndent;

                cv=m_selectedTextColor.colorLinearTo(0.66, m_textColor);
                cb=m_selectedColor.colorLinearTo(0.66, m_backgroundColor);
                cairo_rectangle(c, x, y, w, lh);
                cb.cairo_set_source(c);
                cairo_fill(c);
                drawAlignedColoredText(c, xtxt+m_subindicatorWidth+2, y+3, w-m_subindicatorWidth-2, lh, txt1, cv, cgalLeft, cgalTop);
                drawIndicator(c,xtxt,y,lh,cv);
                y+=lh;
                xtxt+=m_treeIndent;
            } else if (level>3) {
                std::string txt1, txt2;
                std::string txtell="...";
                std::vector<std::string> txts=parentItemNames(2);
                if (txts.size()>0) txt1=txts[0];
                if (txts.size()>1) txt2=txts[1];
                CGColor cv=m_selectedTextColor.colorLinearTo(0.25, m_textColor);
                CGColor cb=m_selectedColor.colorLinearTo(0.25, m_backgroundColor);
                cairo_rectangle(c, x, y, w, lh);
                cb.cairo_set_source(c);
                cairo_fill(c);
                drawAlignedColoredText(c, xtxt+m_subindicatorWidth+2, y+3, w-m_subindicatorWidth-2, lh, txt2, cv, cgalLeft, cgalTop);
                drawIndicator(c,xtxt,y,lh,cv);
                y+=lh;
                xtxt+=m_treeIndent;

                cv=m_selectedTextColor.colorLinearTo(0.5, m_textColor);
                cb=m_selectedColor.colorLinearTo(0.5, m_backgroundColor);
                cairo_rectangle(c, x, y, w, lh);
                cb.cairo_set_source(c);
                cairo_fill(c);
                drawAlignedColoredText(c, xtxt+m_subindicatorWidth+2, y+3, w-m_subindicatorWidth-2, lh, txtell, cv, cgalLeft, cgalTop);
                drawIndicator(c,xtxt,y,lh,cv);
                y+=lh;
                xtxt+=m_treeIndent;

                cv=m_selectedTextColor.colorLinearTo(0.75, m_textColor);
                cb=m_selectedColor.colorLinearTo(0.75, m_backgroundColor);
                cairo_rectangle(c, x, y, w, lh);
                cb.cairo_set_source(c);
                cairo_fill(c);
                drawAlignedColoredText(c, xtxt+m_subindicatorWidth+2, y+3, w-m_subindicatorWidth-2, lh, txt1, cv, cgalLeft, cgalTop);
                drawIndicator(c,xtxt,y,lh,cv);
                y+=lh;
                xtxt+=m_treeIndent;

            }
        }

        int ifirst=-1;
        int ilast=-1;
        //std::cout<<"----------------------- m_startVisible="<<m_startVisible<<"\n";
        while (y<m_height && i<cnt) {
            if (i>=0 && i<cnt) {

                CGColor col=m_textColor;
                if (m_currentItem==i) {
                    cairo_rectangle(c, x, y, w, lh);
                    m_selectedColor.cairo_set_source(c);
                    cairo_fill(c);

                    col=m_selectedTextColor;
                    if (ifirst<0) ifirst=i;
                    if (y+lh<m_height) ilast=i;
                }
                //std::cout<<"CGTreeBase: i="<<i<<": x="<<x<<", y="<<y<<": "<<item(i)<<"   lh="<<lh<<"   col="<<col<<"\n";
                drawAlignedColoredText(c, xtxt+m_subindicatorWidth+2, y+3, w-m_subindicatorWidth-2, lh, itemName(i), col, cgalLeft, cgalTop);

                if (hasChildren(i)){
                    drawIndicator(c,xtxt,y,lh,col);
                }

            }
            y=y+lh;
            i++;
        }

        if (ifirst<0) ifirst=0;
        if (ilast<0) ilast=0;
        if (ilast==ifirst) ilast=ifirst+1;
    //std::cout<<"-----------------------\n";
    cairo_restore(c);


    if (m_showScrollbar) {
        paintScrollbar(c, w+1,m_frameWidth+2,m_scrollbarWidth,m_height-2.0*m_frameWidth-2, 0, count(), ifirst, ilast-ifirst);
    }

}

void CGTreeBase::clear()
{

}






float CGTreeBase::itemHeight() const
{
    return m_fontSize*1.3;
}

void CGTreeBase::drawIndicator(cairo_t *c, float x, float y, float lh, CGColor col) const
{
    float isiz=m_subindicatorWidth*0.75;
    cairo_move_to(c, x+m_subindicatorWidth/2.0+isiz/2.0, y+lh/2.0);
    cairo_rel_line_to(c, -isiz, -isiz/2.0);
    cairo_rel_line_to(c, 0, isiz);
    cairo_close_path(c);
    col.cairo_set_source(c);
    cairo_fill(c);
}


void CGTreeBase::setPropsFromPalette(CGPalette *palette)
{
    CGFrame::setPropsFromPalette(palette);
    if (palette) {
        setScrollbarPropsFromPalette(palette);
        setSelectedColor(palette->color(CGPalette::crSelection));
        setSelectedTextColor(palette->color(CGPalette::crSelectionIconOrText));
    }
}
