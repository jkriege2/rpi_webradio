#ifndef CGPROGRESSBAR_H
#define CGPROGRESSBAR_H

#include "cgframe.h"
#include "cgfontprops.h"

/** \brief a progress bar with 0..100% number */
class CGProgressBar : public CGFrame
{
    public:
        explicit CGProgressBar(CGWidget* parent=NULL);
        explicit CGProgressBar(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGProgressBar();

        inline float value() const {
            return m_value;
        }
        inline void setValue(float v) {
            m_value=v;
        }
        inline float max() const {
            return m_max;
        }
        inline void setMax(float v) {
            m_max=v;
        }
        inline float min() const {
            return m_min;
        }
        inline void setMin(float v) {
            m_min=v;
        }
        inline void setRange(float min, float max) {
            m_min=min;
            m_max=max;
        }
        inline CGColor progressColor() const {
            return m_progressColor;
        }
        inline void setProgressColor(CGColor v) {
            m_progressColor=v;
        }
        inline bool showText() const {
            return m_showText;
        }
        inline void setShowText(bool val) {
            m_showText=val;
        }
        inline bool showUserText() const {
            return m_showUserText;
        }
        inline void setShowUserText(bool val) {
            m_showUserText=val;
        }
        inline std::string userText() const {
            return m_userText;
        }
        inline void setUserText(const std::string& val) {
            m_userText=val;
        }
        inline void setUserText(const std::string& val, bool enabled) {
            m_userText=val;
            m_showUserText=enabled;
        }


        virtual void paint(cairo_t *c)  override;
        virtual std::string progressText() const;

        void setPropsFromPalette(CGPalette *palette);
    protected:
        float m_min;
        float m_max;
        float m_value;
        CGColor m_progressColor;
        bool m_showText;
        std::string m_userText;
        bool m_showUserText;
};


#endif // CGPROGRESSBAR_H
