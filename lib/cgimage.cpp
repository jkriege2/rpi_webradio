#include "cgimage.h"

CGImage::CGImage(CGWidget *parent):
    CGFrame(parent)
{
    img_surface=NULL;
    img_w=img_h=0;
    m_image_file="";
    m_imageOffset=1;
    m_imageScaled=smScaled;
//    m_verticalAlignment=cgalLeft;
//    m_horizontalAlignment=cgalTop;
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setPropsFromDefaultPalette();
}

CGImage::CGImage(int x, int y, int width, int height, const std::string &image_file, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    img_surface=NULL;
    img_w=img_h=0;
    m_imageOffset=1;
    m_imageScaled=smScaled;
//    m_verticalAlignment=cgalLeft;
//    m_horizontalAlignment=cgalTop;
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setImagePNG(image_file);
    setPropsFromDefaultPalette();
}

CGImage::CGImage(int x, int y, int width, int height, CGWidget *parent):
    CGFrame(x,y,width,height,parent)
{
    img_surface=NULL;
    img_w=img_h=0;
    m_imageOffset=1;
    m_image_file="";
    m_imageScaled=smScaled;
//    m_verticalAlignment=cgalLeft;
//    m_horizontalAlignment=cgalTop;
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setPropsFromDefaultPalette();

}

CGImage::CGImage(const std::string &image_file, CGWidget *parent):
    CGFrame(parent)
{
    img_surface=NULL;
    img_w=img_h=0;
    m_imageOffset=1;
    m_imageScaled=smScaled;
//    m_verticalAlignment=cgalLeft;
//    m_horizontalAlignment=cgalTop;
    setFrameWidth(0);
    setFrameColor(CGColor::ccTransparent);
    setBackgroundColor(CGColor::ccTransparent);
    setImagePNG(image_file);
    setPropsFromDefaultPalette();
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
    }
    if (m_image_file.size()>0) {
        img_surface = cairo_image_surface_create_from_png(m_image_file.c_str());
        img_w = cairo_image_surface_get_width(img_surface);
        img_h = cairo_image_surface_get_height(img_surface);
    }
    if (resize) resizeToImageSize();

}

void CGImage::paint(cairo_t *c) const
{
    CGFrame::paint(c);

    if (img_surface && img_w>0 && img_h>0){
        float offx=m_imageOffset+m_frameWidth;
        float offy=m_imageOffset+m_frameWidth;
        float target_width=m_width-offx*2;
        float target_height=m_height-offy*2;

        float scalex=1;
        float scaley=1;

        if (m_imageScaled==CGImage::smScaled) {
            scalex=target_width/float(img_w);
            scaley=target_height/float(img_h);
        } else if (m_imageScaled==CGImage::smShrinkOnly) {
            scalex=std::min(1.0f,target_width/float(img_w));
            scaley=std::min(1.0f,target_height/float(img_h));
        } else if (m_imageScaled==CGImage::smExpandOnly) {
            scalex=std::max(1.0f,target_width/float(img_w));
            scaley=std::max(1.0f,target_height/float(img_h));
        }

        //float target_img_width=scalex*target_width;
        //float target_img_height=scaley*target_height;

        float imgoffx=0;
        float imgoffy=0;

        int ixoff=0, iyoff=0;

//        if (m_horizontalAlignment==cgalLeft) imgoffx=0;
//        else if (m_horizontalAlignment==cgalCenter) { imgoffx=(target_width-target_img_width)/2.0; ixoff=0;}//-img_w/2.0; }
//        else if (m_horizontalAlignment==cgalRight) { imgoffx=target_width-target_img_width; ixoff=0;}//-img_w; }

//        if (m_verticalAlignment==cgalTop) imgoffy=0;
//        else if (m_verticalAlignment==cgalCenter) imgoffy=(target_height-target_img_height)/2.0;
//        else if (m_verticalAlignment==cgalBottom) imgoffy=target_height-target_img_height;

        //std::cout<<m_image_file<<"  off="<<offx<<","<<offy<<"   imgoff="<<imgoffx<<","<<imgoffy<<"   scale="<<scalex<<","<<scaley<<"   target="<<target_width<<","<<target_height<<"   target_img="<<target_img_width<<","<<target_img_height<<std::endl;

        cairo_save(c);
            cairo_translate(c, offx,offy);
            cairo_rectangle(c, 0,0, target_width,target_height);
            cairo_clip (c);

            cairo_translate(c, imgoffx,imgoffy);
            cairo_scale(c, scalex, scaley);
            cairo_translate(c, ixoff,iyoff);

            cairo_set_source_surface(c, img_surface, 0,0);

            cairo_paint (c);
        cairo_restore(c);

    }

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
