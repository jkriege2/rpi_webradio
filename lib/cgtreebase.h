#ifndef CGTreeBase_H
#define CGTreeBase_H

#include "cgframe.h"
#include <vector>
#include <string>
#include "cgfontprops.h"
#include "cgscrollbar.h"

/** \brief a base-class for widgets that displays a tree */
class CGTreeBase: public CGFrame, public CGScrollBarMixin
{
    public:

        explicit CGTreeBase(CGWidget* parent=NULL);
        explicit CGTreeBase(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGTreeBase();
        virtual void paint(cairo_t *c)  override;


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

        virtual void downLevel()=0;
        virtual void upLevel()=0;
        virtual int currentLevel() const=0;
        virtual void clear();
        virtual int count() const=0;
        virtual std::string itemName(int i, const std::string& defaultItem=std::string()) const=0;
        virtual bool hasChildren(int i) const=0;
        virtual bool hasParent() const=0;
        virtual std::vector<std::string> parentItemNames(int maxLevel=-1, const std::string& defaultItem=std::string()) const=0;
        virtual std::string parentItemName(const std::string& defaultItem=std::string()) const;


        void setPropsFromPalette(CGPalette *palette);
    protected:
        virtual void updateState();
        virtual float itemHeight() const;
        void drawIndicator(cairo_t* c, float x, float y, float lh, CGColor col) const ;


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

#endif // CGTreeBase_H
