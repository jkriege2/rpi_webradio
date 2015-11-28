#ifndef CGTABMIXIN_H
#define CGTABMIXIN_H

#include <string>
#include "cgbasics.h"
#include "cgfontprops.h"

/** \brief Mixin, which adds a tab-bar to a widget */
class CGTabMixin
{
    public:
        enum TabPosition {
            tpTop,
            tpBottom
        };

        CGTabMixin(TabPosition tp=tpTop);
        ~CGTabMixin();

        virtual std::string tabName(int idx) const=0;
        virtual int tabCount() const=0;
        virtual bool tabIsActive(int idx) const=0;
        virtual int tabGetActiveTab() const;

        /** \brief paint the tab-bar at the top or bottom of the area in the area (x,y) -> (x+m_width,y+m_height).
         *
         * The tab-bar always has full width and the height tabHeight().
         */
        virtual void paintTabBar(cairo_t *c, int m_width, int m_height, const CGFontProps* fp, cgRect<int> *remainingRect=NULL) const;
        /** \brief paint the tab-bar at the top or bottom of the area in the area (x,y) -> (x+m_width,y+m_height).
         *
         * The tab-bar always has full width and the height tabHeight().
         */
        virtual cgRect<int> getRemainingRect(int m_width, int m_height) const;

        virtual void setTabPropsFromPalette(CGPalette *palette);

        inline int tabTextSpace() const {
            return m_tabTextSpace;
        }
        inline void setTabTextSpace(int v) {
            m_tabTextSpace=v;
        }

        inline TabPosition tabPosition() const {
            return m_tabPosition;
        }
        inline void setTabPosition(TabPosition v) {
            m_tabPosition=v;
        }

        inline int tabHeight() const {
            return m_tabheight;
        }
        inline void setTabHeight(int v) {
            m_tabheight=v;
        }

        inline CGColor tabFrameColor() const {
            return m_tabFrameColor;
        }
        void setTabFrameColor(CGColor col);
        inline float tabFrameWidth() const {
            return m_tabFrameWidth;
        }
        void setTabFrameWidth(float width);

        inline CGColor activeTabFrameColor() const {
            return m_activeTabFrameColor;
        }
        void setActiveTabFrameColor(CGColor col);
        inline float activeTabFrameWidth() const {
            return m_activeTabFrameWidth;
        }
        void setActiveTabFrameWidth(float width);

        inline CGColor activeTabColor() const {
            return m_activeTabColor;
        }
        void setActiveTabColor(CGColor col);
        inline CGColor tabColor() const {
            return m_tabColor;
        }
        void setTabColor(CGColor col);

        inline CGColor activeTabTextColor() const {
            return m_activeTabTextColor;
        }
        void setActiveTabTextColor(CGColor col);
        inline CGColor tabTextColor() const {
            return m_tabTextColor;
        }
        void setTabTextColor(CGColor col);

    protected:
        int m_tabheight;
        int m_tabTextSpace;

        float m_tabFrameWidth;
        CGColor m_tabFrameColor;
        float m_activeTabFrameWidth;
        CGColor m_activeTabFrameColor;
        CGColor m_tabColor;
        CGColor m_activeTabColor;
        CGColor m_activeTabTextColor;
        CGColor m_tabTextColor;
        TabPosition m_tabPosition;

};

#endif // CGTABMIXIN_H
