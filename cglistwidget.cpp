#include "cglistwidget.h"


CGListWidget::CGListWidget(CGWidget *parent):
    CGFrame(parent)
{
    m_selectedColor=CGColor::ccGray25;
    m_selectedTextColor=CGColor::ccWhite;
    m_scrollbarColor=CGColor::ccGray25;
    m_scrollbarBackgroundColor=CGColor::ccGray10;
    m_showScrollbar=true;
    m_currentItem=0;
    m_items.clear();
    m_startVisible=0;
    m_scrollbarWidth=10;
}

CGListWidget::CGListWidget(int x, int y, int width, int height, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    m_selectedColor=CGColor::ccGray25;
    m_selectedTextColor=CGColor::ccWhite;
    m_scrollbarColor=CGColor::ccGray25;
    m_scrollbarBackgroundColor=CGColor::ccGray10;
    m_showScrollbar=true;
    m_currentItem=0;
    m_items.clear();
    m_startVisible=0;
    m_scrollbarWidth=7;
}

CGListWidget::~CGListWidget()
{

}

void CGListWidget::paint(cairo_t *c) const
{
    CGFrame::paint(c);

    float w=m_width-2.0*m_frameWidth-2;
    if (m_showScrollbar) {
        w=w-m_scrollbarWidth;
    }

    cairo_save(c);

        cairo_rectangle(c, m_frameWidth, m_frameWidth, w, m_height-2.0*m_frameWidth);
        cairo_clip (c);
        int i=m_startVisible;
        float x=m_border+1.0;
        float y=m_border+2.0;
        float lh=itemHeight();
        int ifirst=-1;
        int ilast=-1;
        //std::cout<<"----------------------- m_startVisible="<<m_startVisible<<"\n";
        while (y<m_height && i<(int)m_items.size()) {
            if (i>=0 && i<(int)m_items.size()) {
                //std::cout<<"CGListWidget: i="<<i<<": x="<<x<<", y="<<y<<": "<<m_items[i]<<"   lh="<<lh<<"\n";
                CGColor col=m_textColor;
                if (m_currentItem==i) {
                    cairo_rectangle(c, x, y, w, lh);
                    cairo_set_source_rgba(c, m_selectedColor.redf(), m_selectedColor.greenf(), m_selectedColor.bluef(), m_selectedColor.alphaf());
                    cairo_fill(c);

                    col=m_selectedTextColor;
                    if (ifirst<0) ifirst=i;
                    if (y+lh<m_height) ilast=i;
                }
                drawAlignedColoredText(c, x, y+2, w, lh, m_items[i], col, cgalLeft, cgalTop);
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

        float sbh=float(m_height-2.0*m_frameWidth)-3.0;
        float sh=std::max(float(m_scrollbarWidth), sbh*float(ilast-ifirst)/float(count()-1));
        float sh_start=(sbh-sh)*float(ifirst)/float(count()-1);
        //std::cout<<"cur="<<m_currentItem<<" start="<<m_startVisible<<" sbh="<<sbh<<" sh="<<sh<<" sh_start="<<sh_start<<" w="<<w<<"\n";

        cairo_rectangle(c, w+1, m_frameWidth+2, m_scrollbarWidth, sbh);
        cairo_set_source_rgba(c, m_scrollbarBackgroundColor.redf(), m_scrollbarBackgroundColor.greenf(), m_scrollbarBackgroundColor.bluef(), m_scrollbarBackgroundColor.alphaf());
        cairo_fill(c);

        cairo_rectangle(c, w+1, m_frameWidth+2+sh_start, m_scrollbarWidth, sh);
        cairo_set_source_rgba(c, m_scrollbarColor.redf(), m_scrollbarColor.greenf(), m_scrollbarColor.bluef(), m_scrollbarColor.alphaf());
        cairo_fill(c);
    }
}

void CGListWidget::addItem(const std::string &item)
{
    m_items.push_back(item);
}

void CGListWidget::addItems(const std::vector<std::string> &items)
{
    for (size_t i=0; i<items.size(); i++) {
        m_items.push_back(items[i]);
    }
}

void CGListWidget::clear()
{
    m_items.clear();
}

size_t CGListWidget::count() const
{
    return m_items.size();
}

std::string CGListWidget::item(int i, const std::string &defaultItem) const
{
    if (i<0 || i>=(int)m_items.size()) return defaultItem;
    return m_items[i];
}

void CGListWidget::updateState()
{
    if (m_startVisible>=(int64_t)m_items.size()) m_startVisible=m_items.size()-1;
    if (m_currentItem>=(int64_t)m_items.size()) m_currentItem=m_items.size()-1;
    if (m_currentItem<=0) m_currentItem=0;
    if (m_items.size()<=0) m_currentItem=0;
    if (m_startVisible<=0) m_startVisible=0;
    if (m_items.size()<=0) m_startVisible=0;

    if (m_currentItem>=0) {
        int i=m_startVisible;
        float lh=itemHeight();
        float y=m_border+2.0;
        int ifirst=-1;
        int ilast=-1;
        while (y<m_height && i<(int)m_items.size()) {
            if (i>=0 && i<(int)m_items.size()) {
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

float CGListWidget::itemHeight() const
{
    return m_fontSize*1.3;
}
