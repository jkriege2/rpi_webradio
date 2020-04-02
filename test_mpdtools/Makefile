all: Release
debug: Debug
release: Release

LIBS=./ \
     ../

CC=g++ -std=c++11


CFLAGS =  -Wall -pedantic 
LDFLAGS = -Wall -pedantic -lpthread -lboost_iostreams -lboost_program_options -lboost_filesystem -lboost_exception -lboost_system -lboost_signals -lboost_locale -lmpdclient

Release: OBJDIR = .objs
OBJDIR_DEBUG = .objs_debug
OBJDIR_RELEASE = .objs
Debug: OBJDIR = .objs_debug

Release: CFLAGS += -O2
Release: LDFLAGS += -s

Debug: CC += -g -DDEBUG


EXECUTABLE=test_mpdtools
EXECUTABLE_DEBUG=test_mpdtools_debug
SRC_FILE= test_mpdtools.cpp


SRC_FILE_D = $(addprefix ${OBJDIR}/,$(subst .cpp,.d,$(SRC_FILE)))
SRC_FILE_O_DEBUG = $(addprefix ${OBJDIR_DEBUG}/,$(subst .cpp,.o,$(SRC_FILE)))
SRC_FILE_O_RELEASE = $(addprefix ${OBJDIR_RELEASE}/,$(subst .cpp,.o,$(SRC_FILE)))
LIBS_I = $(addprefix -I,$(LIBS))
LIBS_L = $(addprefix -L,$(LIBS))

MPDTOOLSLIBDIR = ../mpdtools/
Release: LDFLAGS += -L${MPDTOOLSLIBDIR} -lmpdtools
Debug: LDFLAGS += -L${MPDTOOLSLIBDIR} -lmpdtools_debug

LIBS += ${GUILIBDIR} ${MPDTOOLSLIBDIR}


-include ${SRC_FILE_D}

Debug:  ${EXECUTABLE_DEBUG}

Release:  ${EXECUTABLE}

${EXECUTABLE}: MPDTOOLSLIB_RELEASE ${SRC_FILE_O_RELEASE}
	$(CC) $(CFLAGS) $(LIBS_L) -o $(EXECUTABLE) ${SRC_FILE_O_RELEASE} $(LDFLAGS)

${EXECUTABLE_DEBUG}: MPDTOOLSLIB_DEBUG ${SRC_FILE_O_DEBUG}
	$(CC) -o $(EXECUTABLE_DEBUG) $(CFLAGS) $(LIBS_L) ${SRC_FILE_O_DEBUG} $(LDFLAGS)


MPDTOOLSLIB_DEBUG:
	+cd $(MPDTOOLSLIBDIR); $(MAKE) Debug
MPDTOOLSLIB_RELEASE:
	+cd $(MPDTOOLSLIBDIR); $(MAKE) Release


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
