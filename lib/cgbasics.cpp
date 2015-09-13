#include "cgbasics.h"

#include <exception>
#include <stdexcept>
#include <cmath>
#include <stdarg.h>
#include <stdint.h>
#include <list>

#ifdef rgb
#  undef rgb
#endif
#define rgb(r,g,b) (uint32_t(0xff000000 | (uint8_t(r) << 16) |  (uint8_t(g) << 8) | uint8_t(b)))
#define rgba(r,g,b,a) (uint32_t((uint8_t(a)<<24) | (uint8_t(r) << 16) |  (uint8_t(g) << 8) | uint8_t(b)))
#define rgbA(r) ((r&0xFF000000)>>24);
#define rgbR(r) ((r&0x00FF0000)>>16);
#define rgbG(r) ((r&0x0000FF00)>>8);
#define rgbB(r) ((r&0x000000FF));

static const struct RGBData {
    CGColor::ColorConstants colorConst;
    const char *name;
    uint32_t  value;
} CGColorRGBTbl[] = {
    { CGColor::ccInvalid, "invalid", rgb(0, 0, 0) },
    { CGColor::ccTransparent, "transparent", rgba(255,255,255,0) },
    { CGColor::ccInvalid, "aliceblue", rgb(240, 248, 255) },
    { CGColor::ccInvalid, "antiquewhite", rgb(250, 235, 215) },
    { CGColor::ccInvalid, "aqua", rgb( 0, 255, 255) },
    { CGColor::ccInvalid, "aquamarine", rgb(127, 255, 212) },
    { CGColor::ccInvalid, "azure", rgb(240, 255, 255) },
    { CGColor::ccInvalid, "beige", rgb(245, 245, 220) },
    { CGColor::ccInvalid, "bisque", rgb(255, 228, 196) },
    { CGColor::ccBlack, "black", rgb( 0, 0, 0) },
    { CGColor::ccInvalid, "blanchedalmond", rgb(255, 235, 205) },
    { CGColor::ccBlue, "blue", rgb( 0, 0, 255) },
    { CGColor::ccInvalid, "blueviolet", rgb(138, 43, 226) },
    { CGColor::ccInvalid, "brown", rgb(165, 42, 42) },
    { CGColor::ccInvalid, "burlywood", rgb(222, 184, 135) },
    { CGColor::ccInvalid, "cadetblue", rgb( 95, 158, 160) },
    { CGColor::ccInvalid, "chartreuse", rgb(127, 255, 0) },
    { CGColor::ccInvalid, "chocolate", rgb(210, 105, 30) },
    { CGColor::ccInvalid, "coral", rgb(255, 127, 80) },
    { CGColor::ccInvalid, "cornflowerblue", rgb(100, 149, 237) },
    { CGColor::ccInvalid, "cornsilk", rgb(255, 248, 220) },
    { CGColor::ccInvalid, "crimson", rgb(220, 20, 60) },
    { CGColor::ccCyan, "cyan", rgb( 0, 255, 255) },
    { CGColor::ccDarkblue, "darkblue", rgb( 0, 0, 139) },
    { CGColor::ccDarkcyan, "darkcyan", rgb( 0, 139, 139) },
    { CGColor::ccInvalid, "darkgoldenrod", rgb(184, 134, 11) },
    { CGColor::ccInvalid, "darkgray", rgb(169, 169, 169) },
    { CGColor::ccDarkgreen, "darkgreen", rgb( 0, 100, 0) },
    { CGColor::ccDarkgrey, "darkgrey", rgb(169, 169, 169) },
    { CGColor::ccDarkgray, "darkgray", rgb(169, 169, 169) },
    { CGColor::ccInvalid, "darkkhaki", rgb(189, 183, 107) },
    { CGColor::ccDarkmagenta, "darkmagenta", rgb(139, 0, 139) },
    { CGColor::ccInvalid, "darkolivegreen", rgb( 85, 107, 47) },
    { CGColor::ccDarkorange, "darkorange", rgb(255, 140, 0) },
    { CGColor::ccInvalid, "darkorchid", rgb(153, 50, 204) },
    { CGColor::ccDarkred, "darkred", rgb(139, 0, 0) },
    { CGColor::ccInvalid, "darksalmon", rgb(233, 150, 122) },
    { CGColor::ccInvalid, "darkseagreen", rgb(143, 188, 143) },
    { CGColor::ccInvalid, "darkslateblue", rgb( 72, 61, 139) },
    { CGColor::ccInvalid, "darkslategray", rgb( 47, 79, 79) },
    { CGColor::ccInvalid, "darkslategrey", rgb( 47, 79, 79) },
    { CGColor::ccInvalid, "darkturquoise", rgb( 0, 206, 209) },
    { CGColor::ccInvalid, "darkviolet", rgb(148, 0, 211) },
    { CGColor::ccInvalid, "deeppink", rgb(255, 20, 147) },
    { CGColor::ccInvalid, "deepskyblue", rgb( 0, 191, 255) },
    { CGColor::ccInvalid, "dimgray", rgb(105, 105, 105) },
    { CGColor::ccInvalid, "dimgrey", rgb(105, 105, 105) },
    { CGColor::ccInvalid, "dodgerblue", rgb( 30, 144, 255) },
    { CGColor::ccInvalid, "firebrick", rgb(178, 34, 34) },
    { CGColor::ccInvalid, "floralwhite", rgb(255, 250, 240) },
    { CGColor::ccInvalid, "forestgreen", rgb( 34, 139, 34) },
    { CGColor::ccInvalid, "fuchsia", rgb(255, 0, 255) },
    { CGColor::ccInvalid, "gainsboro", rgb(220, 220, 220) },
    { CGColor::ccInvalid, "ghostwhite", rgb(248, 248, 255) },
    { CGColor::ccInvalid, "gold", rgb(255, 215, 0) },
    { CGColor::ccInvalid, "goldenrod", rgb(218, 165, 32) },
    { CGColor::ccGreen, "green", rgb( 0, 128, 0) },
    { CGColor::ccInvalid, "greenyellow", rgb(173, 255, 47) },
    { CGColor::ccGray,    "gray", rgb(128, 128, 128) },
    { CGColor::ccGrey,    "grey", rgb(128, 128, 128) },
    { CGColor::ccGrey50,  "grey50", rgb(128, 128, 128) },
    { CGColor::ccGray50,  "gray50", rgb(128, 128, 128) },
    { CGColor::ccGrey75,  "grey75", rgb(192, 192, 192) },
    { CGColor::ccGray75,  "gray75", rgb(192, 192, 192) },
    { CGColor::ccGrey10,  "grey10", rgb(26,26,26) },
    { CGColor::ccGray10,  "gray10", rgb(26,26,26) },
    { CGColor::ccGrey25,  "grey25", rgb(64,64,64) },
    { CGColor::ccGray25,  "gray25", rgb(64,64,64) },
    { CGColor::ccInvalid, "honeydew", rgb(240, 255, 240) },
    { CGColor::ccInvalid, "hotpink", rgb(255, 105, 180) },
    { CGColor::ccInvalid, "indianred", rgb(205, 92, 92) },
    { CGColor::ccInvalid, "indigo", rgb( 75, 0, 130) },
    { CGColor::ccInvalid, "ivory", rgb(255, 255, 240) },
    { CGColor::ccInvalid, "khaki", rgb(240, 230, 140) },
    { CGColor::ccInvalid, "lavender", rgb(230, 230, 250) },
    { CGColor::ccInvalid, "lavenderblush", rgb(255, 240, 245) },
    { CGColor::ccInvalid, "lawngreen", rgb(124, 252, 0) },
    { CGColor::ccInvalid, "lemonchiffon", rgb(255, 250, 205) },
    { CGColor::ccInvalid, "lightblue", rgb(173, 216, 230) },
    { CGColor::ccInvalid, "lightcoral", rgb(240, 128, 128) },
    { CGColor::ccInvalid, "lightcyan", rgb(224, 255, 255) },
    { CGColor::ccInvalid, "lightgoldenrodyellow", rgb(250, 250, 210) },
    { CGColor::ccInvalid, "lightgray", rgb(211, 211, 211) },
    { CGColor::ccInvalid, "lightgreen", rgb(144, 238, 144) },
    { CGColor::ccInvalid, "lightgrey", rgb(211, 211, 211) },
    { CGColor::ccInvalid, "lightpink", rgb(255, 182, 193) },
    { CGColor::ccInvalid, "lightsalmon", rgb(255, 160, 122) },
    { CGColor::ccInvalid, "lightseagreen", rgb( 32, 178, 170) },
    { CGColor::ccInvalid, "lightskyblue", rgb(135, 206, 250) },
    { CGColor::ccInvalid, "lightslategray", rgb(119, 136, 153) },
    { CGColor::ccInvalid, "lightslategrey", rgb(119, 136, 153) },
    { CGColor::ccInvalid, "lightsteelblue", rgb(176, 196, 222) },
    { CGColor::ccInvalid, "lightyellow", rgb(255, 255, 224) },
    { CGColor::ccInvalid, "lime", rgb( 0, 255, 0) },
    { CGColor::ccInvalid, "limegreen", rgb( 50, 205, 50) },
    { CGColor::ccInvalid, "linen", rgb(250, 240, 230) },
    { CGColor::ccMagenta, "magenta", rgb(255, 0, 255) },
    { CGColor::ccInvalid, "maroon", rgb(128, 0, 0) },
    { CGColor::ccInvalid, "mediumaquamarine", rgb(102, 205, 170) },
    { CGColor::ccInvalid, "mediumblue", rgb( 0, 0, 205) },
    { CGColor::ccInvalid, "mediumorchid", rgb(186, 85, 211) },
    { CGColor::ccInvalid, "mediumpurple", rgb(147, 112, 219) },
    { CGColor::ccInvalid, "mediumseagreen", rgb( 60, 179, 113) },
    { CGColor::ccInvalid, "mediumslateblue", rgb(123, 104, 238) },
    { CGColor::ccInvalid, "mediumspringgreen", rgb( 0, 250, 154) },
    { CGColor::ccInvalid, "mediumturquoise", rgb( 72, 209, 204) },
    { CGColor::ccInvalid, "mediumvioletred", rgb(199, 21, 133) },
    { CGColor::ccInvalid, "midnightblue", rgb( 25, 25, 112) },
    { CGColor::ccInvalid, "mintcream", rgb(245, 255, 250) },
    { CGColor::ccInvalid, "mistyrose", rgb(255, 228, 225) },
    { CGColor::ccInvalid, "moccasin", rgb(255, 228, 181) },
    { CGColor::ccInvalid, "navajowhite", rgb(255, 222, 173) },
    { CGColor::ccNavy, "navy", rgb( 0, 0, 128) },
    { CGColor::ccInvalid, "navy(16)", rgb( 0, 0, 128) },
    { CGColor::ccInvalid, "oldlace", rgb(253, 245, 230) },
    { CGColor::ccInvalid, "olive", rgb(128, 128, 0) },
    { CGColor::ccInvalid, "olivedrab", rgb(107, 142, 35) },
    { CGColor::ccOrange, "orange", rgb(255, 165, 0) },
    { CGColor::ccInvalid, "orangered", rgb(255, 69, 0) },
    { CGColor::ccInvalid, "orchid", rgb(218, 112, 214) },
    { CGColor::ccInvalid, "palegoldenrod", rgb(238, 232, 170) },
    { CGColor::ccInvalid, "palegreen", rgb(152, 251, 152) },
    { CGColor::ccInvalid, "paleturquoise", rgb(175, 238, 238) },
    { CGColor::ccInvalid, "palevioletred", rgb(219, 112, 147) },
    { CGColor::ccInvalid, "papayawhip", rgb(255, 239, 213) },
    { CGColor::ccInvalid, "peachpuff", rgb(255, 218, 185) },
    { CGColor::ccInvalid, "peru", rgb(205, 133, 63) },
    { CGColor::ccInvalid, "pink", rgb(255, 192, 203) },
    { CGColor::ccInvalid, "plum", rgb(221, 160, 221) },
    { CGColor::ccInvalid, "powderblue", rgb(176, 224, 230) },
    { CGColor::ccInvalid, "purple", rgb(128, 0, 128) },
    { CGColor::ccRed, "red", rgb(255, 0, 0) },
    { CGColor::ccInvalid, "rosybrown", rgb(188, 143, 143) },
    { CGColor::ccInvalid, "royalblue", rgb( 65, 105, 225) },
    { CGColor::ccInvalid, "saddlebrown", rgb(139, 69, 19) },
    { CGColor::ccInvalid, "salmon", rgb(250, 128, 114) },
    { CGColor::ccInvalid, "sandybrown", rgb(244, 164, 96) },
    { CGColor::ccInvalid, "seagreen", rgb( 46, 139, 87) },
    { CGColor::ccInvalid, "seashell", rgb(255, 245, 238) },
    { CGColor::ccInvalid, "sienna", rgb(160, 82, 45) },
    { CGColor::ccSilver, "silver", rgb(192, 192, 192) },
    { CGColor::ccInvalid, "skyblue", rgb(135, 206, 235) },
    { CGColor::ccInvalid, "slateblue", rgb(106, 90, 205) },
    { CGColor::ccInvalid, "slategray", rgb(112, 128, 144) },
    { CGColor::ccInvalid, "slategrey", rgb(112, 128, 144) },
    { CGColor::ccInvalid, "snow", rgb(255, 250, 250) },
    { CGColor::ccInvalid, "springgreen", rgb( 0, 255, 127) },
    { CGColor::ccInvalid, "steelblue", rgb( 70, 130, 180) },
    { CGColor::ccInvalid, "tan", rgb(210, 180, 140) },
    { CGColor::ccInvalid, "teal", rgb( 0, 128, 128) },
    { CGColor::ccInvalid, "thistle", rgb(216, 191, 216) },
    { CGColor::ccInvalid, "tomato", rgb(255, 99, 71) },
    { CGColor::ccInvalid, "transparent", 0 },
    { CGColor::ccInvalid, "turquoise", rgb( 64, 224, 208) },
    { CGColor::ccInvalid, "violet", rgb(238, 130, 238) },
    { CGColor::ccInvalid, "wheat", rgb(245, 222, 179) },
    { CGColor::ccWhite, "white", rgb(255, 255, 255) },
    { CGColor::ccInvalid, "whitesmoke", rgb(245, 245, 245) },
    { CGColor::ccYellow, "yellow", rgb(255, 255, 0) },
    { CGColor::ccInvalid, "yellowgreen", rgb(154, 205, 50) },
};

