#ifndef CGFONTPROPS_H
#define CGFONTPROPS_H

#include "cgbasics.h"
#include <string>

class CGFontProps
{
    public:
        inline CGFontProps() {
            m_bold=false;
            m_italic=false;
            m_fontFace="sans";
            m_fontSize=10;
            m_lineSpacing=1.2;
            etTextColor(CGColor::ccBlack);
        }

        virtual ~CGFontProps() {}

        inline CGColor textColor() const {
            return m_textColor;
        }
        void setTextColor(CGColor col);

        inline std::string fontFace() const {
            return m_fontFace;
        }
        inline void setFontFace(const std::string& val) {
            m_fontFace=val;
        }

        inline bool bold() const {
            return m_bold;
        }
        inline void setBold(bool val) {
            m_bold=val;
        }

        inline bool italic() const {
            return m_italic;
        }
        inline void setItalic(bool val) {
            m_italic=val;
        }
        inline float fontSize() const {
            return m_fontSize;
        }
        inline void setFontSize(float size) {
            m_fontSize=size;
        }
        inline float lineSpacing() const {
            return m_lineSpacing;
        }
        inline void setLineSpacing(float size) {
            m_lineSpacing=size;
        }
    protected:
        CGColor m_textColor;
        float m_fontSize;
        bool m_bold;
        bool m_italic;
        std::string m_fontFace;
        float m_lineSpacing;

};

class CGFontPropsWithAlignment: public CGFontProps {
    public:
        inline CGFontPropsWithAlignment() {
            m_verticalAlignment=cgalLeft;
            m_horizontalAlignment=cgalTop;
        }

        virtual ~CGFontPropsWithAlignment() {}

        inline cgAlignment verticalAlignment() const {
            return m_verticalAlignment;
        }
        inline void setVerticalAlignment(cgAlignment val) {
            m_verticalAlignment=val;
        }
        inline cgAlignment horizontalAlignment() const {
            return m_horizontalAlignment;
        }
        inline void setHorizontalAlignment(cgAlignment val) {
            m_horizontalAlignment=val;
        }
    protected:

        cgAlignment m_verticalAlignment;
        cgAlignment m_horizontalAlignment;

};


#endif // CGFONTPROPS_H
