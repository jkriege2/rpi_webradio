TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += cairo_test.cpp \
    ../lib/framebuffer_cairo_tools.cpp \
    ../lib/cgwidget.cpp \
    ../lib/cgframe.cpp \
    ../lib/cglabel.cpp \
    ../lib/rpi_tools.cpp \
    ../lib/cgbasics.cpp \
    ../lib/cgscreen.cpp \
    ../lib/cgeventqueue.cpp \
    ../lib/cgprogressbar.cpp \
    ../lib/cglistwidget.cpp \
    ../lib/cgfontprops.cpp \
    ../lib/cgtreewidget.cpp \
    ../lib/cgmultiscreens.cpp \
    ../lib/cgpalette.cpp \
    ../lib/cgscrollbar.cpp \
    ../lib/cgimage.cpp

HEADERS += \
    ../lib/framebuffer_cairo_tools.h \
    ../lib/cgwidget.h \
    ../lib/cgframe.h \
    ../lib/cglabel.h \
    ../lib/rpi_tools.h \
    ../lib/cgbasics.h \
    ../lib/cgscreen.h \
    ../lib/cgeventqueue.h \
    ../lib/cgprogressbar.h \
    ../lib/cglistwidget.h \
    ../lib/cgfontprops.h \
    ../lib/cgtreewidget.h \
    ../lib/cgmultiscreens.h \
    ../lib/cgpalette.h \
    ../lib/cgscrollbar.h \
    ../lib/cgimage.h

DISTFILES += Makefile


