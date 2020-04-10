cmake_minimum_required(VERSION 3.7)

set(lib_name rpiwebradio_gui)
message( STATUS "**** BUILDING LIBRARY ${lib_name} ****" )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Cairo REQUIRED)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(WiringPi REQUIRED)

include(PrecompiledHeader)

# Set up source files
set(SOURCES
    cgprecomp.cpp
	cgapplication.cpp 
	cgbasics.cpp 
	cgdirectorytreewidget.cpp 
	cgeventqueue.cpp 
	cgevents.cpp 
	cgfontprops.cpp 
	cgframe.cpp 
	cgimage.cpp 
	cglabel.cpp 
	cglayout.cpp 
	cgmultiscreens.cpp 
	cgpalette.cpp 
	cgprogressbar.cpp 
	cgscreen.cpp 
	cgscrollbar.cpp 
	cgsymbol.cpp 
	cgtabbedmultiscreens.cpp 
	cgtabmixin.cpp 
	cgtreebase.cpp
	cgtwostatimage.cpp 
	cgwidget.cpp 
	framebuffer_cairo_tools.cpp 
	rpi_cgevents.cpp 
	cgdebug.cpp
)

set(HEADERS
    cgprecomp.h
	cgapplication.h 
	cgbasics.h 
	cgdirectorytreewidget.h 
	cgeventqueue.h 
	cgevents.h 
	cgfontprops.h 
	cgframe.h 
	cgimage.h 
	cglabel.h 
	cglayout.h
    cglib.h	
	cglistwidget.h
	cgmultiscreens.h 
	cgpalette.h 
	cgprogressbar.h 
	cgscreen.h 
	cgscrollbar.h 
	cgsymbol.h 
	cgtabbedmultiscreens.h 
	cgtabmixin.h 
	cgtreebase.h
	cgtwostatimage.h 
	cgwidget.h 
	framebuffer_cairo_tools.h 
	rpi_cgevents.h 
	cgdebug.h
)

include(CMakePackageConfigHelpers)

add_library(${lib_name} SHARED  ${SOURCES} ${HEADERS})
set_property(TARGET ${lib_name} PROPERTY VERSION "${PROJECT_VERSION}")
set_property(TARGET ${lib_name} PROPERTY OUTPUT_NAME  "${lib_name}")
set_property(TARGET ${lib_name} PROPERTY POSITION_INDEPENDENT_CODE ON)
#set_target_properties(${lib_name} PROPERTIES PUBLIC_HEADER ${HEADERS})
#target_precompile_headers(${lib_name} PRIVATE cgprecomp.h) # available from CMake 3.17
add_precompiled_header(${lib_name} cgprecomp.h FORCEINCLUDE SOURCE_CXX cgprecomp.cpp)
target_link_libraries(${lib_name} PUBLIC ${CAIRO_LIBRARIES} )
target_include_directories(${lib_name} PRIVATE ${CAIRO_INCLUDE_DIRS})
target_link_libraries(${lib_name} PUBLIC ${WIRINGPI_LIBRARIES} )
target_include_directories(${lib_name} PRIVATE ${WIRINGPI_INCLUDE_DIRS})
target_link_libraries (${lib_name} PUBLIC Threads::Threads)
target_link_libraries (${lib_name} PUBLIC rpiwebradio_tools)
# Specify include directories for both compilation and installation process.
# The $<INSTALL_PREFIX> generator expression is useful to ensure to create
# relocatable configuration files, see https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-relocatable-packages
target_include_directories(${lib_name} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                              "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>/${lib_name}")


write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${lib_name}Version.cmake
								 VERSION ${PROJECT_VERSION} 
								 COMPATIBILITY AnyNewerVersion )   
								 


# Installation
install(TARGETS ${lib_name} EXPORT ${lib_name}_TARGETS
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${lib_name}
)
install(EXPORT ${lib_name}_TARGETS
	FILE ${lib_name}Config.cmake 
	DESTINATION lib/cmake/${lib_name}
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${lib_name}Version.cmake" 
		DESTINATION lib/cmake/${lib_name}  )


