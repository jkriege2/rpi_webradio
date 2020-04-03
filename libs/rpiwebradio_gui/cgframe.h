#ifndef CAIROGUI_FRAME_H
#define CAIROGUI_FRAME_H


#include "cgwidget.h"

/*! \brief a widget witha frame (given color and width) around it
 */
class CGFrame: public CGWidget {
	public:
        explicit CGFrame(CGWidget* parent=NULL);
        explicit CGFrame(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGFrame();

        virtual void setPropsFromPalette(CGPalette* palette) override;

        inline CGColor frameColor() const {
            return m_frameColor;
        }
        void setFrameColor(CGColor col);
        inline float frameWidth() const {
            return m_frameWidth;
        }
        void setFrameWidth(float width);

        inline CGColor focusedFrameColor() const {
            return m_focusedFrameColor;
        }
        void setFocusedFrameColor(CGColor col);
        inline float focusedFrameWidth() const {
            return m_focusedFrameWidth;
        }
        void setFocusedFrameWidth(float width);

        virtual void paint(cairo_t *c)  override;
    protected:
        float m_frameWidth;
        CGColor m_frameColor;
        float m_focusedFrameWidth;
        CGColor m_focusedFrameColor;
};
  
#endif // CAIROGUI_FRAME_H
