#ifndef CGTABBEDMULTISCREENS_H
#define CGTABBEDMULTISCREENS_H

#include "cgmultiscreens.h"
#include <vector>
#include "cgtabmixin.h"

/** \brief a multi-screen-manager with tabs that indicate which screen is currently used */
class CGTabbedMultiScreens : public CGMultiScreens, public CGTabMixin
{
    public:
        explicit CGTabbedMultiScreens(CGWidget* parent=NULL);
        explicit CGTabbedMultiScreens(const fbcairo_context* context, CGWidget* parent=NULL);
        explicit CGTabbedMultiScreens(int width, int height, CGWidget* parent=NULL);
        virtual ~CGTabbedMultiScreens();

        virtual void paint(cairo_t *c) const;

        virtual void resize(int width, int height);

        void addScreen(CGScreen* screen, const std::string& name);
        CGScreen* addScreen(const std::string& name);
        void addScreen(CGScreen* screen);
        CGScreen* addScreen();
        std::string screenName(int idx) const;

        virtual void setPropsFromPalette(CGPalette *palette);

        virtual std::string tabName(int idx) const;
        virtual int tabCount() const;
        virtual bool tabIsActive(int idx) const;

    protected:
        std::vector<std::string> m_screenNames;


};

#endif // CGTABBEDMULTISCREENS_H
