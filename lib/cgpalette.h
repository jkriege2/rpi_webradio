#ifndef CGPALETTE_H
#define CGPALETTE_H

#include "cgbasics.h"
#include <string>

/** \brief a CGPalette defines the appearance (colors, ine-widths, fonts, ...) of an application */
class CGPalette
{
    public:
        CGPalette();
        ~CGPalette();

        static CGPalette* defaultPalette();

        enum ColorRoles {
            crBackground,
            crText,
            crIcon,
            crIconHighlight,
            crIconShadow,
            crIconBackground,
            crBright,
            crDim,
            crDark,
            crButton,
            crButtonIconOrText,
            crButtonFrame,
            crInactiveButton,
            crInactiveButtonIconOrText,
            crInactiveButtonFrame,
            crSelection,
            crSelectionIconOrText,
            crFrame,
            crFocusedFrame,
            crHighlight,
            crTextOnHighlight,
            crTitleBackground,
            crTitleText,
        };

        enum SizeRoles {
            srFrameWidth,
            srFocusedFrameWidth,
            srIconLineWidth,
            srFontSize
        };

        enum NameRoles {
            nrFontName
        };

        CGColor color(ColorRoles role) const;
        float size(SizeRoles role) const;
        std::string name(NameRoles role) const;



    protected:
        static CGPalette* defInstance;

        CGColor backgroundColor;
        CGColor textColor;
        CGColor iconColor;
        CGColor iconHighlightColor;
        CGColor iconShadowColor;
        CGColor iconBackgroundColor;
        CGColor brightColor;
        CGColor dimColor;
        CGColor darkColor;
        CGColor buttonColor;
        CGColor buttonFrameColor;
        CGColor buttonIconOrTextColor;
        CGColor inactiveButtonColor;
        CGColor inactiveButtonFrameColor;
        CGColor inactiveButtonIconOrTextColor;
        CGColor selectionColor;
        CGColor selectedIconOrTextColor;
        CGColor frameColor;
        CGColor focusedFrameColor;
        CGColor highlightColor;
        CGColor textOnHighlightColor;

        CGColor titleBackgroundColor;
        CGColor titleTextColor;

        float frameWidth;
        float iconLineWidth;
        float focusedFrameWidth;
        float fontSize;
        std::string fontName;
};

#endif // CGPALETTE_H
