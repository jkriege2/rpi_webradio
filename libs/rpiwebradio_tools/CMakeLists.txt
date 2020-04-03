cmake_minimum_required(VERSION 3.7)

set(lib_name rpiwebradio_tools)
message( STATUS "**** BUILDING LIBRARY ${lib_name} ****" )

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(WiringPi REQUIRED)

# Set up source files
set(SOURCES
    rpi_tools.cpp
)

set(HEADERS
    rpi_tools.h
)

include(CMakePackageConfigHelpers)

add_library(${lib_name} SHARED  ${SOURCES} ${HEADERS})
set_property(TARGET ${lib_name} PROPERTY VERSION "${PROJECT_VERSION}")
set_property(TARGET ${lib_name} PROPERTY OUTPUT_NAME  "${lib_name}")
set_target_properties(${lib_name} PROPERTIES PUBLIC_HEADER ${HEADERS})
target_link_libraries(${lib_name} PUBLIC ${WIRINGPI_LIBRARIES} )
target_link_libraries (${lib_name} PUBLIC Threads::Threads)
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


