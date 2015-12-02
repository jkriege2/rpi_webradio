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

template<typename T>
inline T cgBound(T mi, T val, T ma) {
    if (val<mi) return mi;
    else if (val>ma) return ma;
    return val;
}

/** \brief represents a color in RGBA */
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

    inline void setRGB(unsigned char r, unsigned char g, unsigned char b) {
        this->r=r;
        this->g=g;
        this->b=b;
    }
    inline void setRGBF(float r, float g, float b) {
        this->r=cgBound<int>(0, r*255.0, 255);
        this->g=cgBound<int>(0, g*255.0, 255);
        this->b=cgBound<int>(0, b*255.0, 255);
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

    void getHSV(float& h, float& s, float& v) const;
    void setFromHSV(float h, float s, float v);

    CGColor lighter(float factor=200);
    CGColor darker(float factor=200);
};

/** \brief implement \c operator<<() for CGColor output into streams. */
std::ostream& operator<< (std::ostream& stream, const CGColor& matrix);


/** \brief alignment constants */
enum cgAlignment {
    cgalCenter,
    cgalStart,
    cgalEnd,
    cgalLeft=cgalStart,
    cgalRight=cgalEnd,
    cgalTop=cgalStart,
    cgalBottom=cgalEnd,

};

/** \brief direction constants */
enum cgDirection {
    cgdHorizontal=0x00,
    cgdVertical=0x01,
};

/** \brief this class represents a rectangle with a user-specifyable type for the top-left coordinate (x,y) and size (width,height) */
template<typename T>
struct cgSize {
    inline cgSize() {
        width=height=0;
    }

    inline cgSize(T width, T height) {
        this->width=width;
        this->height=height;
    }
    /** \brief width  */
    T width;
    /** \brief height  */
    T height;
};

/** \brief implement \c operator<<() for cgSize output into streams. */
template<typename T>
inline std::ostream& operator<< (std::ostream& stream, const cgSize<T>& r) {
    stream<<"cgSize["<<r.width<<", "<<r.height<<"]";
    return stream;
}

/** \brief this class represents a rectangle with a user-specifyable type for the top-left coordinate (x,y) and size (width,height) */
template<typename T>
struct cgRect {
    inline cgRect() {
        x=y=width=height=0;
    }

    inline cgRect(T x, T y, T width, T height) {
        this->x=x;
        this->y=y;
        this->width=width;
        this->height=height;
    }

    /** \brief left start of rectangle */
    T x;
    /** \brief top start of rectangle */
    T y;
    /** \brief width of rectangle */
    T width;
    /** \brief height of rectangle */
    T height;

    /** \brief translate to the top left (x,y) in the given cairo context \a c */
    inline void cairo_translateTopLeft(cairo_t *c) const {
        cairo_translate(c, x,y);
    }
    /** \brief clip this rectangle  */
    inline void cairo_clip(cairo_t *c) const {
        std::cout<<"clip "<<*this<<std::endl;
        cairo_rectangle(c, x,y,width,height);
        cairo_clip(c);
    }
    /** \brief draw the rectangle-frame-line around it (colored with \a color and with a width of \a framewidth)  */
    inline void cairo_draw(cairo_t *c, CGColor color, float framewidth=1) const {
        cgDrawRectangle(c, x,y,width,height,color,framewidth);
    }
    /** \brief draw the rectangle, filled with fillColor  */
    inline void cairo_drawFilled(cairo_t *c, CGColor fillColor) const {
        cgDrawFilledRectangle(c, x,y,width,height,fillColor);
    }
    /** \brief draw the rectangle, filled with fillColor and with a frame-line around it (colored with \a color and with a width of \a framewidth)  */
    inline void cairo_drawFilled(cairo_t *c, CGColor fillColor, CGColor color, float framewidth=1) const {
        cgDrawFilledRectangle(c, x,y,width,height, fillColor,color,framewidth);
    }
    template<typename T2>
    inline cgSize<T2> size() const {
        return cgSize<T2>(width, height);
    }

};


/** \brief implement \c operator<<() for cgRect output into streams. */
template<typename T>
inline std::ostream& operator<< (std::ostream& stream, const cgRect<T>& r) {
    stream<<"cgRect[tl=("<<r.x<<", "<<r.y<<"), size=("<<r.width<<", "<<r.height<<")]";
    return stream;
}


/** \brief draw the given text using cairo */
void cgDrawText(cairo_t* cr, int xx, int yy, int m_width, int m_height, const std::string& m_text, const std::string& m_fontFace=std::string("sans"), float m_fontSize=10.0, bool m_italic=false, bool m_bold=false, CGColor m_textColor=CGColor::ccBlack, float m_lineSpacing=1.2, cgAlignment m_horizontalAlignment=cgalCenter, cgAlignment m_verticalAlignment=cgalCenter);
/** \brief draw a non-filled rectangle frame */
void cgDrawRectangle(cairo_t* cr, int xx, int yy, int m_width, int m_height, CGColor color, float framewidth=1);
/** \brief draw a filled and framed rectangle frame */
void cgDrawFilledRectangle(cairo_t* cr, int xx, int yy, int m_width, int m_height, CGColor fillColor, CGColor color, float framewidth=1);
/** \brief draw a filled and non-framed rectangle frame */
void cgDrawFilledRectangle(cairo_t* cr, int xx, int yy, int m_width, int m_height, CGColor fillColor);
/** \brief draw a line */
void cgDrawLine(cairo_t* cr, int x1, int y1, int x2, int y2, CGColor color, float framewidth=1);
/** \brief draw a 2-line poylgon */
void cgDrawLines(cairo_t* cr, int x1, int y1, int x2, int y2, int x3, int y3, CGColor color, float framewidth=1);
/** \brief draw a 3-line poylgon */
void cgDrawLines(cairo_t* cr, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, CGColor color, float framewidth=1);
/** \brief draw a 4-line poylgon */
void cgDrawLines(cairo_t* cr, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, CGColor color, float framewidth=1);
/** \brief draw a 2-line poylgon */
void cgDrawPolygon(cairo_t* cr, int x1, int y1, int x2, int y2, int x3, int y3, CGColor color, float framewidth=1);
/** \brief draw a 3-line poylgon */
void cgDrawPolygon(cairo_t* cr, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, CGColor color, float framewidth=1);
/** \brief draw a 4-line poylgon */
void cgDrawPolygon(cairo_t* cr, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, CGColor color, float framewidth=1);
/** \brief fill a 2-line poylgon (automatically closed) */
void cgFillPolygon(cairo_t* cr, int x1, int y1, int x2, int y2, int x3, int y3, CGColor fillcolor);
/** \brief draw a 3-line poylgon (automatically closed)  */
void cgFillPolygon(cairo_t* cr, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, CGColor fillcolor);
/** \brief draw a 4-line poylgon (automatically closed)  */
void cgFillPolygon(cairo_t* cr, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, CGColor fillcolor);
/** \brief draw an image  */
void cgDrawImage(cairo_t* cr, int x, int y, int width, int height, cairo_surface_t *img_surface, int img_width, int img_height);


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
/** \brief returns \c true, if the string consists of whitepsaces only */
bool cgOnlySpace(const std::string& text);

#endif // CGBASICS_H
