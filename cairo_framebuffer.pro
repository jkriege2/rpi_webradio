TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    cairo_test.cpp \
    framebuffer_cairo_tools.cpp \
    cgwidget.cpp \
    cgframe.cpp \
    cglabel.cpp \
    rpi_tools.cpp \
    cgbasics.cpp \
    cgscreen.cpp \
    cgeventqueue.cpp \
    cgprogressbar.cpp \
    cglistwidget.cpp \
    cgfontprops.cpp

HEADERS += \
    framebuffer_cairo_tools.h \
    cgwidget.h \
    cgframe.h \
    cglabel.h \
    rpi_tools.h \
    cgbasics.h \
    cgscreen.h \
    cgeventqueue.h \
    cgprogressbar.h \
    cglistwidget.h \
    cgfontprops.h

DISTFILES += \
    Makefile


