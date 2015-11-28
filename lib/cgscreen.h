#ifndef CGSCREEN_H
#define CGSCREEN_H

#include "cgwidget.h"
#include "cgfontprops.h"

class fbcairo_context; // forward

/** \biref represents an (exclusively displayed) screen */
class CGScreen : public CGWidget, public CGFontPropsWithAlignment
{
    public:
        explicit CGScreen(CGWidget* parent=NULL);
        explicit CGScreen(const fbcairo_context* context, CGWidget* parent=NULL);
        explicit CGScreen(int width, int height, CGWidget* parent=NULL);
        virtual ~CGScreen();

        virtual void move(int x, int y);

        void setTitle(const std::string& text) {
            m_title=text;
        }
        inline std::string title() const {
            return m_title;
        }

        inline void setTitleBackgroundColor(CGColor v) {
            m_titleBackground=v;
        }
        inline CGColor titleBackground() const {
            return m_titleBackground;
        }

        virtual void paint(cairo_t *c) const;
        void setPropsFromPalette(CGPalette *palette);
    protected:
        std::string m_title;
        CGColor m_titleBackground;
};

#endif // CGSCREEN_H
