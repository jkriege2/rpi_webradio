all: Release
debug: Debug
release: Release

both: 
	+make Debug 
	+make Release 

LIBS=./ \
     ../ \
     ../../CImg

CC=g++ -std=c++11


CFLAGS =  -Wall -pedantic `pkg-config --cflags cairo` -static
LDFLAGS = -Wall -pedantic `pkg-config --libs cairo` -lwiringPi -lpthread -lboost_iostreams -lboost_program_options -lboost_filesystem -lboost_exception -lboost_system -lboost_signals -lboost_locale -lmpdclient
OBJDIR_DEBUG = .objs_debug
OBJDIR_RELEASE = .objs
OBJDIR = .objs
Release: OBJDIR = .objs
Debug: OBJDIR = .objs_debug
Debug: CC += -g -DDEBUG
Release: CFLAGS += -O2
Release: LDFLAGS += -s

LIB_NAME=cairogui
SRC_FILE= framebuffer_cairo_tools.cpp \
          cgwidget.cpp \
          cgframe.cpp \
          cglabel.cpp \
          rpi_tools.cpp \
          cgbasics.cpp \
          cgscreen.cpp \
          cgeventqueue.cpp \
          cgprogressbar.cpp \
          cgfontprops.cpp \
          cgmultiscreens.cpp \
          cgtabbedmultiscreens.cpp \
          cgscrollbar.cpp \
          cgpalette.cpp \
          cgimage.cpp \
          rpi_cgevents.cpp \
          cgevents.cpp \
          cgtabmixin.cpp \
          cglayout.cpp \
          cgapplication.cpp \
          cgtwostatimage.cpp \
          cgsymbol.cpp \
          cgdirectorytreewidget.cpp \
          cgtreebase.cpp \
          mpd_tools.cpp

RELEASE_LIB_NAME = lib${LIB_NAME}.a
DEBUG_LIB_NAME = lib${LIB_NAME}_debug.a

Release: FULL_LIB_NAME = lib${LIB_NAME}.a

Debug: FULL_LIB_NAME = lib${LIB_NAME}_debug.a

#SRC_FILE_D = 

Release: SRC_FILE_D = $(addprefix $(OBJDIR_RELEASE)/,$(subst .cpp,.d,$(SRC_FILE)))

Debug: SRC_FILE_D = $(addprefix $(OBJDIR_DEBUG)/,$(subst .cpp,.d,$(SRC_FILE)))

SRC_FILE_O_DEBUG = $(addprefix $(OBJDIR_DEBUG)/,$(subst .cpp,.o,$(SRC_FILE)))
SRC_FILE_O_RELEASE = $(addprefix $(OBJDIR_RELEASE)/,$(subst .cpp,.o,$(SRC_FILE)))


LIBS_I = $(addprefix -I,$(LIBS))
LIBS_L = $(addprefix -L,$(LIBS))
include ${SRC_FILE_D}

Debug:  ${DEBUG_LIB_NAME}
Release:  ${RELEASE_LIB_NAME}

${DEBUG_LIB_NAME}: ${SRC_FILE_O_DEBUG}
	ar rc $@ ${SRC_FILE_O_DEBUG}
	ranlib $@

${RELEASE_LIB_NAME}: ${SRC_FILE_O_RELEASE}
	ar rc $@ ${SRC_FILE_O_RELEASE}
	ranlib $@

${OBJDIR_RELEASE}/%.o: ./%.cpp
	@mkdir -p ${OBJDIR_RELEASE}
	$(CC) -c $(CFLAGS) $(LIBS_I) $*.cpp -o ${OBJDIR_RELEASE}/$*.o
	@$(CC) -MM $(CFLAGS) $(LIBS_I) $*.cpp > ${OBJDIR_RELEASE}/$*.d
	@mv -f ${OBJDIR_RELEASE}/$*.d ${OBJDIR_RELEASE}/$*.d.tmp
	@sed -e "s|.*:|$(subst .,\.,${OBJDIR_RELEASE})/$*.o:|" < ${OBJDIR_RELEASE}/$*.d.tmp > ${OBJDIR_RELEASE}/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < ${OBJDIR_RELEASE}/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> ${OBJDIR_RELEASE}/$*.d
	@rm -f ${OBJDIR_RELEASE}/$*.d.tmp

${OBJDIR_DEBUG}/%.o: ./%.cpp
	@mkdir -p ${OBJDIR_DEBUG}
	$(CC) -c $(CFLAGS) $(LIBS_I) $*.cpp -o ${OBJDIR_DEBUG}/$*.o
	@$(CC) -MM $(CFLAGS) $(LIBS_I) $*.cpp > ${OBJDIR_DEBUG}/$*.d
	@mv -f ${OBJDIR_DEBUG}/$*.d ${OBJDIR_DEBUG}/$*.d.tmp
	@sed -e "s|.*:|$(subst .,\.,${OBJDIR_DEBUG})/$*.o:|" < ${OBJDIR_DEBUG}/$*.d.tmp > ${OBJDIR_DEBUG}/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < ${OBJDIR_DEBUG}/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> ${OBJDIR_DEBUG}/$*.d
	@rm -f ${OBJDIR_DEBUG}/$*.d.tmp


clean:
	rm -f ${DEBUG_LIB_NAME}
	rm -f ${RELEASE_LIB_NAME}
	rm -rf ${OBJDIR_DEBUG}
	rm -rf ${OBJDIR_RELEASE}
