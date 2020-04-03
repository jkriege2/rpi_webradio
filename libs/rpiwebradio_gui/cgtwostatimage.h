#ifndef CGTWOSTATEIMAGE_H
#define CGTWOSTATEIMAGE_H

#include <string>
#include "cgimage.h"

/** \brief a widget, which can display one out of two possible images (controlled by setState() ) */
class CGTwoStateImage : public CGImage
{
    public:

        explicit CGTwoStateImage(CGWidget* parent=NULL);
        explicit CGTwoStateImage(int x, int y, int width, int height, const std::string& image_file, const std::string& image_file2, CGWidget* parent=NULL);
        explicit CGTwoStateImage(int x, int y, int width, int height, CGWidget* parent=NULL);
        explicit CGTwoStateImage(const std::string& image_file, const std::string& image_file2, CGWidget* parent=NULL);
        virtual ~CGTwoStateImage();

        void setImagePNGFalse(const std::string& image_file, bool resize=false);
        inline void setImagePNGTrue(const std::string& image_file, bool resize=false) {
            setImagePNG(image_file, resize);
        }
        void setImageSymbolFalse(CGSymbol::Symbols symbol) {
            setImageSymbolFalse(CGSymbol(symbol));
        }

        void setImageSymbolFalse(const CGSymbol& symbol);
        inline void setImageSymbolTrue(const CGSymbol& symbol) {
            setImageSymbol(symbol);
        }
        void setImageSymbolTrue(CGSymbol::Symbols symbol) {
            setImageSymbol(CGSymbol(symbol));
        }


        inline CGSymbol imageSymbolTrue() const {
            return imageSymbol();
        }

        inline std::string imageFileFalse() const {
            return m_image_file_false;
        }

        inline std::string imageFileTrue() const {
            return imageFile();
        }

        virtual void paint(cairo_t *c)  override;

        virtual void clear() override;
        virtual void resizeToImageSize() override;

        inline bool state() const {
            return m_state;
        }
        inline void setState(bool state) {
            m_state=state;
        }
        inline void toggleState() {
            m_state=!m_state;
        }

    protected:
        std::string m_image_file_false;
        CGSymbol img_symbol_false;

        int img_false_w;
        int img_false_h;
        cairo_surface_t *img_false_surface;
        bool m_state;
};

#endif // CGTWOSTATEIMAGE_H
