TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../lib/  \
               ../mpdtools/

SOURCES += main.cpp \
    wrmainscreen.cpp \
    ../lib/framebuffer_cairo_tools.cpp \
    ../lib/cgwidget.cpp \
    ../lib/cgframe.cpp \
    ../lib/cglabel.cpp \
    ../lib/rpi_tools.cpp \
    ../lib/cgbasics.cpp \
    ../lib/cgscreen.cpp \
    ../lib/cgeventqueue.cpp \
    ../lib/cgprogressbar.cpp \
    ../lib/cgfontprops.cpp \
    ../lib/cgtreewidget.cpp \
    ../lib/cgmultiscreens.cpp \
    ../lib/cgtabbedmultiscreens.cpp \
    ../lib/cgpalette.cpp \
    ../lib/cgscrollbar.cpp \
    ../lib/cgimage.cpp \
    ../lib/cgevents.cpp \
    ../lib/rpi_cgevents.cpp \
    ../lib/cgtabmixin.cpp \
    ../lib/cglayout.cpp \
    ../lib/cgapplication.cpp \
    wrradioscreen.cpp \
    ../lib/cgtwostatimage.cpp \
    ../lib/cgsymbol.cpp \
    ../lib/mpd_tools.cpp \
    wrmusicscreen.cpp \
    ../lib/cgdirectorytreewidget.cpp \
    ../mpdtools/mpd_tools.cpp \
    ../wrmpddirectorytreeprovider.cpp \
    wrmpddirectorytreeprovider.cpp \
    ../rpitools/rpi_tools.cpp

HEADERS += \
    wrmainscreen.h \
    ../lib/framebuffer_cairo_tools.h \
    ../lib/cgwidget.h \
    ../lib/cgframe.h \
    ../lib/cglabel.h \
    ../lib/cgbasics.h \
    ../lib/cgscreen.h \
    ../lib/cgeventqueue.h \
    ../lib/cgprogressbar.h \
    ../lib/cglistwidget.h \
    ../lib/cgfontprops.h \
    ../lib/cgtreewidget.h \
    ../lib/cgmultiscreens.h \
    ../lib/cgtabbedmultiscreens.h \
    ../lib/cgpalette.h \
    ../lib/cgscrollbar.h \
    ../lib/cgimage.h \
    ../lib/cgevents.h \
    ../lib/rpi_cgevents.h \
    ../lib/cgtabmixin.h \
    ../lib/cglayout.h \
    ../lib/cgapplication.h \
    wrradioscreen.h \
    ../lib/cgtwostatimage.h \
    ../lib/cgsymbol.h \
    global.h \
    wrmusicscreen.h \
    ../mpdtools/mpd_tools.h \
    ../wrmpddirectorytreeprovider.h \
    wrmpddirectorytreeprovider.h \
    ../lib/cgdirectorytreewidget.h \
    ../lib/cglib.h \
    precomp.h \
    ../lib/cgprecomp.h \
    ../rpitools/rpi_tools.h

DISTFILES += Makefile \
    ../lib/Makefile \
    ../mpdtools/Makefile \
    ../rpitools/Makefile