static const int CGColorRGBTblSize = sizeof(CGColorRGBTbl) / sizeof(RGBData);

std::string CGColor::toString() const {
    if (a==255) {// only for non-transparent colors
        for (int i=0; i<CGColorRGBTblSize; i++) {
            if (rgb(r,g,b)==CGColorRGBTbl[i].value) {
                return CGColorRGBTbl[i].name;
            }
        }
        return cgFormat("#%02X%02X%02X", (int)r, (int)g, (int)b);
    }
    // if we reach this, we have an unnamed transparent color
    return cgFormat("#%02X%02X%02X%02X", (int)r, (int)g, (int)b, (int)a);
}

CGColor CGColor::colorLinear(float v, CGColor col1, CGColor col2)
{
    CGColor c;
    c.r=col1.r+round(v*float(col2.r-col1.r));
    c.g=col1.g+round(v*float(col2.g-col1.g));
    c.b=col1.b+round(v*float(col2.b-col1.b));
    c.a=col1.a+round(v*float(col2.a-col1.a));
    return c;
}


CGColor::CGColor(CGColor::ColorConstants color)
{
    r=g=b=0;
    a=255;
    if (color!=ccInvalid) {
        for (int i=0; i<CGColorRGBTblSize; i++) {
            if (CGColorRGBTbl[i].colorConst==color) {
                r=rgbR(CGColorRGBTbl[i].value);
                g=rgbG(CGColorRGBTbl[i].value);
                b=rgbB(CGColorRGBTbl[i].value);
                a=rgbA(CGColorRGBTbl[i].value);
                break;
            }
        }
    }
}

