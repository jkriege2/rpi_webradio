#ifndef CGWIDGET_H
#define CGWIDGET_H

#include <cairo.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include "cgbasics.h"
#include "cgpalette.h"
#include "cgevents.h"
#include "cgfontprops.h"
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>

class CGLayout; // forward

/** \brief base-class for all widgets in this library */
class CGWidget: public CGFontProps, private boost::noncopyable
{
    public:
        explicit CGWidget(CGWidget* parent=NULL);
        explicit CGWidget(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGWidget();

        /** \brief return the width of the widget */
        inline unsigned int width() const { return m_width; }
        /** \brief return the height of the widget */
        inline unsigned int height() const { return m_height; }
        /** \brief resize the widget */
        virtual void resize(unsigned int width, unsigned int height);
        /** \brief resize the widget */
        inline void resize(cgSize<unsigned int> size) {
            resize(size.width, size.height);
        }
        /** \brief resize the width of the widget */
        inline void setWidth(unsigned int size) {
            resize(size, height());
        }
        /** \brief resize the height of the widget */
        inline void setHeight(unsigned int size) {
            resize(width(), size);
        }

        /** \brief minimum size of the widget */
        inline cgSize<unsigned int> size() const {
            return cgSize<unsigned int>(width(), height());
        }
        /** \brief size, available for child-widgets */
        virtual cgSize<unsigned int> sizeForChildren() const;

        /** \brief the top-left corner x-coordinate of the wqidget */
        inline int x() const { return m_x; }
        /** \brief the top-left corner y-coordinate of the wqidget */
        inline int y() const { return m_y; }
        /** \brief return the border-width */
        virtual inline float border() const { return m_border; }

        /** \brief return the x-position of the widget in absolute screen coordinates */
        inline float absX() const {
            if (m_parent) {
                return m_x+m_parent->absX()+border();
            } else {
                return m_x+border();
            }
        }

        /** \brief return the y-position of the widget in absolute screen coordinates */
        inline float absY() const {
            if (m_parent) {
                return m_y+m_parent->absY()+border();
            } else {
                return m_y+border();
            }
        }

        /** \brief move the top-left of this widget to ( \a x , \a y ) in the coordinate system of the parent widget*/
        virtual void move(int x, int y);

        /** \brief background color of the widget */
        inline CGColor backgroundColor() const {
            return m_backgroundColor;
        }
        /** \brief set the background color */
        void setBackgroundColor(CGColor col);

        /** \brief returns the parent widget */
        inline CGWidget* parent() const { return m_parent; }
        /** \brief set the parent widget of this widget */
        virtual void setParent(CGWidget* p);

        /** \brief paint the widget */
        virtual void paint(cairo_t *c) const;

        /** \brief returns true, if the absolute screen coordinates ( \a x , \a y ) are inside the widget */
        virtual bool isAbsPosInside(int x, int y);
        /** \brief returns true, if the coordinates ( \a x , \a y ), given relative to the parent widget, are inside the widget */
        virtual bool isRelPosInside(int x, int y);

        virtual void setPropsFromPalette(CGPalette* palette);
        void setPropsFromDefaultPalette();

        /** \brief returns \c true, if this widget may receive the input focus */
        inline bool mayReceiveFocus() const {
            return m_mayReceiveFocus;
        }
        /** \brief set, whether thios widget may receive the input focus */
        void setMayReceiveFocus(bool en);

        /** \brief returns \c true, if this widget will process events only if it has the focus */
        inline bool eventsOnlyIfFocused() const {
            return m_eventsOnlyIfFocused;
        }
        /** \brief set, whether thios widget may receive the input focus */
        void setEventsOnlyIfFocused(bool en);

        /** \brief get next child that may receive the focus */
        CGWidget* getNextFocusChild() const;
        /** \brief get first child that may receive the focus */
        CGWidget* getFirstFocusChild() const;
        /** \brief return the layout-object, used for this widget */
        CGLayout* layout() const { return m_layout; }
        /** \brief set the layout-widget used for this widget */
        void setLayout(CGLayout* layout, bool deleteOld=true);
        /** \brief reset the current layout */
        inline void resetLayout(bool deleteOld=true) {
            setLayout(NULL, deleteOld);
        }

        /** \brief set the focus to this widget */
        virtual void setFocus();
        /** \brief give the focus to the next focussable widget */
        virtual void focusNext();
        /** \brief does this widget have the focus */
        virtual bool hasFocus() const;

        /** \brief minimum size of the widget */
        inline cgSize<unsigned int> minimumSize() const {
            return m_minSize;
        }
        /** \brief set the minimum size of the widget */
        void setMinimumSize(cgSize<unsigned int> size);
        /** \brief maximum size of the widget */
        inline cgSize<unsigned int> maximumSize() const {
            return m_maxSize;
        }
        /** \brief set the maximum size of the widget */
        void setMaximumSize(cgSize<unsigned int> size);

        /** \brief use this function to post an event into this object from an external source
         *
         * \note This function is used by CGEventQueue and is seldomly required to be called from other sources!
         */
        void postEvent(CGEvent* e);

        /** \brief signals a resize of the widget */
        boost::signals2::signal<void(unsigned int, unsigned int)> sigResize;

    protected:
        /** \brief process events
         *
         * Overwrite this function in a derived class, if you want to react to events. However, remember to call the events() function
         * in your base-class if you don't want to completely superseed its functionality. If you accepted the event and do not want
         * any other child-widget to receive this event, set its state to accepted after reacting to it!
         */
        virtual void event(CGEvent* e);

        CGWidget* m_parent;
        std::list<CGWidget*> m_children;
        int m_x;
        int m_y;
        unsigned int m_width;
        unsigned int m_height;
        float m_border;
        CGColor m_backgroundColor;
        bool m_mayReceiveFocus;
        bool m_hasFocus;
        bool m_eventsOnlyIfFocused;
        cgSize<unsigned int> m_maxSize;
        cgSize<unsigned int> m_minSize;
        CGLayout* m_layout;


};


#endif // CGWIDGET_H
