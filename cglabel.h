#ifndef CGLABEL_H
#define CGLABEL_H

#include "cgframe.h"
#include <string>

class CGLabel: public CGFrame
{
    public:
        enum Alignment {
            alCenter,
            alStart,
            alEnd,
            alLeft=alStart,
            alRight=alEnd,
            alTop=alStart,
            alBottom=alEnd,

        };

        explicit CGLabel(CGWidget* parent=NULL);
        explicit CGLabel(int x, int y, int width, int height, const std::string& text, CGWidget* parent=NULL);
        explicit CGLabel(int x, int y, int width, int height, CGWidget* parent=NULL);
        explicit CGLabel(const std::string& text, CGWidget* parent=NULL);
        virtual ~CGLabel();

        void setText(const std::string& text);
        inline std::string text() const {
            return m_text;
        }

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

        inline float lineSpacing() const {
            return m_lineSpacing;
        }
        inline void setLineSpacing(float size) {
            m_lineSpacing=size;
        }

        inline float fontSize() const {
            return m_fontSize;
        }
        inline void setFontSize(float size) {
            m_fontSize=size;
        }

        inline float textOffset() const {
            return m_textOffset;
        }
        inline void setTextOffset(float size) {
            m_textOffset=size;
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

        inline Alignment verticalAlignment() const {
            return m_verticalAlignment;
        }
        inline void setVerticalAlignment(Alignment val) {
            m_verticalAlignment=val;
        }
        inline Alignment horizontalAlignment() const {
            return m_horizontalAlignment;
        }
        inline void setHorizontalAlignment(Alignment val) {
            m_horizontalAlignment=val;
        }

        virtual void paint(cairo_t *c) const;
    protected:
        std::string m_text;
        CGColor m_textColor;
        float m_fontSize;
        bool m_bold;
        bool m_italic;
        std::string m_fontFace;
        float m_lineSpacing;
        float m_textOffset;

        Alignment m_verticalAlignment;
        Alignment m_horizontalAlignment;

};

#endif // CGLABEL_H
