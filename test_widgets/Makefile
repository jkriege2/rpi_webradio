all: Release
debug: Debug
release: Release

LIBS=../lib \
     ../../CImg

CC=g++ -std=c++11


CFLAGS =  -Wall -pedantic `pkg-config --cflags cairo`
LDFLAGS = -Wall -pedantic `pkg-config --libs cairo` -lwiringPi -lpthread

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
          ../lib/cgtabbedmultiscreens.cpp \
          ../lib/cgscrollbar.cpp \
          ../lib/cgpalette.cpp \
          ../lib/cgimage.cpp \
          ../lib/rpi_cgevents.cpp \
          ../lib/cgevents.cpp \
          ../lib/cgtabmixin.cpp \
          ../lib/cglayout.cpp


SRC_FILE_O = $(subst .cpp,.o,$(SRC_FILE))
SRC_FILE_D = $(subst .cpp,.d,$(SRC_FILE))
LIBS_I = $(addprefix -I,$(LIBS))
LIBS_L = $(addprefix -L,$(LIBS))

-include ${SRC_FILE_D}

Debug:  ${EXECUTABLE}

Release:  ${EXECUTABLE}

${EXECUTABLE}: ${SRC_FILE_O}
	$(CC) $(CFLAGS) $(LIBS_L) -o $(EXECUTABLE) ${SRC_FILE_O} $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(LIBS_I) $*.cpp -o $*.o
	@$(CC) -MM $(CFLAGS) $(LIBS_I) $*.cpp > $*.d
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
