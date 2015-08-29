#include "cglistwidget.h"


CGListWidget::CGListWidget(CGWidget *parent):
    CGFrame(parent)
{
    m_selectedColor=CGColor::ccGray25;
    m_currentItem=0;
    m_items.clear();
    m_startVisible=0;
}

CGListWidget::CGListWidget(int x, int y, int width, int height, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    m_selectedColor=CGColor::ccGray25;
    m_currentItem=0;
    m_items.clear();
    m_startVisible=0;
}

CGListWidget::~CGListWidget()
{

}

void CGListWidget::paint(cairo_t *c) const
{

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

std::string CGListWidget::item(int i, const std::string &defaultItem) const
{
    if (i<0 || i>=m_items.size()) return defaultItem;
    return m_items[i];
}
