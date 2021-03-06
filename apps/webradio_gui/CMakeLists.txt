cmake_minimum_required(VERSION 3.0)

set(EXAMPLE_NAME webradio_gui)
set(EXENAME ${EXAMPLE_NAME})

message( STATUS "**** BUILDING TEST ${EXAMPLE_NAME} ****" )
#rpiwebradio_dumpallvariables()

find_package(Cairo REQUIRED)
find_package(Boost REQUIRED)
find_package(Boost COMPONENTS program_options filesystem locale REQUIRED)
find_package(Threads REQUIRED)
find_package(WiringPi REQUIRED)

# Set up source files
set(SOURCES
        precomp.cpp
		main.cpp 
		wrmainscreen.cpp 
		wrradioscreen.cpp 
		wrmusicscreen.cpp 
		wrmpddirectorytreeprovider.cpp
    )
set(HEADERS
        precomp.h
		global.h
		wrmainscreen.h
		wrradioscreen.h
		wrmusicscreen.h
		wrmpddirectorytreeprovider.h
    )

add_executable(${EXENAME} ${SOURCES} ${HEADERS})
#target_precompile_headers(${EXENAME} PRIVATE precomp.h) # available from CMake 3.17
add_precompiled_header(${EXENAME} precomp.h FORCEINCLUDE SOURCE_CXX precomp.cpp)
target_link_libraries(${EXENAME} rpiwebradio_gui)
target_link_libraries(${EXENAME} rpiwebradio_mpd)
target_link_libraries(${EXENAME} rpiwebradio_tools)
target_link_libraries(${EXENAME} ${CAIRO_LIBRARIES} )
target_include_directories(${EXENAME} PRIVATE ${CAIRO_INCLUDE_DIRS})
target_link_libraries(${EXENAME} ${WIRINGPI_LIBRARIES} )
target_include_directories(${EXENAME} PRIVATE ${WIRINGPI_INCLUDE_DIRS})
target_link_libraries (${EXENAME} Threads::Threads)
target_link_libraries (${EXENAME} ${Boost_LIBRARIES})
target_link_libraries (${EXENAME} Boost::program_options Boost::filesystem Boost::locale)
target_include_directories(${EXENAME} PRIVATE ${Boost_INCLUDE_DIR})



# Installation
install(TARGETS ${EXENAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
