# FindWiringpi.cmake - Try to find the wiringPi library
# Once done this will define
#
#  WIRINGPI_FOUND - System has Hiredis
#  WIRINGPI_INCLUDE_DIR - The Hiredis include directory
#  WIRINGPI_LIBRARIES - The libraries needed to use Hiredis
#  WIRINGPI_DEFINITIONS - Compiler switches required for using Hiredis

FIND_PATH(WIRINGPI_INCLUDE_DIR NAMES wiringPi.h
   PATHS
   /usr
   /usr/local
   /opt
   PATH_SUFFIXES
   )

FIND_LIBRARY(WIRINGPI_LIBRARIES NAMES wiringPi
   PATHS
   /usr
   /usr/local
   /opt
   )

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Wiringpi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIR)

MARK_AS_ADVANCED(WIRINGPI_INCLUDE_DIR WIRINGPI_LIBRARIES)


IF(WIRINGPI_FOUND)
	MESSAGE(STATUS "Found WiringPi: ${WIRINGPI_LIB}")
ELSE(WIRINGPI_FOUND)
	MESSAGE(STATUS "WiringPi Not Found")
ENDIF(WIRINGPI_FOUND)