#ifndef CGWIDGET_H
#define CGWIDGET_H

#include <cairo.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include "cgbasics.h"
#include "cgpalette.h"
#include "cgevents.h"

class CGWidget
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

        virtual void event(CGEvent* e);

        virtual bool isAbsPosInside(int x, int y);
        virtual bool isRelPosInside(int x, int y);

        virtual void setPropsFromPalette(CGPalette* palette);
        void setPropsFromDefaultPalette();
    protected:
        CGWidget* m_parent;
        std::list<CGWidget*> m_children;
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        float m_border;
        CGColor m_backgroundColor;
};


#endif // CGWIDGET_H
