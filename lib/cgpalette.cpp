#include "cgpalette.h"

CGPalette* CGPalette::defInstance=NULL;

CGPalette::CGPalette()
{
    fontSize=10;
    fontName="sans";
    frameWidth=1;

    backgroundColor=CGColor::ccBlack;
    textColor=CGColor::ccWhite;

    brightColor=CGColor::ccGrey75;
    dimColor=CGColor("gray50");
    darkColor=CGColor::ccGrey25;

    buttonColor=CGColor::ccGrey50;
    buttonIconOrTextColor=CGColor::ccGray10;

    selectionColor=CGColor("powderblue");
    selectedIconOrTextColor=CGColor("darkblue");

    highlightColor=CGColor("royalblue");
    textOnHighlightColor=CGColor::ccWhite;

    frameColor=CGColor("navy(16)");

    titleBackgroundColor=dimColor;
    titleTextColor=CGColor::ccBlack;


//    std::cout<<"default-palette:\n";
//    std::cout<<"   fontSize = "<<fontSize<<"\n";
//    std::cout<<"   fontName = "<<fontName<<"\n";
//    std::cout<<"   frameWidth = "<<frameWidth<<"\n";
//    std::cout<<"   backgroundColor = "<<backgroundColor<<"\n";
//    std::cout<<"   textColor = "<<textColor<<"\n";
//    std::cout<<"   brightColor = "<<brightColor<<"\n";
//    std::cout<<"   dimColor = "<<dimColor<<"\n";
//    std::cout<<"   darkColor = "<<darkColor<<"\n";
//    std::cout<<"   buttonColor = "<<buttonColor<<"\n";
//    std::cout<<"   buttonIconOrTextColor = "<<buttonIconOrTextColor<<"\n";
//    std::cout<<"   selectionColor = "<<selectionColor<<"\n";
//    std::cout<<"   selectedIconOrTextColor = "<<selectedIconOrTextColor<<"\n";
//    std::cout<<"   highlightColor = "<<highlightColor<<"\n";
//    std::cout<<"   textOnHighlightColor = "<<textOnHighlightColor<<"\n";
//    std::cout<<"   frameColor = "<<frameColor<<"\n";
//    std::cout<<"   titleBackgroundColor = "<<titleBackgroundColor<<"\n";
//    std::cout<<"   titleTextColor = "<<titleTextColor<<"\n";

}

CGPalette::~CGPalette()
{

}

CGPalette *CGPalette::defaultPalette()
{
    if (!defInstance) defInstance=new CGPalette();
    return defInstance;
}

