#ifndef CGIMAGE_H
#define CGIMAGE_H

#include "cgframe.h"
#include "cgfontprops.h"


class CGImage : public CGFrame//, public CGPropsAlignment
{
    public:
        enum ScaleMode {
            smOriginal=0,
            smScaled=1,
            smShrinkOnly=2,
            smExpandOnly=3
        };

        explicit CGImage(CGWidget* parent=NULL);
        explicit CGImage(int x, int y, int width, int height, const std::string& image_file, CGWidget* parent=NULL);
        explicit CGImage(int x, int y, int width, int height, CGWidget* parent=NULL);
        explicit CGImage(const std::string& image_file, CGWidget* parent=NULL);
        virtual ~CGImage();

        void setImagePNG(const std::string& image_file, bool resize=false);
        inline std::string imageFile() const {
            return m_image_file;
        }

        virtual void paint(cairo_t *c) const;

        inline float imageOffset() const {
            return m_imageOffset;
        }
        inline void setImageOffset(float size) {
            m_imageOffset=size;
        }

        inline ScaleMode imageScaled() const {
            return m_imageScaled;
        }
        inline void setImageScaled(ScaleMode size) {
            m_imageScaled=size;
        }

        void clear();
        void setPropsFromPalette(CGPalette *palette);
        void resizeToImageSize();
    protected:
        std::string m_image_file;
        float m_imageOffset;
        ScaleMode m_imageScaled;

        int img_w;
        int img_h;
        cairo_surface_t *img_surface;
};

#endif // CGIMAGE_H