CGColor::CGColor(const std::string &color)
{
    r=g=b=0;
    a=255;
    for (int i=0; i<CGColorRGBTblSize; i++) {
        if (std::string(CGColorRGBTbl[i].name)==color) {
            r=rgbR(CGColorRGBTbl[i].value);
            g=rgbG(CGColorRGBTbl[i].value);
            b=rgbB(CGColorRGBTbl[i].value);
            a=rgbA(CGColorRGBTbl[i].value);
            break;
        }
    }
}

CGColor &CGColor::operator=(CGColor::ColorConstants color)
{
    r=g=b=0;
    a=255;
    if (color!=ccInvalid) {
        for (int i=0; i<CGColorRGBTblSize; i++) {
            if (CGColorRGBTbl[i].colorConst==color) {
                r=rgbR(CGColorRGBTbl[i].value);
                g=rgbG(CGColorRGBTbl[i].value);
                b=rgbB(CGColorRGBTbl[i].value);
                a=rgbA(CGColorRGBTbl[i].value);
                break;
            }
        }
    }
    return *this;
}


std::string cgIntToStr(long data){
  return cgFormat("%ld", data);
}

std::string cgIntToHex(long data){
  return cgFormat("%lX", data);
}

std::string cgUIntToStr(unsigned long data){
  std::ostringstream ost;
  ost<<data;
  return ost.str();
}

