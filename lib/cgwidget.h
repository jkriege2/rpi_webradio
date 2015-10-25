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

class CGWidget: public CGFontProps
{
    public:
        explicit CGWidget(CGWidget* parent=NULL);
        explicit CGWidget(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGWidget();

        inline int width() const { return m_width; }
        inline int height() const { return m_height; }
        virtual void resize(int width, int height);

        inline int x() const { return m_x; }
        inline int y() const { return m_y; }
        virtual inline float border() const { return m_border; }

        inline float absX() const {
            if (m_parent) {
                return m_x+m_parent->absX()+border();
            } else {
                return m_x+border();
            }
        }

        inline float absY() const {
            if (m_parent) {
                return m_y+m_parent->absY()+border();
            } else {
                return m_y+border();
            }
        }

        virtual void move(int x, int y);

        inline CGColor backgroundColor() const {
            return m_backgroundColor;
        }
        void setBackgroundColor(CGColor col);

        inline CGWidget* parent() const { return m_parent; }
        virtual void setParent(CGWidget* p);

        virtual void paint(cairo_t *c) const;

        virtual bool isAbsPosInside(int x, int y);
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

        virtual void setFocus();
        virtual void focusNext();
        virtual bool hasFocus() const;

        /** \brief use this function to post an event into this object from an external source
         *
         * \note This function is used by CGEventQueue and is seldomly required to be called from other sources!
         */
        void postEvent(CGEvent* e);

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
        int m_width;
        int m_height;
        float m_border;
        CGColor m_backgroundColor;
        bool m_mayReceiveFocus;
        bool m_hasFocus;
        bool m_eventsOnlyIfFocused;
};


#endif // CGWIDGET_H
