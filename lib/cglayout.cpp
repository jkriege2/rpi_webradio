#include "cgprecomp.h"
#include "cglayout.h"
#include "cgwidget.h"
#include "cgframe.h"
#include <iostream>


CGLayout::CGLayout(CGWidget *parent):
    m_parent(NULL), m_spacing(1)
{
    //std::cout<<this<<" CGLayout::CGLayout("<<parent<<").0 m_parent="<<m_parent<<"\n";
    setParent(parent);
    if (parent) parent->setLayout(this, false);
    //std::cout<<this<<" CGLayout::CGLayout("<<parent<<").1 m_parent="<<m_parent<<"\n";
}

CGLayout::~CGLayout()
{
    if (m_parent) m_parent->setLayout(NULL, false);
}

void CGLayout::layoutWidgets()
{
    std::vector<CGWidget*> m_data=managedWidgets();
    for (size_t i=0; i<m_data.size(); i++) {
        if (m_data[i]) {
            if (m_data[i]->parent()!=m_parent) {
                m_data[i]->setParent(m_parent);
            }
            if (m_data[i]->layout()) {
                m_data[i]->layout()->layoutWidgets();
            }
        }
    }
}

void CGLayout::setParent(CGWidget *p)
{
    //std::cout<<this<<" CGLayout::setParent("<<p<<").0 m_parent="<<m_parent<<"\n";
    /*if (m_parent!=p) {
        //std::cout<<"CGLayout::setParent("<<p<<").1 m_parent="<<m_parent<<"\n";
        if (m_parent && (m_parent->layout()==this)) {
            m_parent->setLayout(NULL);
            m_parent=NULL;
        }
        //std::cout<<"CGLayout::setParent("<<p<<").2 m_parent="<<m_parent<<"\n";
        if (p && p->layout()!=this) {
            p->setLayout(this);
        }
    }*/
    m_parent=p;
    //std::cout<<this<<" CGLayout::setParent("<<p<<").3 m_parent="<<m_parent<<"\n";
}

cgSize<unsigned int> CGLayout::minimumSize() const
{
    return minimumSizeFromWidgets();
}

void CGLayout::setSpacing(unsigned int spacing)
{
    m_spacing=spacing;
    layoutWidgets();
}

CGLinearLayout::CGLinearLayout(CGWidget *parent, cgDirection direction):
    CGLayout(parent), m_otherAxisSizeMode(oasmAvailableSpace)
{
    //std::cout<<this<<" CGLinearLayout::CGLinearLayout("<<parent<<").0 m_parent="<<m_parent<<"\n";
    m_direction=direction;
    //std::cout<<this<<" CGLinearLayout::CGLinearLayout("<<parent<<").1 m_parent="<<m_parent<<"\n";
}

CGLinearLayout::~CGLinearLayout()
{

}

void CGLinearLayout::addWidget(CGWidget *widget, int stretch)
{
    if (!widget) return;
    //std::cout<<this<<" CGLayout::addWidget("<<widget<<", "<<stretch<<").0 m_parent="<<m_parent<<"\n";
    CGLinearLayout::layoutData data;
    data.stretch=stretch;
    data.widget=widget;
    m_data.push_back(data);
    if (m_parent && widget->parent()!=m_parent) widget->setParent(m_parent);
    //std::cout<<this<<" CGLayout::addWidget("<<widget<<", "<<stretch<<").1 m_parent="<<m_parent<<"\n";
    layoutWidgets();
    //std::cout<<this<<" CGLayout::addWidget("<<widget<<", "<<stretch<<").2 m_parent="<<m_parent<<"\n";
}


void CGLinearLayout::clearWidgets()
{
    m_data.clear();
}


