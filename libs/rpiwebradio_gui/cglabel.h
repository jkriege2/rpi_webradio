#ifndef CGLABEL_H
#define CGLABEL_H

#include "cgframe.h"
#include <string>
#include <chrono>
#include "cgfontprops.h"

/** \brief a widget that displays text */
class CGLabel: public CGFrame, public CGFontPropsWithAlignment
{
    public:


        explicit CGLabel(CGWidget* parent=NULL);
        explicit CGLabel(int x, int y, int width, int height, const std::string& text, CGWidget* parent=NULL);
        explicit CGLabel(int x, int y, int width, int height, CGWidget* parent=NULL);
        explicit CGLabel(const std::string& text, CGWidget* parent=NULL);
        virtual ~CGLabel();

        virtual void setText(const std::string& text);
        inline std::string text() const {
            return m_text;
        }

        inline float textOffset() const {
            return m_textOffset;
        }
        inline void setTextOffset(float size) {
            m_textOffset=size;
        }


        virtual void paint(cairo_t *c)  override;
        void setPropsFromPalette(CGPalette *palette);
    protected:
        std::string m_text;
        float m_textOffset;


};



/** \brief a widget that displays an animated text (wandering left/right to show the full text) */
class CGMarqueeLabel: public CGLabel {
    public:
        explicit CGMarqueeLabel(CGWidget* parent=NULL);
        explicit CGMarqueeLabel(int x, int y, int width, int height, const std::string& text, CGWidget* parent=NULL);
        explicit CGMarqueeLabel(int x, int y, int width, int height, CGWidget* parent=NULL);
        explicit CGMarqueeLabel(const std::string& text, CGWidget* parent=NULL);

        virtual void setText(const std::string& text);

        inline float stepDurationMS() const {
            return m_stepDurationMS;
        }
        inline void setStepDurationMS(float duration_ms) {
            m_stepDurationMS=duration_ms;
        }

        virtual void paint(cairo_t *c)  override;
    protected:
        int m_stepDurationMS;
        std::chrono::steady_clock::time_point m_start;
        float m_lastOffset;
        std::string m_lastCalcText;
        int m_lastCalcWidth;
        int m_lastDirection;

};

#endif // CGLABEL_H
