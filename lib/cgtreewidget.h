#ifndef CGTREEWIDGET_H
#define CGTREEWIDGET_H

#include "cgframe.h"
#include <vector>
#include <string>
#include "cgfontprops.h"
#include "cgscrollbar.h"
#include "cgtreebase.h"

/** \brief a widget that displays a tree of items of type CGTreeWidget::TreeItem */
template <class TItemData>
class CGTreeWidget: public CGTreeBase
{
    public:
        struct TreeItem {
            std::vector<TreeItem*> children;
            std::string name;
            TItemData data;
            TreeItem* parent;
            int id;

            inline TreeItem(TreeItem* parent=NULL) {
                this->parent=parent;
                name="";
                id=0;
            }
            inline ~TreeItem() {
                clear();
            }


            inline void clear() {
                for (size_t i=0; i<children.size(); i++) {
                    delete children[i];
                }
                children.clear();
            }
            inline TreeItem* addChild(const std::string & name, int id=-1) {
                CGTreeWidget::TreeItem* it=new CGTreeWidget::TreeItem(this);
                it->name=name;
                it->id=id;
                children.push_back(it);
                return it;
            }
            inline TreeItem* addChild(const std::string & name, const TItemData& data, int id=-1) {
                CGTreeWidget::TreeItem* it=new CGTreeWidget::TreeItem(this);
                it->name=name;
                it->data=data;
                it->id=id;
                children.push_back(it);
                return it;
            }

            inline void deleteChild(int i) {
                if (i>=0 && i<(int64_t)children.size()) {
                    CGTreeWidget::TreeItem * it=child(i);
                    children.erase(children.begin()+i);
                    if (it) delete it;
                }
            }

            inline TreeItem* child(int i) {
                if (i>=0 && i<(int64_t)children.size()) {
                    return children[i];
                }
                return NULL;
            }

            inline TreeItem* lastChild() {
                return child(count()-1);
            }
            inline TreeItem* firstChild() {
                return child(0);
            }

            inline const TreeItem* child(int i) const {
                if (i>=0 && i<(int64_t)children.size()) {
                    return children[i];
                }
                return NULL;
            }

            inline int count() const {
                return children.size();
            }

            inline int indexOf(const TreeItem* it) {
                for (size_t i=0; i<children.size(); i++) {
                    if (children[i]==it) return i;
                }
                return -1;
            }

            inline TreeItem* trueRoot() {
                CGTreeWidget::TreeItem *r=parent;
                while (r && r->parent) {
                    r=r->parent;
                }
                return r;
            }

            inline bool hasChildern() const {
                return count()>0;
            }
            inline int level() const {
                int l=0;
                const CGTreeWidget::TreeItem *r=this;
                while (r && r->parent) {
                    r=r->parent;
                    l++;
                }
                return l;
            }

        };

        inline explicit CGTreeWidget(CGWidget* parent=NULL):
            CGTreeBase(parent)
        {
            m_root=NULL;
        }

        inline explicit CGTreeWidget(int x, int y, int width, int height, CGWidget* parent=NULL):
            CGTreeBase(x,y,width,height,parent)
        {
            m_root=NULL;
        }

        inline virtual ~CGTreeWidget() {}

        inline TreeItem* root() const {
            return m_root;
        }
        inline void setRoot(TreeItem* r) {
            m_root=r;
            if (m_root) {
                if (m_currentItem>=m_root->count()) m_currentItem=m_root->count();
            } else {
                m_currentItem=-1;
            }
            updateState();
        }

        inline TreeItem* currentTreeItemParent() const {
            if (currentTreeItem()) {
                return currentTreeItem()->parent;
            }
            return NULL;
        }

        inline TreeItem* currentTreeItem() const {
            if (m_root) {
                return m_root->child(m_currentItem);
            }
            return NULL;
        }

        inline void setCurrentItem(const TreeItem* it) {
            if (it) {
                m_root=it->parent;
                m_currentItem=m_root->indexOf(it);
            }
            updateState();
        }

        inline virtual void downLevel() {
            if (m_root) {
                CGTreeWidget::TreeItem *it=currentTreeItem();
                if (it && it->hasChildern()) {
                    m_root=it;
                    m_currentItem=0;
                }
            }
            updateState();
        }

        inline virtual void upLevel() {
            if (m_root && m_root->parent) {
                m_root=m_root->parent;
                m_currentItem=0;
            }
            updateState();
        }

        inline virtual void clear() {
            if (!m_root) return;
            CGTreeWidget::TreeItem * r=m_root->trueRoot();
            delete r;
            m_root=NULL;
            m_currentItem=-1;
            updateState();
        }

        inline virtual int count() const {
            if (m_root) {
                return m_root->count();
            } else {
                return 0;
            }
        }

        inline virtual std::string itemName(int i, const std::string& defaultItem=std::string()) const {
            if (!m_root) return defaultItem;
            CGTreeWidget::TreeItem * it=m_root->child(i);
            if (it) return it->name;
            return defaultItem;
        }

        inline virtual TItemData itemData(int i, const TItemData& defaultItem) const {
            if (!m_root) return defaultItem;
            CGTreeWidget::TreeItem * it=m_root->child(i);
            if (it) return it->data;
            return defaultItem;
        }

        inline virtual int itemID(int i, int defaultItem=-1) const {
            if (!m_root) return defaultItem;
            CGTreeWidget::TreeItem * it=m_root->child(i);
            if (it) return it->id;
            return defaultItem;
        }

        inline virtual bool hasChildren(int i) const {
            if (!m_root) return false;
            CGTreeWidget::TreeItem * it=m_root->child(i);
            if (it) return it->hasChildern();
            return false;
        }

        inline virtual int currentLevel() const {
            if (currentTreeItem()) {
                return currentTreeItem()->level();
            }
            return 0;
        }

        inline virtual bool hasParent() const {
            return (m_root && m_root->parent);
        }

        inline virtual std::vector<std::string> parentItemNames(int maxLevel=-1, const std::string& defaultItem=std::string()) const {
            std::vector<std::string> res;
            TreeItem* it=m_root;
            while (it && it->parent) {
                res.push_back(it->parent->name);
                it=it->parent;
            }
            return res;
        }

        inline virtual std::string parentItemName(const std::string& defaultItem=std::string()) const {
            if (m_root && m_root->parent) {
                return m_root->parent->name;
            }
            return defaultItem;
        }


        inline CGTreeWidget::TreeItem * addItem(const std::string & name, const TItemData& data, int id=-1) {
            if (!m_root) {
                m_root=new CGTreeWidget::TreeItem(NULL);
            }
            if (m_root) {
                return m_root->addChild(name, data, id);
            }
            return NULL;
        }

        inline CGTreeWidget::TreeItem * addItem(const std::string & name, int id=-1) {
            if (!m_root) {
                m_root=new CGTreeWidget::TreeItem(NULL);
            }
            if (m_root) {
                return m_root->addChild(name, id);
            }
            return NULL;
        }

        inline CGTreeWidget::TreeItem * item(int i) const {
            if (!m_root) return NULL;
            CGTreeWidget::TreeItem * it=m_root->child(i);
            if (it) return it;
            return NULL;
        }

        inline CGTreeWidget::TreeItem * lastItem() const {
            return item(count()-1);
        }

        inline CGTreeWidget::TreeItem * firstItem() const {
            return item(0);
        }


    protected:


        TreeItem* m_root;
};

#endif // CGTREEWIDGET_H
