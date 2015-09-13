#ifndef CGTreeWidget_H
#define CGTREEWIDGET_H

#include "cgframe.h"
#include <vector>
#include <string>
#include "cgfontprops.h"
#include "cgscrollbar.h"

class CGTreeWidget: public CGFrame, public CGFontProps, public CGScrollBarMixin
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

        explicit CGTreeWidget(CGWidget* parent=NULL);
        explicit CGTreeWidget(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGTreeWidget();
        virtual void paint(cairo_t *c) const;

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

        inline int currentItem() const {
            return m_currentItem;
        }
        inline void setCurrentItem(int v) {
            m_currentItem=v;
            updateState();
        }
        inline void nextItem(int inc=1) {
            m_currentItem+=inc;
            updateState();
        }
        inline void prevItem(int inc=1) {
            m_currentItem-=inc;
            updateState();
        }
        inline void scrollDown(int inc=1) {
            m_startVisible+=inc;
            updateState();
        }
        inline void scrollUp(int inc=1) {
            m_startVisible-=inc;
            updateState();
        }

        void downLevel();
        void upLevel();

        inline int scrollbarWidth() const {
            return m_scrollbarWidth;
        }
        inline void setScrollbarWidth(int v) {
            m_scrollbarWidth=v;
        }

        inline int subindicatorWidth() const {
            return m_subindicatorWidth;
        }
        inline void setSubindicatorWidth(int v) {
            m_subindicatorWidth=v;
        }

        inline int treeIndent() const {
            return m_treeIndent;
        }
        inline void setTreeIndent(int v) {
            m_treeIndent=v;
        }

        inline CGColor selectedColor() const {
            return m_selectedColor;
        }
        inline void setSelectedColor(CGColor v) {
            m_selectedColor=v;
        }


        inline CGColor selectedTextColor() const {
            return m_selectedTextColor;
        }
        inline void setSelectedTextColor(CGColor v) {
            m_selectedTextColor=v;
        }

        inline CGColor scrollbarColor() const {
            return m_scrollbarColor;
        }
        inline void SetScrollbarColor(CGColor v) {
            m_scrollbarColor=v;
        }

        inline CGColor scrollbarBackgroundColor() const {
            return m_scrollbarBackgroundColor;
        }
        inline void setScrollbarBackgroundColor(CGColor v) {
            m_scrollbarBackgroundColor=v;
        }

        inline bool showScrollbar() const {
            return m_showScrollbar;
        }
        inline void setShowScrollbar(bool v) {
            m_showScrollbar=v;
        }

        inline bool showUpperLevels() const {
            return m_showUpperLevels;
        }
        inline void setShowUpperLevels(bool v) {
            m_showUpperLevels=v;
        }

        CGTreeWidget::TreeItem * addItem(const std::string & name, const std::string& data=std::string(), int id=-1);
        void clear();
        int count() const;
        std::string itemName(int i, const std::string& defaultItem=std::string()) const;
        std::string itemData(int i, const std::string& defaultItem=std::string()) const;
        int itemID(int i, int defaultItem=-1) const;
        bool hasChildren(int i) const;
        CGTreeWidget::TreeItem * item(int i) const;
        inline CGTreeWidget::TreeItem * lastItem() const {
            return item(count()-1);
        }
        inline CGTreeWidget::TreeItem * firstItem() const {
            return item(0);
        }


        void setPropsFromPalette(CGPalette *palette);
    protected:
        void updateState();
        float itemHeight() const;
        int currentLevel() const;
        void drawIndicator(cairo_t* c, float x, float y, float lh, CGColor col) const ;


        TreeItem* m_root;
        int m_currentItem;
        int m_startVisible;
        CGColor m_selectedColor;
        CGColor m_selectedTextColor;

        CGColor m_scrollbarColor;
        CGColor m_scrollbarBackgroundColor;
        int m_scrollbarWidth;
        bool m_showScrollbar;
        bool m_showUpperLevels;

        int m_subindicatorWidth;
        int m_treeIndent;
};

#endif // CGTreeWidget_H
