#include "cgtreewidget.h"


CGTreeWidget::CGTreeWidget(CGWidget *parent):
    CGFrame(parent)
{
    m_textColor=CGColor::ccGray50;
    m_selectedColor=CGColor::ccGray25;
    m_selectedTextColor=CGColor::ccWhite;
    m_scrollbarColor=CGColor::ccGray25;
    m_scrollbarBackgroundColor=CGColor::ccGray10;
    m_subindicatorWidth=8;
    m_showScrollbar=true;
    m_currentItem=0;
    m_root=NULL;
    m_startVisible=0;
    m_scrollbarWidth=10;
}

CGTreeWidget::CGTreeWidget(int x, int y, int width, int height, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    m_textColor=CGColor::ccGray50;
    m_selectedColor=CGColor::ccGray25;
    m_selectedTextColor=CGColor::ccWhite;
    m_scrollbarColor=CGColor::ccGray25;
    m_scrollbarBackgroundColor=CGColor::ccGray10;
    m_subindicatorWidth=8;
    m_showScrollbar=true;
    m_currentItem=0;
    m_root=NULL;
    m_startVisible=0;
    m_scrollbarWidth=7;
}

CGTreeWidget::~CGTreeWidget()
{
    clear();
}

void CGTreeWidget::paint(cairo_t *c) const
{
    CGFrame::paint(c);

    int cnt=count();

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
        while (y<m_height && i<cnt) {
            if (i>=0 && i<cnt) {
                //std::cout<<"CGTreeWidget: i="<<i<<": x="<<x<<", y="<<y<<": "<<item(i)<<"   lh="<<lh<<"\n";
                CGColor col=m_textColor;
                if (m_currentItem==i) {
                    cairo_rectangle(c, x, y, w, lh);
                    cairo_set_source_rgba(c, m_selectedColor.redf(), m_selectedColor.greenf(), m_selectedColor.bluef(), m_selectedColor.alphaf());
                    cairo_fill(c);

                    col=m_selectedTextColor;
                    if (ifirst<0) ifirst=i;
                    if (y+lh<m_height) ilast=i;
                }
                drawAlignedColoredText(c, x+m_subindicatorWidth+2, y+2, w-m_subindicatorWidth-2, lh, itemName(i), col, cgalLeft, cgalTop);

                if (hasChildren(i)){
                    cairo_set_source_rgba(c, col.redf(), col.greenf(), col.bluef(), col.alphaf());
                    cairo_move_to(c, x+m_subindicatorWidth, y+lh/2);
                    cairo_line_to(c, x, y+lh/2-m_subindicatorWidth/2);
                    cairo_line_to(c, x, y+lh/2+m_subindicatorWidth/2);
                    cairo_close_path(c);
                    cairo_fill(c);
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

void CGTreeWidget::setCurrentItem(const CGTreeWidget::TreeItem *it)
{
    if (it) {
        m_root=it->parent;
        m_currentItem=m_root->indexOf(it);
    }
    updateState();
}

void CGTreeWidget::downLevel()
{
    if (m_root) {
        CGTreeWidget::TreeItem *it=currentTreeItem();
        if (it && it->hasChildern()) {
            m_root=it;
            m_currentItem=0;
        }
    }
    updateState();
}


void CGTreeWidget::upLevel()
{
    if (m_root && m_root->parent) {
        m_root=m_root->parent;
        m_currentItem=0;
    }
    updateState();
}

CGTreeWidget::TreeItem *CGTreeWidget::addItem(const std::string &name, const std::string &data, int id)
{
    if (!m_root) {
        m_root=new CGTreeWidget::TreeItem(NULL);
    }
    if (m_root) {
        return m_root->addChild(name, data, id);
    }
    return NULL;
}


void CGTreeWidget::clear()
{
    if (!m_root) return;
    CGTreeWidget::TreeItem * r=m_root->trueRoot();
    delete r;
    m_root=NULL;
    m_currentItem=-1;
    updateState();
}

size_t CGTreeWidget::count() const
{
    if (m_root) {
        return m_root->count();
    } else {
        return 0;
    }
}

std::string CGTreeWidget::itemName(int i, const std::string &defaultItem) const
{
    if (!m_root) return defaultItem;
    CGTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it->name;
    return defaultItem;
}

std::string CGTreeWidget::itemData(int i, const std::string &defaultItem) const
{
    if (!m_root) return defaultItem;
    CGTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it->data;
    return defaultItem;
}

int CGTreeWidget::itemID(int i, int defaultItem) const
{
    if (!m_root) return defaultItem;
    CGTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it->id;
    return defaultItem;
}

bool CGTreeWidget::hasChildren(int i) const
{
    if (!m_root) return false;
    CGTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it->hasChildern();
    return false;
}

CGTreeWidget::TreeItem *CGTreeWidget::item(int i) const
{
    if (!m_root) return NULL;
    CGTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it;
    return NULL;
}

void CGTreeWidget::updateState()
{
    int cnt=count();
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

float CGTreeWidget::itemHeight() const
{
    return m_fontSize*1.3;
}


CGTreeWidget::TreeItem::TreeItem(TreeItem *parent)
{
    this->parent=parent;
    name="";
    data="";
    id=0;
}

CGTreeWidget::TreeItem::~TreeItem()
{
    clear();
}

void CGTreeWidget::TreeItem::clear()
{
    for (size_t i=0; i<children.size(); i++) {
        delete children[i];
    }
    children.clear();
}

CGTreeWidget::TreeItem *CGTreeWidget::TreeItem::addChild(const std::string &name, const std::string &data, int id)
{
    CGTreeWidget::TreeItem* it=new CGTreeWidget::TreeItem(this);
    it->name=name;
    it->data=data;
    it->id=id;
    children.push_back(it);
    return it;
}

void CGTreeWidget::TreeItem::deleteChild(int i)
{
    if (i>=0 && i<(int64_t)children.size()) {
        CGTreeWidget::TreeItem * it=child(i);
        children.erase(children.begin()+i);
        if (it) delete it;
    }
}

CGTreeWidget::TreeItem *CGTreeWidget::TreeItem::child(int i)
{
    if (i>=0 && i<(int64_t)children.size()) {
        return children[i];
    }
    return NULL;
}

const CGTreeWidget::TreeItem *CGTreeWidget::TreeItem::child(int i) const
{
    if (i>=0 && i<(int64_t)children.size()) {
        return children[i];
    }
    return NULL;
}

int CGTreeWidget::TreeItem::count() const
{
    return children.size();
}

int CGTreeWidget::TreeItem::indexOf(const CGTreeWidget::TreeItem *it)
{
    for (size_t i=0; i<children.size(); i++) {
        if (children[i]==it) return i;
    }
    return -1;
}

CGTreeWidget::TreeItem *CGTreeWidget::TreeItem::trueRoot()
{
    CGTreeWidget::TreeItem *r=parent;
    while (r && r->parent) {
        r=r->parent;
    }
    return r;
}
