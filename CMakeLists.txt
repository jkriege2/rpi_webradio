cmake_minimum_required(VERSION 3.0)

# Project Name and Version
project(RPI_Webradio LANGUAGES CXX VERSION 0.1)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)
 
# set search path for CMake files
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

message(STATUS " ${CMAKE_MODULE_PATH} ")

include(GNUInstallDirs)

# configure compiler
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# tool function
include(rpiwebradio_dumpallvariables)
#rpiwebradio_dumpallvariables()


# now add subdirectories with the library code ...
add_subdirectory(libs)
add_subdirectory(apps)
add_subdirectory(tests)
