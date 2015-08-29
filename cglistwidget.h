#ifndef CGLISTWIDGET_H
#define CGLISTWIDGET_H

#include "cgframe.h"
#include <vector>
#include <string>

class CGListWidget: public CGFrame
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
        }
        inline void nextItem() {
            m_currentItem++;
            if (m_currentItem>=m_items.size()) m_currentItem=m_items.size()-1;
        }
        inline void prevItem() {
            m_currentItem--;
            if (m_currentItem<=0) m_currentItem=0;
            if (m_items.size()<=0) m_currentItem=0;
        }
        inline void scrollDown() {
            m_startVisible++;
            if (m_startVisible>=m_items.size()) m_startVisible=m_items.size()-1;
        }
        inline void scrollUp() {
            m_startVisible--;
            if (m_startVisible<=0) m_startVisible=0;
            if (m_items.size()<=0) m_startVisible=0;
        }


        inline CGColor selectedColor() const {
            return m_selectedColor;
        }
        inline void setSelectedColor(CGColor v) {
            m_selectedColor=v;
        }

        void addItem(const std::string& item);
        void addItems(const std::vector<std::string>& items);
        void clear();
        std::string item(int i, const std::string& defaultItem=std::string()) const;

    protected:
        std::vector<std::string> m_items;
        int m_currentItem;
        int m_startVisible;
        CGColor m_selectedColor;
};

#endif // CGLISTWIDGET_H