std::string cgFloatToStr(double data, int past_comma, bool remove_trail0, double belowIsZero){
  if (belowIsZero>0) {
      if (fabs(data)<belowIsZero) return std::string("0");
  }

  std::string form="%."+cgIntToStr(past_comma)+"lf";
  //std::string form="%lf";
  if (past_comma<=0) form="%lf";
  std::string r=cgFormat(form,data);
  //std::cout<<r<<std::endl;
  if (remove_trail0 && (cgToLower(r).find('e')==std::string::npos)) {
      if (data==0) return "0";
      //size_t cp=r.find(".");
      //if (cp<r.size()) return r;
      std::string re;
      size_t dpos=r.find('.');
      if (dpos==std::string::npos) {
          return r;
      } else {
          long i=r.size()-1;
          bool nonz=false;
          while (i>=0) {
              //std::cout<<i<<"\n";
              if (r[i]!='0') {
                  nonz=true;
              }
              if (nonz || (i<long(dpos))) {
                  if (re.size()==0 && r[i]=='.') {
                      // swallow decimal dot, if only 0 folowed
                  } else {
                      re=r[i]+re;
                  }
              }
              i--;
          }
          return re;
      }

  }
  return r;
}


std::string cgBytesToStr(double bytes){
    double data=bytes;
  std::string form="%.0lf";
  std::string res=cgFormat(form,data);
  form="%.3lf";
  if (fabs(data)>=1024.0) res=cgFormat(form,data/1024.0)+" k";
  if (fabs(data)>=1024.0*1024.0) res=cgFormat(form,data/(1024.0*1024.0))+" M";
  if (fabs(data)>=1024.0*1024.0*1024.0) res=cgFormat(form,data/(1024.0*1024.0*1024.0))+" ";
  if (fabs(data)>=1024.0*1024.0*1024.0*1024.0) res=cgFormat(form,data/(1024.0*1024.0*1024.0*1024.0))+" G";
  if (fabs(data)>=1024.0*1024.0*1024.0*1024.0*1024.0) res=cgFormat(form,data/(1024.0*1024.0*1024.0*1024.0*1024.0))+" T";
  if (fabs(data)>=1024.0*1024.0*1024.0*1024.0*1024.0*1024.0) res=cgFormat(form,data/(1024.0*1024.0*1024.0*1024.0*1024.0*1024.0))+" E";
  if (fabs(data)==0) res="0 ";
  return res+"Bytes";
}


