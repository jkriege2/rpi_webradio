#include "cgprecomp.h"
#include "cgpalette.h"

CGPalette* CGPalette::defInstance=NULL;

CGPalette::CGPalette()
{
    fontSize=15;
    fontName="sans";
    frameWidth=1;
    focusedFrameWidth=1;
    iconLineWidth=2;

    backgroundColor=CGColor::ccBlack;
    textColor=CGColor::ccWhite;
    iconColor=CGColor(16,12,39);
    iconHighlightColor=CGColor("lightsteelblue");
    iconShadowColor=CGColor("steelblue");
    iconBackgroundColor=backgroundColor;

    brightColor=CGColor::ccGrey75;
    dimColor=CGColor("gray50");
    darkColor=CGColor::ccGrey25;

    buttonColor=dimColor;
    buttonIconOrTextColor=CGColor::ccGray10;
    buttonFrameColor=buttonIconOrTextColor;

    inactiveButtonColor=darkColor;
    inactiveButtonIconOrTextColor=dimColor;
    inactiveButtonFrameColor=inactiveButtonIconOrTextColor;

    selectionColor=CGColor("powderblue");
    selectedIconOrTextColor=CGColor("darkblue");

    highlightColor=CGColor("royalblue");
    textOnHighlightColor=CGColor::ccWhite;

    frameColor=CGColor("navy(16)");
    focusedFrameColor=CGColor("limegreen");

    titleBackgroundColor=dimColor;
    titleTextColor=CGColor::ccBlack;


}

CGPalette::~CGPalette()
{

}

CGPalette *CGPalette::defaultPalette()
{
    if (!defInstance) defInstance=new CGPalette();
    return defInstance;
}

CGColor CGPalette::color(CGPalette::ColorRoles role) const
{
    switch (role) {
        case crBackground:
            return backgroundColor;
        case crText:
            return textColor;
        case crIcon:
            return iconColor;
        case crIconHighlight:
            return iconHighlightColor;
        case crIconShadow:
            return iconShadowColor;
        case crIconBackground:
            return iconBackgroundColor;
        case crBright:
            return brightColor;
        case crDim:
            return dimColor;
        case crDark:
            return darkColor;
        case crButton:
            return buttonColor;
        case crButtonIconOrText:
            return buttonIconOrTextColor;
        case crButtonFrame:
            return buttonFrameColor;
        case crInactiveButton:
            return inactiveButtonColor;
        case crInactiveButtonFrame:
            return inactiveButtonFrameColor;
        case crInactiveButtonIconOrText:
            return inactiveButtonIconOrTextColor;
        case crSelection:
            return selectionColor;
        case crSelectionIconOrText:
            return selectedIconOrTextColor;
        case crFrame:
            return frameColor;
        case crHighlight:
            return highlightColor;
        case crTextOnHighlight:
            return textOnHighlightColor;
        case crTitleBackground:
            return titleBackgroundColor;
        case crTitleText:
            return titleTextColor;
        case crFocusedFrame:
            return focusedFrameColor;
        default:
            return CGColor::ccBlack;
    }
    return CGColor::ccBlack;
}

float CGPalette::size(CGPalette::SizeRoles role) const
{
    switch (role) {
        case srFrameWidth:
            return frameWidth;
        case srIconLineWidth:
            return iconLineWidth;
        case srFocusedFrameWidth:
            return focusedFrameWidth;
        case srFontSize:
            return fontSize;
        default:
            return 0;
    }
    return 0;
}

std::string CGPalette::name(CGPalette::NameRoles role) const
{
    switch (role) {
        case nrFontName:
            return fontName;
        default:
            return std::string();
    }
    return std::string();
}

