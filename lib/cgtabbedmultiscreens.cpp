#include "cgtabbedmultiscreens.h"




CGTabbedMultiScreens::CGTabbedMultiScreens(CGWidget *parent):
    CGMultiScreens(parent)
{
    setPropsFromDefaultPalette();
}

CGTabbedMultiScreens::CGTabbedMultiScreens(const fbcairo_context *context, CGWidget *parent):
    CGMultiScreens(context, parent)
{
    setPropsFromDefaultPalette();
}

CGTabbedMultiScreens::CGTabbedMultiScreens(int width, int height, CGWidget *parent):
    CGMultiScreens(width, height, parent)
{
    setPropsFromDefaultPalette();
}

CGTabbedMultiScreens::~CGTabbedMultiScreens()
{
}

void CGTabbedMultiScreens::paint(cairo_t *c) const
{
    cairo_save(c);
        cairo_translate(c, 0, 0);
        cgRect<int> remainingRect;
        paintTabBar(c, m_width, m_height, this, &remainingRect);
        //remainingRect.cairo_clip(c);
        remainingRect.cairo_translateTopLeft(c);
        CGMultiScreens::paint(c);
    cairo_restore(c);
}

void CGTabbedMultiScreens::addScreen(CGScreen *screen, const std::string &name)
{
    CGMultiScreens::addScreen(screen);
    m_screenNames.push_back(name);
}

CGScreen *CGTabbedMultiScreens::addScreen(const std::string &name)
{
    CGScreen * s=CGMultiScreens::addScreen();
    m_screenNames.push_back(name);
    return s;
}

void CGTabbedMultiScreens::addScreen(CGScreen *screen)
{
    addScreen(screen, cgFormat("screen #%d", count()));
}

CGScreen *CGTabbedMultiScreens::addScreen()
{
    return addScreen(cgFormat("screen #%d", count()));
}

std::string CGTabbedMultiScreens::screenName(int idx) const
{
    if (idx>=0 && (size_t)idx<m_screenNames.size()) return m_screenNames[idx];
    return std::string();
}

cgSize<unsigned int> CGTabbedMultiScreens::sizeForChildren() const
{
    cgRect<int> r=getRemainingRect(width()-border()*2, height()-border()*2);
    //std::cout<<"CGTabbedMultiScreens::sizeForChildren():"<<width()<<","<<height()<<" -> "<<r<<" -> "<<r.size<unsigned int>()<<"\n";
    return r.size<unsigned int>();
}

void CGTabbedMultiScreens::setPropsFromPalette(CGPalette *palette)
{
    CGMultiScreens::setPropsFromPalette(palette);
    if (palette) {
        setTabPropsFromPalette(palette);
    }
}

std::string CGTabbedMultiScreens::tabName(int idx) const
{
    return screenName(idx);
}

int CGTabbedMultiScreens::tabCount() const
{
    return count();
}

bool CGTabbedMultiScreens::tabIsActive(int idx) const
{
    return (idx>=0) && currentScreenID()==idx;
}
