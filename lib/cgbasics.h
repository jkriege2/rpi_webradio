#ifndef CGBASICS_H
#define CGBASICS_H

#include <cairo.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

struct CGColor {
    enum ColorConstants {
        ccTransparent=0,
        ccBlack,
        ccWhite,
        ccGray,
        ccGray10,
        ccGray25,
        ccGray75,
        ccGray50,
        ccGrey,
        ccGrey10,
        ccGrey25,
        ccGrey50,
        ccGrey75,
        ccSilver,
        ccDarkgrey,
        ccDarkgray,
        ccRed,
        ccDarkred,
        ccGreen,
        ccDarkgreen,
        ccBlue,
        ccDarkblue,
        ccMagenta,
        ccDarkmagenta,
        ccYellow,
        ccOrange,
        ccCyan,
        ccDarkcyan,
        ccDarkorange,
        ccNavy,

        ccInvalid,
    };
     CGColor(ColorConstants color=ccBlack);
    inline  CGColor(const CGColor& other) {
        r=other.r;
        g=other.g;
        b=other.b;
        a=other.a;
    }

     CGColor(const std::string& color);
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

    inline CGColor& operator=(const CGColor& other) {
        r=other.r;
        g=other.g;
        b=other.b;
        a=other.a;
        return *this;
    }
    CGColor& operator=(ColorConstants color);
    inline float redf() const {
        return float(r)/255.0;
    }
    inline float greenf() const {
        return float(g)/255.0;
    }
    inline float bluef() const {
        return float(b)/255.0;
    }
    inline float alphaf() const {
        return float(a)/255.0;
    }


    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    inline bool isTransparent() const {
        return a==0;
    }


    std::string toString() const;
    inline void cairo_set_source(cairo_t* c) const {
        cairo_set_source_rgba(c, redf(), greenf(), bluef(), alphaf());
    }

    static CGColor colorLinear(float v, CGColor col1, CGColor col2);
    inline CGColor colorLinearTo(float v, CGColor col2) const {
        return colorLinear(v, *this, col2);
    }
    inline CGColor colorLinearFrom(float v, CGColor col1) const {
        return colorLinear(v, col1, *this);
    }
};

std::ostream& operator<< (std::ostream& stream, const CGColor& matrix);


class CGEvent {
     public:
        explicit CGEvent();
        virtual ~CGEvent() {}
        virtual std::string toString();
        void accept();
        inline bool accepted() const {
            return m_accepted;
        }
    protected:
        bool m_accepted;
};

class cgClickEvent: public CGEvent {
     public:
        enum Button {
            Button1=1,
            Button2=2,

            ButtonDefault=Button1,
            ButtonLeft=Button1,
            ButtonRight=Button2
        };

        explicit cgClickEvent(int x, int y, Button button=ButtonDefault);
        virtual ~cgClickEvent() {}
        virtual std::string toString();

        inline int x() const { return m_x; }
        inline int y() const { return m_y; }
        inline Button button() const { return m_button; }

    protected:
        Button m_button;
        int m_x;
        int m_y;
};

class cgButtonEvent: public CGEvent {
     public:

        explicit cgButtonEvent(int button);
        virtual ~cgButtonEvent() {}
        virtual std::string toString();
        inline int button() const { return m_button; }
    protected:
        int m_button;
};

class cgKeyEvent: public CGEvent {
     public:

        explicit cgKeyEvent(int key, bool shift=false, bool ctrl=false, bool alt=false);
        virtual ~cgKeyEvent() {}
        virtual std::string toString();

        inline int key() const { return m_key; }
        inline bool shift() const { return m_shift; }
        inline bool ctrl() const { return m_ctrl; }
        inline bool alt() const { return m_alt; }
    protected:
        int m_key;
        bool m_shift;
        bool m_ctrl;
        bool m_alt;
};

enum cgAlignment {
    cgalCenter,
    cgalStart,
    cgalEnd,
    cgalLeft=cgalStart,
    cgalRight=cgalEnd,
    cgalTop=cgalStart,
    cgalBottom=cgalEnd,

};
void cgDrawText(cairo_t* cr, int xx, int yy, int m_width, int m_height, const std::string& m_text, const std::string& m_fontFace=std::string("sans"), float m_fontSize=10.0, bool m_italic=false, bool m_bold=false, CGColor m_textColor=CGColor::ccBlack, float m_lineSpacing=1.2, cgAlignment m_horizontalAlignment=cgalCenter, cgAlignment m_verticalAlignment=cgalCenter);


/** \brief convert a long integer to a C++ string */
std::string cgIntToStr(long data);
/** \brief convert a long integer to a C++ string containing the number in hex notation */
std::string cgIntToHex(long data);
/** \brief convert a unsigned long integer to a C++ string */
std::string cgUIntToStr(unsigned long data);
/** \brief convert a long integer to a C++ string by using a printf-style format string (see <A HREF="http://www.cplusplus.com/reference/clibrary/cstdio/printf.html">printf format quick reference</A>)  */
std::string cgIntToStrFmt(long data, const std::string & cgFormat="%ld");
/** \brief convert an unsigned long integer to a C++ string by using a printf-style format string (see <A HREF="http://www.cplusplus.com/reference/clibrary/cstdio/printf.html">printf format quick reference</A>)  */
std::string cgUIntToStrFmt(unsigned long data, const std::string & cgFormat="%ld");
/** \brief convert a double float to a C++ string. in \a past_comma you can give the number of digits
 *         to show after the decimal divider. If \a remove_trail0 is \c true the method removes all trailing '0'.
 *
 * If \a belowIsZero>0 and \c abs(data) is smaller than \a belowIsZero, then \c "0" is returned.
 */
std::string cgFloatToStr(double data, int past_comma=-1, bool remove_trail0=false, double belowIsZero=1e-16);
/*! \brief convert a given string to a double floating point value.

    \param data input string
    \return the number read from the given string
    \throws std::runtime_error if a conversion error occurs

    Basically this function is a wrapper around strtod() from libc.
 */
double cgStrToFloat(const std::string & data);
/** \brief convert a double float to a C++ string by using a printf-style format string (see <A HREF="http://www.cplusplus.com/reference/clibrary/cstdio/printf.html">printf format quick reference</A>) */
std::string cgFloatToStrFmt(double data, const std::string &cgFormat="%lf");
/** \brief prints the supplied number of bytes. If bytes>1024 it prints (bytes/1024)+" kBytes" ... */
std::string cgBytesToStr(double bytes);
/** \brief convert a boolean to a C++ string. Return \c "true" or \c "false" */
std::string cgBoolToStr(bool data);
/*! \brief convert a C++ string to a boolean.

    This function accepts \c "true", \c "t", \c "1", \c "j", \c "y", \c "yes", \c "ja" as \c true and returns \c false
    if none of these was found.
 */
bool cgStrToBool(const std::string & data);

/** \brief like sprintf(), but returns a std::string (see <A HREF="http://www.cplusplus.com/reference/clibrary/cstdio/printf.html">printf format quick reference</A>)  */
std::string cgFormat(const std::string & templ, ...);
/** \brief convert a string to all lower case letters */
std::string cgToLower(const std::string & s);

/** \brief convert a string to all upper case letters */
std::string cgToUpper(const std::string & s);

bool cgOnlySpace(const std::string& text);

#endif // CGBASICS_H
