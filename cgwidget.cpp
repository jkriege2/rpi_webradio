#include "cgwidget.h"
#include <iostream>

CGWidget::CGWidget(CGWidget *parent)
{
    m_border=0;
    m_parent=NULL;
    setParent(parent);
    m_x=0;
    m_y=0;
    m_width=1;
    m_height=1;
    setBackgroundColor(CGColor::transparent());
}

CGWidget::CGWidget(int x, int y, int width, int height, CGWidget *parent)
{
    m_border=0;
    m_parent=NULL;
    setParent(parent);
    m_x=x;
    m_y=y;
    m_width=width;
    m_height=height;
    setBackgroundColor(CGColor::transparent());
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
    if (m_backgroundColor.a!=0) {
        cairo_rectangle(c, absX(), absY(), m_width, m_height);
        cairo_set_source_rgba(c, m_backgroundColor.rf(), m_backgroundColor.gf(), m_backgroundColor.bf(), m_backgroundColor.af());
        cairo_fill(c);
    }

    //std::cout<<"CGWidget::paint()\n";
    for (std::list<CGWidget*>::const_iterator it=m_children.begin(); it!=m_children.end(); ++it) {
        if (*it) {
            //std::cout<<"draw child\n";
            (*it)->paint(c);
        }
    }
}


void CGWidget::setBackgroundColor(CGColor col)
{
    this->m_backgroundColor=col;
}
