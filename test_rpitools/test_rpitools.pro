TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../rpitools/

SOURCES += \
    test_rpitools.cpp \
    ../rpitools/rpi_tools.cpp

HEADERS += \
    ../mpdtools/rpi_tools.h \
    ../rpitools/rpi_tools.h

DISTFILES += Makefile \
    ../rpitools/Makefile


