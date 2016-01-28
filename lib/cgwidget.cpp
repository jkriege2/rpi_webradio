#include "cgwidget.h"
#include "cglayout.h"
#include <iostream>
#include <limits>


CGWidget::CGWidget(CGWidget *parent):
    CGFontProps()
{
    m_layout=NULL;
    m_minSize=cgSize<unsigned int>(0,0);
    m_maxSize=cgSize<unsigned int>(std::numeric_limits<int>().max(), std::numeric_limits<int>().max());
    m_border=0;
    m_hasFocus=false;
    m_parent=NULL;
    m_mayReceiveFocus=false;
    m_eventsOnlyIfFocused=false;
    setParent(parent);
    m_x=0;
    m_y=0;
    m_width=1;
    m_height=1;
    setBackgroundColor(CGColor::ccTransparent);
    setPropsFromDefaultPalette();
}

CGWidget::CGWidget(int x, int y, int width, int height, CGWidget *parent):
    CGFontProps()
{
    m_layout=NULL;
    m_minSize=cgSize<unsigned int>(0,0);
    m_maxSize=cgSize<unsigned int>(std::numeric_limits<int>().max(), std::numeric_limits<int>().max());
    m_border=0;
    m_hasFocus=false;
    m_parent=NULL;
    m_mayReceiveFocus=false;
    m_eventsOnlyIfFocused=false;
    setParent(parent);
    m_x=0;
    m_y=0;
    m_width=1;
    m_height=1;
    setBackgroundColor(CGColor::ccTransparent);
    m_x=x;
    m_y=y;
    m_width=width;
    m_height=height;
    setPropsFromDefaultPalette();
}

CGWidget::~CGWidget()
{
    for (std::list<CGWidget*>::const_iterator it=m_children.begin(); it!=m_children.end(); it++) {
        if (*it) {
            delete *it;
        }
    }
    m_children.clear();
    if (m_layout) delete m_layout;
}

void CGWidget::resize(unsigned int width, unsigned int height)
{
    unsigned int w=cgBound<unsigned int>(m_minSize.width, width, m_maxSize.width);
    unsigned int h=cgBound<unsigned int>(m_minSize.height, height, m_maxSize.height);
    bool newsize=(m_width!=w)||(m_height!=h);
    //std::cout<<"CGWidget::resize("<<width<<","<<height<<"): "<<w<<","<<h<<": "<<newsize<<"\n";
    if (newsize) {
        m_width=w;
        m_height=h;
        sigResize(w, h);
        if (m_parent && m_parent->layout()) m_parent->layout()->layoutWidgets();
        else if (m_layout) m_layout->layoutWidgets();
    }
}

cgSize<unsigned int> CGWidget::sizeForChildren() const
{
    return cgSize<unsigned int>(width()-2*border(), height()-2*border());
}

void CGWidget::move(int x, int y)
{
    m_x=x;
    m_y=y;
}

void CGWidget::setParent(CGWidget *p)
{
    //std::cout<<this<<" CGWidget::setParent("<<p<<").0 m_parent="<<m_parent<<"\n";
    if (m_parent) {
        m_parent->m_children.remove(p);
    }
    m_parent=p;
    if (m_parent) {
        m_parent->m_children.push_back(this);
    }
    //std::cout<<this<<" CGWidget::setParent("<<p<<").0 m_parent="<<m_parent<<"\n";
}

void CGWidget::paint(cairo_t *c)
{
    if (!m_backgroundColor.isTransparent()) {
        cairo_rectangle(c, 0, 0, m_width, m_height);
        m_backgroundColor.cairo_set_source(c);
        cairo_fill(c);
    }
    cairo_save(c);
        cairo_translate(c, m_border, m_border);
        cairo_rectangle(c, 0,0, m_width-2.0*m_border, m_height-2.0*m_border);
        cairo_clip (c);
            //std::cout<<this<<" CGWidget::paint() size="<<m_children.size()<<"\n";
            for (std::list<CGWidget*>::const_iterator it=m_children.begin(); it!=m_children.end(); ++it) {
                if (*it) {
                    cairo_save(c);
                        cairo_translate(c, (*it)->x(), (*it)->y());
                        cairo_rectangle(c, 0, 0, (*it)->width(), (*it)->height());
                        cairo_clip (c);
                        //std::cout<<"  draw child "<<c<<"\n";
                        (*it)->paint(c);
                    cairo_restore(c);
                }
            }
    cairo_restore(c);
}

