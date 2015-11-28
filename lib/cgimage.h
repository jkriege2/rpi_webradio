#ifndef CGIMAGE_H
#define CGIMAGE_H

#include "cgframe.h"
#include "cgfontprops.h"

/** \brief awidget, which can display an image */
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

        inline bool keepAspectRatio() const {
            return m_keepAspectRatio;
        }
        inline void setKeepAspectRatio(bool enabled) {
            m_keepAspectRatio=enabled;
        }

        void clear();
        void setPropsFromPalette(CGPalette *palette);
        void resizeToImageSize();
    protected:
        std::string m_image_file;
        float m_imageOffset;
        ScaleMode m_imageScaled;
        bool m_keepAspectRatio;

        int img_w;
        int img_h;
        cairo_surface_t *img_surface;
};

#endif // CGIMAGE_H
