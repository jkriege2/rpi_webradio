#include "cgtwostatimage.h"

CGTwoStateImage::CGTwoStateImage(CGWidget *parent):
    CGImage(parent)
{
    m_state=true;
    img_false_surface=NULL;
    img_false_w=img_false_h=0;
    m_image_file_false="";
}

CGTwoStateImage::CGTwoStateImage(int x, int y, int width, int height, const std::string &image_file, const std::string& image_file2, CGWidget *parent):
    CGImage(x,y,width,height,image_file,parent)
{
    m_state=true;
    img_false_surface=NULL;
    img_false_w=img_false_h=0;
    m_image_file_false="";
    setImagePNGFalse(image_file2);
}

CGTwoStateImage::CGTwoStateImage(int x, int y, int width, int height, CGWidget *parent):
    CGImage(x,y,width,height,parent)
{
    m_state=true;
    img_false_surface=NULL;
    img_false_w=img_false_h=0;
    m_image_file_false="";
}

CGTwoStateImage::CGTwoStateImage(const std::string &image_file, const std::string& image_file2, CGWidget *parent):
    CGImage(image_file,parent)
{
    m_state=true;
    img_false_surface=NULL;
    img_false_w=img_false_h=0;
    m_image_file_false="";
    setImagePNGFalse(image_file2);
}

CGTwoStateImage::~CGTwoStateImage()
{
    clear();
}

void CGTwoStateImage::setImagePNGFalse(const std::string &image_file, bool resize)
{
    m_image_file_false=image_file;
    if (img_false_surface) {
        img_false_w=img_false_h=0;
        cairo_surface_destroy(img_false_surface);
        img_false_surface=NULL;
    }
    if (m_image_file.size()>0) {
        img_symbol_false.setSymbol(CGSymbol::iNone);
        img_false_surface = cairo_image_surface_create_from_png(m_image_file_false.c_str());
        img_false_w = cairo_image_surface_get_width(img_false_surface);
        img_false_h = cairo_image_surface_get_height(img_false_surface);
    }
    if (resize) resizeToImageSize();

}

void CGTwoStateImage::setImageSymbolFalse(const CGSymbol &symbol)
{
    setImagePNGFalse("");
    img_symbol_false=symbol;
}

void CGTwoStateImage::paint(cairo_t *c)
{
    CGFrame::paint(c);
    if (m_state) paintImage(c, img_surface, img_w, img_h, img_symbol);
    else paintImage(c, img_false_surface, img_false_w, img_false_h, img_symbol_false);
}


void CGTwoStateImage::clear()
{
    setImagePNG("");
    setImagePNGFalse("");
}

void CGTwoStateImage::resizeToImageSize()
{
    resize(std::max<int>(img_w, img_false_w),std::max<int>(img_h, img_false_h));
}

