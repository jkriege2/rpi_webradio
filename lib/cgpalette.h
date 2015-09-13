#ifndef CGPALETTE_H
#define CGPALETTE_H

#include "cgbasics.h"
#include <string>
class CGPalette
{
    public:
        CGPalette();
        ~CGPalette();

        static CGPalette* defaultPalette();

        CGColor backgroundColor;
        CGColor textColor;
        CGColor brightColor;
        CGColor dimColor;
        CGColor darkColor;
        CGColor buttonColor;
        CGColor buttonIconOrTextColor;
        CGColor selectionColor;
        CGColor selectedIconOrTextColor;
        CGColor frameColor;
        CGColor highlightColor;
        CGColor textOnHighlightColor;

        CGColor titleBackgroundColor;
        CGColor titleTextColor;

        float frameWidth;
        float fontSize;
        std::string fontName;

    protected:
        static CGPalette* defInstance;
};

#endif // CGPALETTE_H
