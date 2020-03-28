all: Release
debug: Debug
release: Release

LIBS=../lib \
     ../rpitools \
     ./ \
     ../ \
     ../../CImg

CC=g++ -std=c++11


CFLAGS =  -Wall -pedantic `pkg-config --cflags cairo`
LDFLAGS = -Wall -pedantic `pkg-config --libs cairo` -lwiringPi -lpthread -lboost_iostreams -lboost_program_options -lboost_filesystem -lboost_exception -lboost_system -lboost_signals -lboost_locale

Release: OBJDIR = .objs
OBJDIR_DEBUG = .objs_debug
OBJDIR_RELEASE = .objs
Debug: OBJDIR = .objs_debug

Release: CFLAGS += -O2
Release: LDFLAGS += -s

Debug: CC += -g -DDEBUG


EXECUTABLE=cairo_test
EXECUTABLE_DEBUG=cairo_test_debug
SRC_FILE= cairo_test.cpp


SRC_FILE_D = $(addprefix ${OBJDIR}/,$(subst .cpp,.d,$(SRC_FILE)))
SRC_FILE_O_DEBUG = $(addprefix ${OBJDIR_DEBUG}/,$(subst .cpp,.o,$(SRC_FILE)))
SRC_FILE_O_RELEASE = $(addprefix ${OBJDIR_RELEASE}/,$(subst .cpp,.o,$(SRC_FILE)))
LIBS_I = $(addprefix -I,$(LIBS))
LIBS_L = $(addprefix -L,$(LIBS))

GUILIBDIR = ../lib/
RPITOOLSLIBDIR = ../rpitools/
Release: LDFLAGS += -L${GUILIBDIR} -lcairogui -L${RPITOOLSLIBDIR} -lrpitools
Debug: LDFLAGS += -L${GUILIBDIR} -lcairogui_debug -L${RPITOOLSLIBDIR} -lrpitools_debug

LIBS += ${GUILIBDIR} ${RPITOOLSLIBDIR}

-include ${SRC_FILE_D}

Debug:  ${EXECUTABLE_DEBUG}

Release:  ${EXECUTABLE}

${EXECUTABLE}: GUILIB_RELEASE RPITOOLSLIB_RELEASE ${SRC_FILE_O_RELEASE}
	$(CC) $(CFLAGS) $(LIBS_L) -o $(EXECUTABLE) ${SRC_FILE_O_RELEASE} $(LDFLAGS)

${EXECUTABLE_DEBUG}: GUILIB_DEBUG RPITOOLSLIB_DEBUG ${SRC_FILE_O_DEBUG}
	$(CC) $(CFLAGS) $(LIBS_L) -o $(EXECUTABLE) ${SRC_FILE_O_DEBUG} $(LDFLAGS)

GUILIB_DEBUG:
	cd $(GUILIBDIR); make Debug -j4
GUILIB_RELEASE:
	cd $(GUILIBDIR); make Release -j4

RPITOOLSLIB_DEBUG:
	+cd $(RPITOOLSLIBDIR); $(MAKE) Debug
RPITOOLSLIB_RELEASE:
	+cd $(RPITOOLSLIBDIR); $(MAKE) Release


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

