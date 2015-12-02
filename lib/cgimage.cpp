#include "cgimage.h"

CGImage::CGImage(CGWidget *parent):
    CGFrame(parent)
{
    m_keepAspectRatio=true;
    img_surface=NULL;
    img_w=img_h=0;
    m_image_file="";
    m_imageOffset=1;
    m_imageScaled=smScaled;
//    m_verticalAlignment=cgalLeft;
//    m_horizontalAlignment=cgalTop;
    setPropsFromDefaultPalette();
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
}

CGImage::CGImage(int x, int y, int width, int height, const std::string &image_file, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    m_keepAspectRatio=true;
    img_surface=NULL;
    img_w=img_h=0;
    m_imageOffset=1;
    m_imageScaled=smScaled;
//    m_verticalAlignment=cgalLeft;
//    m_horizontalAlignment=cgalTop;
    setPropsFromDefaultPalette();
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setImagePNG(image_file);
}

CGImage::CGImage(int x, int y, int width, int height, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    m_keepAspectRatio=true;
    img_surface=NULL;
    img_w=img_h=0;
    m_imageOffset=1;
    m_image_file="";
    m_imageScaled=smScaled;
//    m_verticalAlignment=cgalLeft;
//    m_horizontalAlignment=cgalTop;
    setPropsFromDefaultPalette();
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);

}

CGImage::CGImage(const std::string &image_file, CGWidget *parent):
    CGFrame(parent)
{
    m_keepAspectRatio=true;
    img_surface=NULL;
    img_w=img_h=0;
    m_imageOffset=1;
    m_imageScaled=smScaled;
//    m_verticalAlignment=cgalLeft;
//    m_horizontalAlignment=cgalTop;
    setPropsFromDefaultPalette();
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setImagePNG(image_file);
}

CGImage::~CGImage()
{
    clear();
}

void CGImage::setImagePNG(const std::string &image_file, bool resize)
{
    m_image_file=image_file;
    if (img_surface) {
        img_w=img_h=0;
        cairo_surface_destroy(img_surface);
        img_surface=NULL;
    }
    if (m_image_file.size()>0) {
        img_symbol.setSymbol(CGSymbol::iNone);
        img_surface = cairo_image_surface_create_from_png(m_image_file.c_str());
        img_w = cairo_image_surface_get_width(img_surface);
        img_h = cairo_image_surface_get_height(img_surface);
    }
    if (resize) resizeToImageSize();

}

void CGImage::setImageSymbol(const CGSymbol & symbol)
{
    setImagePNG("");
    img_symbol=symbol;
}

void CGImage::paintImage(cairo_t *c, cairo_surface_t *img_surface, int img_w, int img_h, const CGSymbol& symbol) const
{
    //std::cout<<"CGImage::paintImage: 0 "<<symbol.symbol()<<" -> "<<img_w<<","<<img_h<<"\n";
    if (!symbol.isNoneSymbol()  || (img_w>0 && img_h>0)) {
        if (!symbol.isNoneSymbol()) {
            img_w=width()-2*border();
            img_h=symbol.heightForWidth(img_w);
        }
        float offx=m_imageOffset+m_frameWidth;
        float offy=m_imageOffset+m_frameWidth;
        float target_width=m_width-offx*2;
        float target_height=m_height-offy*2;

        float tw;
        float th;

        if (m_keepAspectRatio) {
            if (m_imageScaled==CGImage::smScaled) {
                float scale= std::min(target_width/float(img_w), target_height/float(img_h));
                tw=scale*img_w;
                th=scale*img_h;
            } else if (m_imageScaled==CGImage::smShrinkOnly) {
                float scale= std::min(std::min<float>(img_w, target_width)/img_w,std::min<float>(img_h, target_height)/img_h);
                tw=scale*img_w;
                th=scale*img_h;
            } else if (m_imageScaled==CGImage::smExpandOnly) {
                float scale= std::min(std::max<float>(img_w, target_width)/img_w,std::max<float>(img_h, target_height)/img_h);
                tw=scale*img_w;
                th=scale*img_h;
            } else {
                tw=img_w;
                th=img_h;
            }
        } else {
            if (m_imageScaled==CGImage::smScaled) {
                tw=target_width;
                th=target_height;
            } else if (m_imageScaled==CGImage::smShrinkOnly) {
                tw=std::min<float>(img_w, target_width);
                th=std::min<float>(img_h, target_height);
            } else if (m_imageScaled==CGImage::smExpandOnly) {
                tw=std::max<float>(img_w, target_width);
                th=std::max<float>(img_h, target_height);
            } else {
                tw=img_w;
                th=img_h;
            }
        }
        //std::cout<<"CGImage::paintImage: 1 "<<symbol.isNoneSymbol()<<" -> "<<img_w<<","<<img_h<<"\n";
        if (!symbol.isNoneSymbol()) {
            symbol.paint(c, offx, offy, tw, th);
        } else if (img_surface){
            cgDrawImage(c, offx, offy, tw, th, img_surface, img_w, img_h);
        }
    }
}

void CGImage::paint(cairo_t *c) const
{
    CGFrame::paint(c);
    paintImage(c, img_surface, img_w, img_h, img_symbol);
}

void CGImage::clear()
{
    setImagePNG("");
}

void CGImage::setPropsFromPalette(CGPalette *palette)
{
    CGFrame::setPropsFromPalette(palette);
    if (palette) {

    }
}

void CGImage::resizeToImageSize()
{
    resize(img_w,img_h);
}