std::string cgFloatToStrFmt(double data, const std::string& format){
  char st[512];
  sprintf(st, format.c_str(), data);
  return st;
}

std::string cgIntToStrFmt(long data, const std::string & format){
  char st[512];
  sprintf(st, format.c_str(), data);
  return st;
}

std::string cgUIntToStrFmt(unsigned long data, const std::string & format){
  char st[512];
  sprintf(st, format.c_str(), data);
  return st;
}

std::string chartostr(char data){
  std::ostringstream ost;
  ost<<data;
  return ost.str();
}

std::string cgBoolToStr(bool data){
  if (data) return "true";
  return "false";
}

bool cgStrToBool(const std::string & data){
    std::string d=cgToLower(data);
  if (d=="true") return true;
  if (d=="t") return true;
  if (d=="1") return true;
  if (d=="j") return true;
  if (d=="y") return true;
  if (d=="yes") return true;
  if (d=="ja") return true;
  return false;
}


std::string cgFormat(const std::string & templ, ...){
  va_list ap;
  char buffer[4096];
  va_start (ap, templ);
  vsprintf (buffer, templ.c_str(), ap);
  va_end (ap);
  std::string ret(buffer);
  return ret;
}

double cgStrToFloat(const std::string & data) {
    char* p;
    double result=strtod(data.c_str(), &p);
    if (result==0 && p==data.c_str())  {
        throw std::runtime_error(cgFormat("could not convert '%s' to a double", data.c_str()));
    }
    std::string tail=p;
    if (tail.size()>0 && !cgOnlySpace(tail)) {
        throw std::runtime_error(cgFormat("could not convert '%s' to a double", data.c_str()));
    }
    return result;
}


