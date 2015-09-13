all: Release
debug: Debug
release: Release

LIB=../../../LIB/trunk
CC=g++


CFLAGS =  -Wall -pedantic -std=c++11 -I../lib `pkg-config --cflags cairo`
LDFLAGS = -Wall -pedantic -std=c++11 `pkg-config --libs cairo` -lwiringPi

Release: CFLAGS += -O2
Release: LDFLAGS += -s

Debug: CC += -g -DDEBUG
Debug: CC += -g -DDEBUG

EXECUTABLE=cairo_test
SRC_FILE= cairo_test.cpp \
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
          ../lib/cgscrollbar.cpp \
          ../lib/cgpalette.cpp \
          ../lib/cgimage.cpp \
          ../lib/rpi_cgevents.cpp \
          ../lib/cgevents.cpp


SRC_FILE_O = $(subst .cpp,.o,$(SRC_FILE))
SRC_FILE_D = $(subst .cpp,.d,$(SRC_FILE))

-include ${SRC_FILE_D}

Debug:  ${EXECUTABLE}

Release:  ${EXECUTABLE}

${EXECUTABLE}: ${SRC_FILE_O}
	$(CC) $(CFLAGS) -o $(EXECUTABLE) ${SRC_FILE_O} $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $*.cpp -o $*.o
	@$(CC) -MM $(CFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

clean:
	rm -f ${EXECUTABLE}
	rm -f ${SRC_FILE_O}
	rm -f ${SRC_FILE_D}
	rm -f *.o
