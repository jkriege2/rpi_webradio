#ifndef CAIROGUI_FRAME_H
#define CAIROGUI_FRAME_H

#include "cgwidget.h"

class CGFrame: public CGWidget {
	public:
        explicit CGFrame(CGWidget* parent=NULL);
        explicit CGFrame(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGFrame();

        virtual void setPropsFromPalette(CGPalette* palette);

        inline CGColor frameColor() const {
            return m_frameColor;
        }
        void setFrameColor(CGColor col);
        inline float framewidth() const {
            return m_frameWidth;
        }
        void setFrameWidth(float width);

        virtual void paint(cairo_t *c) const;
    protected:
        float m_frameWidth;
        CGColor m_frameColor;
};
  
#endif // CAIROGUI_FRAME_H
