#include "cgprecomp.h"
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

void CGMultiScreens::paint(cairo_t *c)
{
    if (currentScreen()) {
        currentScreen()->paint(c);
    }
}

void CGMultiScreens::resize(unsigned int width, unsigned int height)
{
    CGScreen::resize(width, height);
    for (size_t i=0; i<m_screens.size(); i++) {
        if (m_screens[i]) m_screens[i]->resize(sizeForChildren());
    }
}

void CGMultiScreens::clear()
{
    for (size_t i=0; i<m_screens.size(); i++) {
        if (m_screens[i]) delete m_screens[i];
    }
    m_screens.clear();
    setCurrentScreen(0);
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
    int oldcs=m_currentScreen;
    m_currentScreen=i;
    if (m_currentScreen>(int64_t)m_screens.size()) m_currentScreen=(int64_t)m_screens.size()-1;
    if (m_currentScreen<0) m_currentScreen=0;
    if (oldcs!=m_currentScreen) {
        if (screen(oldcs)) screen(oldcs)->hideScreen();
        if (screen(m_currentScreen)) screen(m_currentScreen)->showScreen();
    }

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
    if (!screen) return;
    m_screens.push_back(screen);
    screen->setParent(this);
    screen->resize(sizeForChildren());
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

void CGMultiScreens::event(CGEvent *e)
{
    if (currentScreen()) currentScreen()->event(e);
    /*if (!e->accepted()) {
        CGScreen::event(e);
    }*/
}

void CGMultiScreens::showScreen()
{
    if (currentScreen()) currentScreen()->showScreen();
}

void CGMultiScreens::hideScreen()
{
    if (currentScreen()) currentScreen()->hideScreen();
}
