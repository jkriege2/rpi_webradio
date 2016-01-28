#ifndef CGLABEL_H
#define CGLABEL_H

#include "cgframe.h"
#include <string>
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

        void setText(const std::string& text);
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

#endif // CGLABEL_H
