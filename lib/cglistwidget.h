#ifndef CGLISTWIDGET_H
#define CGLISTWIDGET_H

#include "cgframe.h"
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include "cgfontprops.h"
#include "cgscrollbar.h"

/** \biref a widget that displays a list of items */
template<class TItemData>
class CGListWidget: public CGFrame, public CGScrollBarMixin
{
    public:
        inline explicit CGListWidget(CGWidget* parent=NULL):
            CGFrame(parent)
        {
            m_textColor=CGColor::ccGray50;
            m_selectedColor=CGColor::ccGray25;
            m_selectedTextColor=CGColor::ccWhite;
            m_showScrollbar=true;
            m_currentItem=0;
            m_items.clear();
            m_startVisible=0;
            m_scrollbarWidth=10;
            setPropsFromDefaultPalette();
        }

        inline explicit CGListWidget(int x, int y, int width, int height, CGWidget* parent=NULL):
            CGFrame(x,y,width,height,parent)
        {
            m_textColor=CGColor::ccGray50;
            m_selectedColor=CGColor::ccGray25;
            m_selectedTextColor=CGColor::ccWhite;
            m_showScrollbar=true;
            m_currentItem=0;
            m_items.clear();
            m_startVisible=0;
            m_scrollbarWidth=10;
            setPropsFromDefaultPalette();
        }
        inline virtual ~CGListWidget() {}
        inline virtual void paint(cairo_t *c)  override{
            CGFrame::paint(c);

            float w=m_width-2.0*m_frameWidth-2;
            if (m_showScrollbar) {
                w=w-m_scrollbarWidth;
            }

            cairo_save(c);

                cairo_rectangle(c, m_frameWidth, m_frameWidth, w, m_height-2.0*m_frameWidth);
                cairo_clip (c);
                int i=m_startVisible;
                float x=m_border+1.0;
                float y=m_border+2.0;
                float lh=itemHeight();
                int ifirst=-1;
                int ilast=-1;
                //std::cout<<"----------------------- m_startVisible="<<m_startVisible<<"\n";
                while (y<m_height && i<(int)m_items.size()) {
                    if (i>=0 && i<(int)m_items.size()) {
                        //std::cout<<"CGListWidget: i="<<i<<": x="<<x<<", y="<<y<<": "<<m_items[i]<<"   lh="<<lh<<"\n";
                        CGColor col=m_textColor;
                        if (m_currentItem==i) {
                            cairo_rectangle(c, x, y, w, lh);
                            m_selectedColor.cairo_set_source(c);
                            cairo_fill(c);

                            col=m_selectedTextColor;
                            if (ifirst<0) ifirst=i;
                            if (y+lh<m_height) ilast=i;
                        }
                        drawAlignedColoredText(c, x, y+2, w, lh, m_items[i].name, col, cgalLeft, cgalTop);
                        //std::cout<<"paint(). m_currentItem="<<m_currentItem<<" m_startVisible="<<m_startVisible<<" size="<<m_items.size()<<" i="<<i<<" p="<<x<<","<<y+2<<" s="<<w<<"x"<<lh<<": "<<m_items[i].name<<" color="<<col<<"\n";
                    }
                    y=y+lh;
                    i++;
                }

                if (ifirst<0) ifirst=0;
                if (ilast<0) ilast=0;
                if (ilast==ifirst) ilast=ifirst+1;
            //std::cout<<"-----------------------\n";
            cairo_restore(c);
            if (m_showScrollbar) {
                paintScrollbar(c, w+1,m_frameWidth+2,m_scrollbarWidth,m_height-2.0*m_frameWidth-2, 0, count(), ifirst, ilast-ifirst);
            }
        }

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
        inline void nextItemRoundabout(int inc=1) {
            m_currentItem=(m_currentItem+inc);
            if (m_currentItem<0) m_currentItem=count()-1;
            if (m_currentItem>=count()) m_currentItem=0;
            if (count()<=0) m_currentItem=-1;
            updateState();
        }
        inline void prevItemRoundabout(int inc=1) {
            m_currentItem=(m_currentItem-inc);
            if (m_currentItem<0) m_currentItem=count()-1;
            if (m_currentItem>=count()) m_currentItem=0;
            if (count()<=0) m_currentItem=-1;
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

        inline int scrollbarWidth() const {
            return m_scrollbarWidth;
        }
        inline void setScrollbarWidth(int v) {
            m_scrollbarWidth=v;
        }

        inline bool showScrollbar() const {
            return m_showScrollbar;
        }
        inline void setShowScrollbar(bool v) {
            m_showScrollbar=v;
        }

        inline void addItem(const std::string& item){
            Item it;
            it.name=item;
            m_items.push_back(it);
        }

        inline void addItem(const std::string& item, const TItemData& data){
            Item it;
            it.name=item;
            it.data=data;
            m_items.push_back(it);
        }

        inline void addItems(const std::vector<std::string>& items){
            for (size_t i=0; i<items.size(); i++) {
                addItem(items[i]);
            }
        }
        inline void addItems(const std::vector<std::string>& items, const std::vector<TItemData>& itemdatas){
            for (size_t i=0; i<items.size(); i++) {
                addItem(items[i], itemdatas[i]);
            }
        }
        inline void clear(){
            m_items.clear();
        }

        inline int count() const{
            return m_items.size();
        }

        inline std::string item(int i, const std::string& defaultItem=std::string()) const{
            if (i<0 || i>=(int)m_items.size()) return defaultItem;
            return m_items[i].name;
        }
        inline TItemData itemData(int i, const TItemData& defaultItem) const{
            if (i<0 || i>=(int)m_items.size()) return defaultItem;
            return m_items[i].data;
        }
        inline TItemData itemData(int i) const{
            TItemData dat;
            return itemData(i, dat);
        }

        inline void setItem(int i, const std::string& item){
            if (i>=0 || i<(int)m_items.size()) {
                m_items[i].name=item;
            }
        }
        inline void setItem(int i, const std::string& item, const TItemData& data){
            if (i>=0 || i<(int)m_items.size()) {
                m_items[i].name=item;
                m_items[i].data=data;
            }
        }
        inline void setItemData(int i, const TItemData& data){
            if (i>=0 || i<(int)m_items.size()) {
                m_items[i].data=data;
            }
        }
        inline void removeItem(int i){
            if (i>=0 || i<(int)m_items.size()) {
                m_items.erase(m_items.begin()+i);
            }
        }

        inline void setPropsFromPalette(CGPalette *palette) override{
            CGFrame::setPropsFromPalette(palette);
            if (palette) {
                setScrollbarPropsFromPalette(palette);
                setSelectedColor(palette->color(CGPalette::crSelection));
                setSelectedTextColor(palette->color(CGPalette::crSelectionIconOrText));
            }
        }
        inline void sort(bool caseInsensitive=false) {
            if (caseInsensitive){
                std::sort(m_items.begin(), m_items.end(), []( const Item& s1, const Item& s2) { return boost::algorithm::to_lower_copy(s1.name)<boost::algorithm::to_lower_copy(s2.name); } );
            } else {
                std::sort(m_items.begin(), m_items.end(), []( const Item& s1, const Item& s2) { return s1.name<s2.name; } );
            }
        }

    protected:
        inline void updateState(){
            if (m_startVisible>=(int64_t)m_items.size()) m_startVisible=m_items.size()-1;
            if (m_currentItem>=(int64_t)m_items.size()) m_currentItem=m_items.size()-1;
            if (m_currentItem<=0) m_currentItem=0;
            if (m_items.size()<=0) m_currentItem=0;
            if (m_startVisible<=0) m_startVisible=0;
            if (m_items.size()<=0) m_startVisible=0;

            if (m_currentItem>=0) {
                int i=m_startVisible;
                float lh=itemHeight();
                float y=m_border+2.0;
                int ifirst=-1;
                int ilast=-1;
                while (y<m_height && i<(int)m_items.size()) {
                    if (i>=0 && i<(int)m_items.size()) {
                        if (ifirst<0) ifirst=i;
                        if (y+lh<m_height) ilast=i;
                    }
                    y=y+lh;
                    i++;
                }

                if (ifirst<0) ifirst=0;
                if (ilast<0) ilast=0;
                if (ilast==ifirst) ilast=ifirst+1;

                if (m_currentItem<ifirst) {
                    m_startVisible=m_currentItem;
                } else if (m_currentItem>ilast) {
                    m_startVisible=m_currentItem-(ilast-ifirst);
                }
                if (m_startVisible<0) m_startVisible=0;
            }
            //std::cout<<"updateState(). m_currentItem="<<m_currentItem<<" m_startVisible="<<m_startVisible<<" size="<<m_items.size()<<"\n";
        }
        inline float itemHeight() const{
            return m_fontSize*1.3;
        }

        struct Item {
            std::string name;
            TItemData data;
        };

        std::vector<Item> m_items;
        int m_currentItem;
        int m_startVisible;
        CGColor m_selectedColor;
        CGColor m_selectedTextColor;
        bool m_showScrollbar;
        int m_scrollbarWidth;

};

typedef CGListWidget<char> CGSimpleListWidget;
#endif // CGLISTWIDGET_H
