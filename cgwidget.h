#ifndef CGWIDGET_H
#define CGWIDGET_H

#include <cairo.h>
#include <stdlib.h>
#include <string.h>
#include <list>

struct CGColor {
    inline CGColor() {
        r=g=b=255;
        a=255;
    }
    inline CGColor(unsigned char r, unsigned char g, unsigned char b) {
        this->r=r;
        this->g=g;
        this->b=b;
        this->a=255;
    }
    inline CGColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->r=r;
        this->g=g;
        this->b=b;
        this->a=a;
    }
    inline CGColor(unsigned char gray) {
        this->r=gray;
        this->g=gray;
        this->b=gray;
        this->a=255;
    }

    inline float rf() const {
        return float(r)/255.0;
    }
    inline float gf() const {
        return float(g)/255.0;
    }
    inline float bf() const {
        return float(b)/255.0;
    }
    inline float af() const {
        return float(a)/255.0;
    }


    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    inline static CGColor transparent() {
        return CGColor(255,255,255,255);
    }
    inline static CGColor black() {
        return CGColor(0,0,0,255);
    }
    inline static CGColor white() {
        return CGColor(255,255,255,255);
    }

};

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
