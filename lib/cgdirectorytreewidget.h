#ifndef CGDirectoryTreeWidget_H
#define CGDirectoryTreeWidget_H

#include "cgframe.h"
#include <vector>
#include <string>
#include "cgfontprops.h"
#include "cgscrollbar.h"
#include "cgtreebase.h"

/** \brief a widget that displays a tree of items of type CGDirectoryTree::TreeProvider */
class CGDirectoryTreeWidget: public CGTreeBase
{
    public:
        struct TreeItem {
            TreeItem(TreeItem* parent=NULL);
            ~TreeItem();
            std::vector<TreeItem*> children;
            std::string name;
            std::string data;
            TreeItem* parent;
            int id;
            void clear();
            TreeItem* addChild(const std::string & name, const std::string& data=std::string(), int id=-1);
            void deleteChild(int i);
            TreeItem* child(int i);
            inline TreeItem* lastChild() {
                return child(count()-1);
            }
            inline TreeItem* firstChild() {
                return child(0);
            }

            const TreeItem* child(int i) const;
            int count() const;
            int indexOf(const TreeItem* it);
            TreeItem* trueRoot();
            inline bool hasChildern() const {
                return count()>0;
            }
            int level() const;
        };

        explicit CGDirectoryTreeWidget(CGWidget* parent=NULL);
        explicit CGDirectoryTreeWidget(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGDirectoryTreeWidget();

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

        void setCurrentItem(const TreeItem* it);

        virtual void downLevel();
        virtual void upLevel();
        virtual void clear();
        virtual int count() const;
        virtual std::string itemName(int i, const std::string& defaultItem=std::string()) const;
        virtual std::string itemData(int i, const std::string& defaultItem=std::string()) const;
        virtual int itemID(int i, int defaultItem=-1) const;
        virtual bool hasChildren(int i) const;
        virtual int currentLevel() const;


        TreeItem * addItem(const std::string & name, const std::string& data=std::string(), int id=-1);
        TreeItem * item(int i) const;
        inline TreeItem * lastItem() const {
            return item(count()-1);
        }
        inline TreeItem * firstItem() const {
            return item(0);
        }


    protected:


        TreeItem* m_root;
};


#endif // CGDirectoryTreeWidget_H
