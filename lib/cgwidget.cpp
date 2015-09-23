#include "cgwidget.h"
#include <iostream>

CGWidget::CGWidget(CGWidget *parent)
{
    m_border=0;
    m_hasFocus=false;
    m_parent=NULL;
    m_mayReceiveFocus=false;
    setParent(parent);
    m_x=0;
    m_y=0;
    m_width=1;
    m_height=1;
    setBackgroundColor(CGColor::ccTransparent);
    setPropsFromDefaultPalette();
}

CGWidget::CGWidget(int x, int y, int width, int height, CGWidget *parent)
{
    m_border=0;
    m_hasFocus=false;
    m_parent=NULL;
    m_mayReceiveFocus=false;
    setParent(parent);
    m_x=x;
    m_y=y;
    m_width=width;
    m_height=height;
    setBackgroundColor(CGColor::ccTransparent);
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
}

void CGWidget::resize(int width, int height)
{
    m_width=width;
    m_height=height;
}

void CGWidget::move(int x, int y)
{
    m_x=x;
    m_y=y;
}

void CGWidget::setParent(CGWidget *p)
{
    if (m_parent) {
        m_parent->m_children.remove(p);
    }
    m_parent=p;
    if (m_parent) {
        m_parent->m_children.push_back(this);
    }
}

void CGWidget::paint(cairo_t *c) const
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
            //std::cout<<"CGWidget::paint()\n";
            for (std::list<CGWidget*>::const_iterator it=m_children.begin(); it!=m_children.end(); ++it) {
                if (*it) {
                    cairo_save(c);
                        cairo_translate(c, (*it)->x(), (*it)->y());
                        cairo_rectangle(c, 0, 0, (*it)->width(), (*it)->height());
                        cairo_clip (c);
                        //std::cout<<"draw child\n";
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
    return (x>=ax && y>=ay && x<ax+m_width && y<ay+m_height);
}

bool CGWidget::isRelPosInside(int x, int y)
{
    return isAbsPosInside(absX()+x, absY()+y);
}

void CGWidget::setPropsFromPalette(CGPalette *palette)
{
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


void CGWidget::setBackgroundColor(CGColor col)
{
    this->m_backgroundColor=col;
}
