cmake_minimum_required(VERSION 3.0)

set(EXAMPLE_NAME test_mpdtools_base)
set(EXENAME ${EXAMPLE_NAME})

message( STATUS "**** BUILDING TEST ${EXAMPLE_NAME} ****" )
#rpiwebradio_dumpallvariables()

# Set up source files
set(SOURCES
    test_mpdtools_base.cpp
    )
set(HEADERS
    )

add_executable(${EXENAME} ${SOURCES} ${HEADERS})
target_link_libraries(${EXENAME} rpiwebradio_mpd)


# Installation
install(TARGETS ${EXENAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
