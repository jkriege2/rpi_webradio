all: Release
debug: Debug
release: Release

LIBS=../lib \
     ./ \
     ../ \
     ../../CImg

CC=g++ -std=c++11


CFLAGS =  -Wall -pedantic `pkg-config --cflags cairo`
LDFLAGS = -Wall -pedantic `pkg-config --libs cairo` -lwiringPi -lpthread -lboost_iostreams -lboost_program_options -lboost_filesystem -lboost_exception -lboost_system -lboost_signals -lmpdclient

Release: OBJDIR = .objs
OBJDIR_DEBUG = .objs_debug
OBJDIR_RELEASE = .objs
Debug: OBJDIR = .objs_debug

Release: CFLAGS += -O2
Release: LDFLAGS += -s

Debug: CC += -g -DDEBUG


EXECUTABLE=webradio_gui
EXECUTABLE_DEBUG=webradio_gui_debug
SRC_FILE= main.cpp \
		  wrmainscreen.cpp \
		  wrradioscreen.cpp \
		  wrmusicscreen.cpp


SRC_FILE_D = $(addprefix ${OBJDIR}/,$(subst .cpp,.d,$(SRC_FILE)))
SRC_FILE_O_DEBUG = $(addprefix ${OBJDIR_DEBUG}/,$(subst .cpp,.o,$(SRC_FILE)))
SRC_FILE_O_RELEASE = $(addprefix ${OBJDIR_RELEASE}/,$(subst .cpp,.o,$(SRC_FILE)))
LIBS_I = $(addprefix -I,$(LIBS))
LIBS_L = $(addprefix -L,$(LIBS))

GUILIBDIR = ../lib/
Release: LDFLAGS += -L${GUILIBDIR} -lcairogui
Debug: LDFLAGS += -L${GUILIBDIR} -lcairogui_debug


-include ${SRC_FILE_D}

Debug:  ${EXECUTABLE_DEBUG}

Release:  ${EXECUTABLE}

${EXECUTABLE}: GUILIB_RELEASE ${SRC_FILE_O_RELEASE}
	cd $(GUILIBDIR); make Release -j4
	$(CC) $(CFLAGS) $(LIBS_L) -o $(EXECUTABLE) ${SRC_FILE_O_RELEASE} $(LDFLAGS)

${EXECUTABLE_DEBUG}: GUILIB_DEBUG ${SRC_FILE_O_DEBUG}
	$(CC) -o $(EXECUTABLE_DEBUG) $(CFLAGS) $(LIBS_L) ${SRC_FILE_O_DEBUG} $(LDFLAGS)

GUILIB_DEBUG:
	+cd $(GUILIBDIR); $(MAKE) Debug
GUILIB_RELEASE:
	+cd $(GUILIBDIR); $(MAKE) Release


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
	rm -f ${EXECUTABLE}
	rm -f ${EXECUTABLE_DEBUG}
	rm -rf ${OBJDIR_DEBUG}
	rm -rf ${OBJDIR_RELEASE}


cleanlib:
	+cd $(GUILIBDIR); $(MAKE) clean
