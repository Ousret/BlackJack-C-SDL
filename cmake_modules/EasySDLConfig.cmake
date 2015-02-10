# - EasySDL finder - by TAHRI Ahmed R. @Ousret
# - https://github.com/Ousret
# Once done this will define
#  LIBEASYSDL_FOUND - System has EasySDL
#  LIBEASYSDL_INCLUDE_DIRS - The EasySDL include directories
#  LIBEASYSDL_LIBRARIES - The libraries needed to use EasySDL
#  LIBEASYSDL_DEFINITIONS - Compiler switches required for using EasySDL

find_package(PkgConfig)
pkg_check_modules(PC_LIBEASYSDL QUIET libesdl)
set(LIBEASYSDL_DEFINITIONS ${PC_LIBEASYSDL_CFLAGS_OTHER})
          
FIND_PATH(LIBEASYSDL_INCLUDE_DIR ESDL.h
  HINTS
  $ENV{FMODDIR}
  PATH_SUFFIXES include
  PATHS
  /usr/local
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(LIBEASYSDL_LIBRARY 
  NAMES esdl
  HINTS
  ${PC_LIBFMODEX_LIBDIR} ${PC_LIBFMODEX_LIBRARY_DIRS}
  PATH_SUFFIXES lib64 lib x86_64-linux-gnu
  PATHS
  /sw
  /opt/local
  /usr/local
  /usr/local/lib #Linux
  /opt/csw
  /opt
)

set(LIBEASYSDL_LIBRARIES ${LIBEASYSDL_LIBRARY} )
set(LIBEASYSDL_INCLUDE_DIRS ${LIBEASYSDL_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBFMODEX_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(esdl  DEFAULT_MSG
                                  LIBEASYSDL_LIBRARY LIBEASYSDL_INCLUDE_DIR)

IF(LIBFMODEX_LIBRARIES)
	message(STATUS "Found EasySDL: ${LIBEASYSDL_LIBRARIES}" ", " ${LIBEASYSDL_INCLUDE_DIRS})
	SET(LIBEASYSDL_FOUND TRUE)
	mark_as_advanced(LIBEASYSDL_INCLUDE_DIR LIBEASYSDL_LIBRARY )
ELSE()
	message(FATAL_ERROR "EasySDL SDK is not found !")
	SET(LIBFMODEX_FOUND FALSE)
ENDIF()

