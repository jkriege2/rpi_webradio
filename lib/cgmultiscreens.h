#ifndef CGMULTISCREENS_H
#define CGMULTISCREENS_H

#include "cgscreen.h"
#include <vector>

class CGMultiScreens : public CGScreen
{
    public:
        explicit CGMultiScreens(CGWidget* parent=NULL);
        explicit CGMultiScreens(const fbcairo_context* context, CGWidget* parent=NULL);
        explicit CGMultiScreens(int width, int height, CGWidget* parent=NULL);
        virtual ~CGMultiScreens();


        virtual void paint(cairo_t *c) const;

        virtual void resize(int width, int height);

        virtual void clear();
        CGScreen* currentScreen() const;
        inline int currentScreenID() const {
            return m_currentScreen;
        }
        void nextScreen();
        void previousScreen();
        void setCurrentScreen(int i);
        void setCurrentScreen(CGScreen* s);
        int indexOf(CGScreen* s) const;
        virtual void addScreen(CGScreen* screen);
        virtual CGScreen* addScreen();
        CGScreen* screen(int idx);
        inline int count() const {
            return m_screens.size();
        }
        virtual void setPropsFromPalette(CGPalette *palette);
    protected:
        std::vector<CGScreen*> m_screens;
        int m_currentScreen;
};

#endif // CGMULTISCREENS_H
