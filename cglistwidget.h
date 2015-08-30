#ifndef CGLISTWIDGET_H
#define CGLISTWIDGET_H

#include "cgframe.h"
#include <vector>
#include <string>
#include "cgfontprops.h"

class CGListWidget: public CGFrame, public CGFontProps
{
    public:
        explicit CGListWidget(CGWidget* parent=NULL);
        explicit CGListWidget(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGListWidget();
        virtual void paint(cairo_t *c) const;

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

        void addItem(const std::string& item);
        void addItems(const std::vector<std::string>& items);
        void clear();
        size_t count() const;
        std::string item(int i, const std::string& defaultItem=std::string()) const;


    protected:
        void updateState();
        float itemHeight() const;
        std::vector<std::string> m_items;
        int m_currentItem;
        int m_startVisible;
        CGColor m_selectedColor;
        CGColor m_selectedTextColor;
        CGColor m_scrollbarColor;
        CGColor m_scrollbarBackgroundColor;
        int m_scrollbarWidth;
        bool m_showScrollbar;
};

#endif // CGLISTWIDGET_H
