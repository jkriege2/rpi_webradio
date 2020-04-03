cmake_minimum_required(VERSION 3.0)

set(EXAMPLE_NAME test_widgets)
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
    widgets_test.cpp
    )
set(HEADERS
    )

add_executable(${EXENAME} ${SOURCES} ${HEADERS})
target_link_libraries(${EXENAME} rpiwebradio_gui)
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