void CGWidget::event(CGEvent *e)
{
    for (std::list<CGWidget*>::const_iterator it=m_children.begin(); it!=m_children.end(); ++it) {
        if (*it) {
            //std::cout<<"draw child\n";
            (*it)->event(e);
            if (e->accepted()) return;
        }
    }
}

bool CGWidget::isAbsPosInside(int x, int y)
{
    const int ax=absX();
    const int ay=absY();
    return (x>=ax && y>=ay && x<ax+(int)m_width && y<ay+(int)m_height);
}

bool CGWidget::isRelPosInside(int x, int y)
{
    return isAbsPosInside(absX()+x, absY()+y);
}

void CGWidget::setPropsFromPalette(CGPalette *palette)
{
    setFontPropsFromPalette(palette);
    if (palette) {
        m_backgroundColor=palette->color(CGPalette::crBackground);
    }
    for (std::list<CGWidget*>::const_iterator it=m_children.begin(); it!=m_children.end(); ++it) {
        if (*it) {
            setPropsFromPalette(palette);
        }
    }
}

void CGWidget::setPropsFromDefaultPalette()
{
    setPropsFromPalette(CGPalette::defaultPalette());

}

void CGWidget::setMayReceiveFocus(bool en)
{
    m_mayReceiveFocus=en;
}

void CGWidget::setEventsOnlyIfFocused(bool en)
{
    m_eventsOnlyIfFocused=en;
}

CGWidget *CGWidget::getNextFocusChild() const
{
    CGWidget* first=NULL;
    bool foundFocus=false;
    for (std::list<CGWidget*>::const_iterator it=m_children.begin(); it!=m_children.end(); ++it) {
        if (*it) {
            if ((*it)->mayReceiveFocus()) {
                if (!first) first=*it;
                if ((*it)->hasFocus() && !foundFocus) {
                    foundFocus=true;
                } else if (foundFocus) {
                    return (*it);
                }
            }
        }
    }
    return first;
}

CGWidget *CGWidget::getFirstFocusChild() const
{
    for (std::list<CGWidget*>::const_iterator it=m_children.begin(); it!=m_children.end(); ++it) {
        if (*it) {
            if ((*it)->mayReceiveFocus()) {
                return *it;
            }
        }
    }
    return NULL;
}

void CGWidget::setLayout(CGLayout *layout, bool deleteOld)
{
    //std::cout<<this<<" CGWidget::setLayout("<<layout<<").0 m_layout="<<m_layout<<"\n";

    if (layout!=m_layout) {
        //std::cout<<"CGWidget::setLayout("<<layout<<").1 m_layout="<<m_layout<<"\n";
        if (deleteOld && m_layout) delete m_layout;
        //std::cout<<"CGWidget::setLayout("<<layout<<").2 m_layout="<<m_layout<<"\n";
        if (layout && layout->parent()!=this) layout->setParent(this);
    }
    m_layout=layout;
    //std::cout<<"CGWidget::setLayout("<<layout<<").3 m_layout="<<m_layout<<"\n";
}

void CGWidget::setFocus()
{
    if (!m_hasFocus && m_mayReceiveFocus) {
        CGWidget* wf=getFirstFocusChild();
        if (wf) wf->setFocus();
        else m_hasFocus=true;
    }
}

void CGWidget::focusNext()
{
    CGWidget* wf=getNextFocusChild();
    if (wf) {
        wf->setFocus();
        return;
    } else {
        if (m_parent) {
            bool found=false;
            for (std::list<CGWidget*>::const_iterator it=m_parent->m_children.begin(); it!=m_parent->m_children.end(); ++it) {
                if (*it) {
                    if (*it==this) {
                        found=true;
                    } else if (found) {
                        if ((*it)->mayReceiveFocus() && (! (*it)->hasFocus())) {
                            (*it)->setFocus();
                            return;
                        }
                    }
                }
            }
        }

    }
    setFocus();
    return;
}

bool CGWidget::hasFocus() const
{
    return m_hasFocus && m_mayReceiveFocus;
}

void CGWidget::postEvent(CGEvent *e)
{
    if (!m_eventsOnlyIfFocused || (m_eventsOnlyIfFocused&&hasFocus())) {
        if (e && !e->accepted()) event(e);
    }
}


void CGWidget::setBackgroundColor(CGColor col)
{
    this->m_backgroundColor=col;
}


void CGWidget::setMinimumSize(cgSize<unsigned int> size) {
    m_minSize=size;
}

void CGWidget::setMaximumSize(cgSize<unsigned int> size) {
    m_maxSize=size;
}

