#ifndef CGLAYOUT_H
#define CGLAYOUT_H

#include <string>
#include <map>
#include <vector>
#include <boost/noncopyable.hpp>
#include "cgbasics.h"

class CGWidget; // forward

/** \brief can be used to lay out widgets inside another widget */
class CGLayout: private boost::noncopyable
{
    public:
        CGLayout(CGWidget* parent);
        virtual ~CGLayout();
        /** \brief returns the parent widget */
        inline CGWidget* parent() const { return m_parent; }
        /** \brief layout all the widgets assigned to this layout */
        virtual void layoutWidgets() =0;
        /** \brief minimum size required to lay out all widgets, i.e. accumulated minimum size of all widgets, this does not mind the spacing!!! */
        virtual cgSize<unsigned int> minimumSizeFromWidgets() const =0;
        /** \brief minimum size required to lay out all widgets, i.e. accumulated minimum size of all widgets, this does mind the spacing!!! */
        virtual cgSize<unsigned int> minimumSize() const ;

        /** \brief set the spacing between widgets in pixels */
        void setSpacing(unsigned int spacing);
        /** \brief return the spacing between widgets in pixels */
        inline unsigned int spacing() const { return m_spacing; }
    protected:
        /** \brief set the parent widget of this widget */
        virtual void setParent(CGWidget* p);
        CGWidget* m_parent;
        unsigned int m_spacing;
        CGLayout() = delete;
        CGLayout(const CGLayout&) = delete;

        friend class CGWidget;
};

/** \brief can be used to lay out widgets inside another widget in a linear fashion */
class CGLinearLayout: public CGLayout
{
    public:
        enum OtherAxisSizeMode {
            oasmAsSet,          /**< son't resize the widget */
            oasmAvailableSpace, /**< use all available space */
        };

        explicit CGLinearLayout(CGWidget* parent, cgDirection direction=cgdHorizontal);
        virtual ~CGLinearLayout();
        /** \brief return the layout direction */
        inline cgDirection direction() const {
            return m_direction;
        }
        /** \brief set the layout direction */
        inline void setDirection(cgDirection dir) {
            m_direction=dir;
        }
        /** \brief add a widget to the layout, \a stretch \c >0 specifies a stretch-factor for the widget */
        void addWidget(CGWidget* widget, int stretch=-1);
        /** \brief clear all widgets from the layout */
        void clearWidgets();

        /** \copydoc  CGLayout::layoutWidgets() */
        virtual void layoutWidgets();
        /** \copydoc  CGLayout::minimumSize() */
        virtual cgSize<unsigned int> minimumSizeFromWidgets() const ;
        /** \brief minimum size required to lay out all widgets, i.e. accumulated minimum size of all widgets, this does mind the spacing!!! */
        virtual cgSize<unsigned int> minimumSize() const ;
        /** \brief how to resize the other axis (y-axis for \c m_direction==cgdHorizontal , or x-axis for \c m_direction==cgdVertical ) */
        inline OtherAxisSizeMode otherAxisSizeMode() const {
            return m_otherAxisSizeMode;
        }
        /** \brief set how to resize the other axis (y-axis for \c m_direction==cgdHorizontal , or x-axis for \c m_direction==cgdVertical ) */
        void setOtherAxisSizeMode(OtherAxisSizeMode mode);

    protected:
        struct layoutData {
            inline layoutData(): widget(NULL), stretch(-1) {}
            CGWidget* widget;
            int stretch;
        };

        cgDirection m_direction;
        std::vector<layoutData> m_data;
        OtherAxisSizeMode m_otherAxisSizeMode;

};

#endif // CGLAYOUT_H