void CGLinearLayout::layoutWidgets()
{
    //const auto ms=minimumSizeFromWidgets();
    //std::cout<<this<<" CGLayout::layoutWidgets().0 m_parent="<<m_parent<<"\n";
    CGLayout::layoutWidgets();

    if (m_parent) {
        const auto ps=m_parent->size();
        int laysetsum=0;
        int laysum=0;
        for (size_t i=0; i<m_data.size(); i++) {
            if (m_data[i].stretch>0) laysetsum+=m_data[i].stretch;
            else if (m_data[i].stretch<0) laysum+=(-m_data[i].stretch);
        }
        //std::cout<<this<<" CGLayout::layoutWidgets().0 m_parent="<<m_parent<<"  ps="<<ps<<" laysum="<<laysum<<" laysetsum="<<laysetsum<<"\n";
        if (m_direction==cgdHorizontal) {
            int x=0;
            int y=0;
            std::vector<unsigned int> widths;
            const int freeSpace=(ps.width-(m_data.size()-1)*spacing());
            for (size_t i=0; i<m_data.size(); i++) {
                if (m_data[i].stretch>0) {
                    widths.push_back(m_data[i].stretch);
                } else if (m_data[i].stretch<0) {
                    widths.push_back((laysetsum>=freeSpace)?0:((freeSpace-laysetsum)*(-m_data[i].stretch)/laysum));
                } else {
                    widths.push_back(0);
                }
            }

            for (size_t i=0; i<m_data.size(); i++) {
                if (m_data[i].widget) {
                    m_data[i].widget->move(x,y);
                    m_data[i].widget->setWidth(widths[i]);
                    if (i<m_data.size()-1) x+=(widths[i]+spacing());
                    if (m_otherAxisSizeMode==oasmAvailableSpace) {
                        m_data[i].widget->setHeight(ps.height);
                    }
                    //std::cout<<this<<"   CGLayout::layoutWidgets()   H"<<i<<": new_size="<<m_data[i].widget->size()<<" newpos="<<m_data[i].widget->x()<<","<<m_data[i].widget->y()<<" p="<<m_data[i].widget->parent()<<"\n";
                }
            }
        } else {
            int x=0;
            int y=0;
            std::vector<unsigned int> heights;
            const int freeSpace=(ps.height-(m_data.size()-1)*spacing());
            for (size_t i=0; i<m_data.size(); i++) {
                if (m_data[i].stretch>0) {
                    heights.push_back(m_data[i].stretch);
                } else if (m_data[i].stretch<0) {
                    heights.push_back((laysetsum>=freeSpace)?0:((freeSpace-laysetsum)*(-m_data[i].stretch)/laysum));
                } else {
                    heights.push_back(0);
                }
            }
            for (size_t i=0; i<m_data.size(); i++) {
                if (m_data[i].widget) {
                    m_data[i].widget->move(x,y);
                    m_data[i].widget->setHeight(heights[i]);
                    if (i<m_data.size()-1) y+=(heights[i]+spacing());
                    if (m_otherAxisSizeMode==oasmAvailableSpace) {
                        m_data[i].widget->setWidth(ps.width);
                    }
                    //std::cout<<this<<"   CGLayout::layoutWidgets()   V"<<i<<": new_size="<<m_data[i].widget->size()<<" newpos="<<m_data[i].widget->x()<<","<<m_data[i].widget->y()<<" p="<<m_data[i].widget->parent()<<"\n";
                }
            }
        }
    }
    //std::cout<<this<<" CGLayout::layoutWidgets().1 m_parent="<<m_parent<<"\n";
}

cgSize<unsigned int> CGLinearLayout::minimumSizeFromWidgets() const
{
    cgSize<unsigned int> s;
    for (size_t i=0; i<m_data.size(); i++) {
        cgSize<unsigned int> si;
        if (m_data[i].widget) {
            si=m_data[i].widget->minimumSize();
        }
        s.width += si.width;
        s.height += si.height;
        if (m_direction==cgdHorizontal) {
            s.width += spacing();
        } else {
            s.height += spacing();
        }
    }
    return s;
}

cgSize<unsigned int> CGLinearLayout::minimumSize() const
{
    cgSize<unsigned int> s=minimumSizeFromWidgets();
    if (m_direction==cgdHorizontal) {
        s.width += ((m_data.size()-1)*spacing());
    } else {
        s.height += ((m_data.size()-1)*spacing());
    }
    return s;
}

void CGLinearLayout::setOtherAxisSizeMode(CGLinearLayout::OtherAxisSizeMode mode)
{
    m_otherAxisSizeMode=mode;
    layoutWidgets();

}

std::vector<CGWidget *> CGLinearLayout::managedWidgets() const
{
    std::vector<CGWidget *> res;
    for (auto it= m_data.begin(); it!=m_data.end(); ++it) {
        if (it->widget) res.push_back(it->widget);
    }
    return res;
}
