#ifndef CGSCREEN_H
#define CGSCREEN_H

#include "cgwidget.h"
#include "framebuffer_cairo_tools.h"

class CGScreen : public CGWidget
{
    public:
        explicit CGScreen(CGWidget* parent=NULL);
        explicit CGScreen(const fbcairo_context* context, CGWidget* parent=NULL);
        explicit CGScreen(int width, int height, CGWidget* parent=NULL);
        virtual ~CGScreen();

        virtual void move(int x, int y);

        virtual void paint(cairo_t *c) const;

};

#endif // CGSCREEN_H
