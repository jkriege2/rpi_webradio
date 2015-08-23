all: Release
debug: Debug
release: Release

LIB=../../../LIB/trunk
CC=g++


CFLAGS =  -Wall -pedantic -std=c++11 `pkg-config --cflags cairo` 
LDFLAGS = -Wall -pedantic -std=c++11 `pkg-config --libs cairo` 

Release: CFLAGS += -O2 -ffast-math -ftree-vectorize -ftree-vectorizer-verbose=0

Debug: CC += -DDEBUG -g

EXECUTABLE=cairo_test
SRC_FILE= cairo_test.cpp \
          framebuffer_cairo_tools.cpp \
          cgwidget.cpp \
          cgframe.cpp \
          cglabel.cpp \
          cairogui_frame.cpp \
          rpi_tools.cpp


SRC_FILE_O = $(subst .cpp,.o,$(SRC_FILE))
SRC_FILE_D = $(subst .cpp,.d,$(SRC_FILE))

-include ${SRC_FILE_D}

Debug:  ${EXECUTABLE}

Release:  ${EXECUTABLE}

${EXECUTABLE}: ${SRC_FILE_O}
	$(CC) $(CFLAGS) -o $(EXECUTABLE) ${SRC_FILE_O} $(LDFLAGS)

%.o: %.cpp
	gcc -c $(CFLAGS) $*.cpp -o $*.o
	gcc -MM $(CFLAGS) $*.cpp > $*.d
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
