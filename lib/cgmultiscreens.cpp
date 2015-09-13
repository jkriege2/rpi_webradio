#include "cgmultiscreens.h"


CGMultiScreens::CGMultiScreens(CGWidget *parent):
    CGScreen(parent)
{
    m_currentScreen=0;
    setPropsFromDefaultPalette();
}

CGMultiScreens::CGMultiScreens(const fbcairo_context *context, CGWidget *parent):
    CGScreen(context, parent)
{
    m_currentScreen=0;
    setPropsFromDefaultPalette();
}

CGMultiScreens::CGMultiScreens(int width, int height, CGWidget *parent):
    CGScreen(width, height, parent)
{
    m_currentScreen=0;
    setPropsFromDefaultPalette();
}

CGMultiScreens::~CGMultiScreens()
{
    clear();
}

void CGMultiScreens::paint(cairo_t *c) const
{
    if (currentScreen()) {
        currentScreen()->paint(c);
    }
}

void CGMultiScreens::resize(int width, int height)
{
    for (size_t i=0; i<m_screens.size(); i++) {
        if (m_screens[i]) m_screens[i]->resize(width, height);
    }
}

void CGMultiScreens::clear()
{
    for (size_t i=0; i<m_screens.size(); i++) {
        if (m_screens[i]) delete m_screens[i];
    }
    m_screens.clear();
    m_currentScreen=0;
}

CGScreen *CGMultiScreens::currentScreen() const
{
    if (m_currentScreen>=0 && m_currentScreen<(int64_t)m_screens.size()) {
        return m_screens[m_currentScreen];
    }
    return NULL;
}

void CGMultiScreens::nextScreen()
{
    setCurrentScreen(m_currentScreen+1);
}

void CGMultiScreens::previousScreen()
{
    setCurrentScreen(m_currentScreen-1);
}

void CGMultiScreens::setCurrentScreen(int i)
{
    m_currentScreen=i;
    if (m_currentScreen>(int64_t)m_screens.size()) m_currentScreen=(int64_t)m_screens.size()-1;
    if (m_currentScreen<0) m_currentScreen=0;
}

void CGMultiScreens::setCurrentScreen(CGScreen *s)
{
    for (size_t i=0; i<m_screens.size(); i++) {
        if (m_screens[i]==s) {
            setCurrentScreen(i);
            break;
        }
    }
}

int CGMultiScreens::indexOf(CGScreen *s) const
{
    for (size_t i=0; i<m_screens.size(); i++) {
        if (m_screens[i]==s) {
            return i;
        }
    }
    return -1;
}

void CGMultiScreens::addScreen(CGScreen *screen)
{
    m_screens.push_back(screen);
    screen->setParent(this);
}

CGScreen *CGMultiScreens::addScreen()
{
    CGScreen* s=new CGScreen(width(), height(), this);
    addScreen(s);
    return s;
}

CGScreen *CGMultiScreens::screen(int i)
{
    if (i>=0 && i<count()) {
        return m_screens[i];
    }
    return NULL;
}

void CGMultiScreens::setPropsFromPalette(CGPalette *palette)
{
    CGScreen::setPropsFromPalette(palette);
    for (size_t i=0; i<m_screens.size(); i++) {
        if (m_screens[i]) {
            m_screens[i]->setPropsFromPalette(palette);
        }
    }
}
