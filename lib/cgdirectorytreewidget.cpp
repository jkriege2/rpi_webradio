#include "cgdirectorytreewidget.h"


CGDirectoryTreeWidget::CGDirectoryTreeWidget(CGWidget *parent):
    CGTreeBase(parent)
{
    m_provider=NULL;
    m_ownsProvider=false;
}

CGDirectoryTreeWidget::CGDirectoryTreeWidget(int x, int y, int width, int height, CGWidget *parent):
    CGTreeBase(x,y,width,height,parent)
{
    m_provider=NULL;
    m_ownsProvider=false;
}

CGDirectoryTreeWidget::~CGDirectoryTreeWidget()
{
    clear();
}

void CGDirectoryTreeWidget::setProvider(CGDirectoryTreeWidget::TreeProvider *r, bool owns)
{
    clear();
    m_provider=r;
    m_ownsProvider=owns;
    if (m_provider) {
        m_currentItem=0;
    } else {
        m_currentItem=-1;
    }
    updateState();

}


void CGDirectoryTreeWidget::downLevel()
{
    if (m_provider) {
        if (m_provider->downLevel(m_currentItem))  m_currentItem=0;
    }
    updateState();
}


void CGDirectoryTreeWidget::upLevel()
{
    if (m_provider) {
        if (m_provider->upLevel())  m_currentItem=0;
    }
    updateState();
}


void CGDirectoryTreeWidget::clear()
{
    if (m_ownsProvider && m_provider) {
        TreeProvider* tmp=m_provider;
        m_provider=NULL;
        delete tmp;
    }
}

int CGDirectoryTreeWidget::count() const
{
    if (m_provider) {
        return m_provider->count();
    } else {
        return 0;
    }
}

std::string CGDirectoryTreeWidget::itemName(int i, const std::string &defaultItem) const
{
    if (!m_provider) return defaultItem;
    return m_provider->itemName(i, defaultItem);
}


bool CGDirectoryTreeWidget::hasChildren(int i) const
{
    if (!m_provider) return false;
    return m_provider->hasChildren(i);
}


int CGDirectoryTreeWidget::currentLevel() const
{
    if (m_provider) {
        return m_provider->level();
    }
    return 0;
}

bool CGDirectoryTreeWidget::hasParent() const
{
    if (!m_provider) return false;
    return m_provider->hasParent();
}

std::vector<std::string> CGDirectoryTreeWidget::parentItemNames(int maxLevel, const std::string &defaultItem) const
{
    if (m_provider) {
        return m_provider->parentNames(maxLevel, defaultItem);
    }
    return std::vector<std::string>();
}





std::string CGDirectoryTreeWidget::TreeProvider::parentName(const std::string &defaultItem) const
{
    std::vector<std::string> pars=parentNames(-1, defaultItem);
    if (pars.size()>0) return pars[0];
    return defaultItem;
}
