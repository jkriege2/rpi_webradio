#include "cgdirectorytreewidget.h"


CGDirectoryTreeWidget::CGDirectoryTreeWidget(CGWidget *parent):
    CGTreeBase(parent)
{
    m_root=NULL;
}

CGDirectoryTreeWidget::CGDirectoryTreeWidget(int x, int y, int width, int height, CGWidget *parent):
    CGTreeBase(x,y,width,height,parent)
{
    m_root=NULL;
}

CGDirectoryTreeWidget::~CGDirectoryTreeWidget()
{
}


void CGDirectoryTreeWidget::setCurrentItem(const CGDirectoryTreeWidget::TreeItem *it)
{
    if (it) {
        m_root=it->parent;
        m_currentItem=m_root->indexOf(it);
    }
    updateState();
}

void CGDirectoryTreeWidget::downLevel()
{
    if (m_root) {
        CGDirectoryTreeWidget::TreeItem *it=currentTreeItem();
        if (it && it->hasChildern()) {
            m_root=it;
            m_currentItem=0;
        }
    }
    updateState();
}


void CGDirectoryTreeWidget::upLevel()
{
    if (m_root && m_root->parent) {
        m_root=m_root->parent;
        m_currentItem=0;
    }
    updateState();
}

CGDirectoryTreeWidget::TreeItem *CGDirectoryTreeWidget::addItem(const std::string &name, const std::string &data, int id)
{
    if (!m_root) {
        m_root=new CGDirectoryTreeWidget::TreeItem(NULL);
    }
    if (m_root) {
        return m_root->addChild(name, data, id);
    }
    return NULL;
}


void CGDirectoryTreeWidget::clear()
{
    if (!m_root) return;
    CGDirectoryTreeWidget::TreeItem * r=m_root->trueRoot();
    delete r;
    m_root=NULL;
    m_currentItem=-1;
    updateState();
}

int CGDirectoryTreeWidget::count() const
{
    if (m_root) {
        return m_root->count();
    } else {
        return 0;
    }
}

std::string CGDirectoryTreeWidget::itemName(int i, const std::string &defaultItem) const
{
    if (!m_root) return defaultItem;
    CGDirectoryTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it->name;
    return defaultItem;
}

std::string CGDirectoryTreeWidget::itemData(int i, const std::string &defaultItem) const
{
    if (!m_root) return defaultItem;
    CGDirectoryTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it->data;
    return defaultItem;
}

int CGDirectoryTreeWidget::itemID(int i, int defaultItem) const
{
    if (!m_root) return defaultItem;
    CGDirectoryTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it->id;
    return defaultItem;
}

bool CGDirectoryTreeWidget::hasChildren(int i) const
{
    if (!m_root) return false;
    CGDirectoryTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it->hasChildern();
    return false;
}

CGDirectoryTreeWidget::TreeItem *CGDirectoryTreeWidget::item(int i) const
{
    if (!m_root) return NULL;
    CGDirectoryTreeWidget::TreeItem * it=m_root->child(i);
    if (it) return it;
    return NULL;
}


int CGDirectoryTreeWidget::currentLevel() const
{
    if (currentTreeItem()) {
        return currentTreeItem()->level();
    }
    return 0;
}



CGDirectoryTreeWidget::TreeItem::TreeItem(TreeItem *parent)
{
    this->parent=parent;
    name="";
    data="";
    id=0;
}

CGDirectoryTreeWidget::TreeItem::~TreeItem()
{
    clear();
}

void CGDirectoryTreeWidget::TreeItem::clear()
{
    for (size_t i=0; i<children.size(); i++) {
        delete children[i];
    }
    children.clear();
}

CGDirectoryTreeWidget::TreeItem *CGDirectoryTreeWidget::TreeItem::addChild(const std::string &name, const std::string &data, int id)
{
    CGDirectoryTreeWidget::TreeItem* it=new CGDirectoryTreeWidget::TreeItem(this);
    it->name=name;
    it->data=data;
    it->id=id;
    children.push_back(it);
    return it;
}

void CGDirectoryTreeWidget::TreeItem::deleteChild(int i)
{
    if (i>=0 && i<(int64_t)children.size()) {
        CGDirectoryTreeWidget::TreeItem * it=child(i);
        children.erase(children.begin()+i);
        if (it) delete it;
    }
}

CGDirectoryTreeWidget::TreeItem *CGDirectoryTreeWidget::TreeItem::child(int i)
{
    if (i>=0 && i<(int64_t)children.size()) {
        return children[i];
    }
    return NULL;
}

const CGDirectoryTreeWidget::TreeItem *CGDirectoryTreeWidget::TreeItem::child(int i) const
{
    if (i>=0 && i<(int64_t)children.size()) {
        return children[i];
    }
    return NULL;
}

int CGDirectoryTreeWidget::TreeItem::count() const
{
    return children.size();
}

int CGDirectoryTreeWidget::TreeItem::indexOf(const CGDirectoryTreeWidget::TreeItem *it)
{
    for (size_t i=0; i<children.size(); i++) {
        if (children[i]==it) return i;
    }
    return -1;
}

CGDirectoryTreeWidget::TreeItem *CGDirectoryTreeWidget::TreeItem::trueRoot()
{
    CGDirectoryTreeWidget::TreeItem *r=parent;
    while (r && r->parent) {
        r=r->parent;
    }
    return r;
}

int CGDirectoryTreeWidget::TreeItem::level() const
{
    int l=0;
    const CGDirectoryTreeWidget::TreeItem *r=this;
    while (r && r->parent) {
        r=r->parent;
        l++;
    }
    return l;
}