std::string cgToLower(const std::string& s){
  std::string d;
  d="";
  if (s.length()>0) {
    for (unsigned long i=0; i<s.length(); i++) {
        d+=tolower(s[i]);
    }
  }
  return d;
}

std::string cgToUpper(const std::string& s){
  std::string d;
  d="";
  if (s.length()>0) {
    for (unsigned long i=0; i<s.length(); i++) {
        d+=toupper(s[i]);
    }
  }
  return d;
}


bool cgOnlySpace(const std::string& text) {
  if (text.size()>0) {
    for (size_t i=0; i<text.size(); i++)
      if (text[i]>32) return false;
  }
  return true;
}


void cgDrawText(cairo_t* cr, int xx, int yy, int m_width, int m_height, const std::string& m_text, const std::string& m_fontFace, float m_fontSize, bool m_italic, bool m_bold, CGColor m_textColor, float m_lineSpacing, cgAlignment m_horizontalAlignment, cgAlignment m_verticalAlignment)
{
    cairo_text_extents_t extents;
    cairo_select_font_face (cr, m_fontFace.c_str(), (m_italic)?CAIRO_FONT_SLANT_ITALIC:CAIRO_FONT_SLANT_NORMAL, (m_bold)?CAIRO_FONT_WEIGHT_BOLD:CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, m_fontSize);

    std::list<std::string> lines;
    std::string l;
    float maxH=0, maxW=0, sumH=0;
    for (size_t i=0; i<m_text.size(); i++) {
        if (m_text[i]!='\n') {
            l.push_back(m_text[i]);
        } else {
            lines.push_back(l);
            cairo_text_extents(cr, l.c_str(), &extents);
            if (extents.width>maxW) maxW=extents.width;
            cairo_text_extents(cr, std::string(l+"Aq").c_str(), &extents);
            if (extents.height>maxH) maxH=extents.height;
            sumH=sumH+extents.height;
            l.clear();
        }
    }
    if (l.size()>0) {
        cairo_text_extents(cr, l.c_str(), &extents);
        if (extents.width>maxW) maxW=extents.width;
        cairo_text_extents(cr, std::string(l+"Aq").c_str(), &extents);
        if (extents.height>maxH) maxH=extents.height;
        sumH=sumH+extents.height*m_lineSpacing;

        lines.push_back(l);
    }





    float y = yy- extents.y_bearing;
    if (m_verticalAlignment==cgalBottom) {
        y = (yy+m_height)-sumH - extents.y_bearing;
    } else if (m_verticalAlignment==cgalCenter) {
        y = (yy+m_height)/2-sumH/2 - extents.y_bearing;
    }

    for (std::list<std::string>::const_iterator it=lines.begin(); it!=lines.end(); ++it) {
        cairo_text_extents (cr, (*it).c_str(), &extents);
        float x = xx;
        if (m_horizontalAlignment==cgalRight) {
            x=xx+m_width-extents.width;
        } else if (m_horizontalAlignment==cgalCenter) {
            x=(xx+m_width)/2-extents.width/2;
        }


        m_textColor.cairo_set_source(cr);
        cairo_move_to (cr, x,y);
        cairo_show_text (cr, (*it).c_str());
        y=y+extents.height*m_lineSpacing;
    }
}


std::ostream &operator<<(std::ostream &stream, const CGColor &matrix)
{
    stream<<matrix.toString()<<"["<<(int)matrix.r<<", "<<(int)matrix.g<<", "<<(int)matrix.b<<", "<<(int)matrix.a<<"]";
    return stream;
}
