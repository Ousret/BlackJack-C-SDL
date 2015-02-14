# - EasySDL finder - by TAHRI Ahmed R. @Ousret
# - https://github.com/Ousret
# Once done this will define
#  LIBEASYSDL_FOUND - System has EasySDL
#  LIBEASYSDL_INCLUDE_DIRS - The EasySDL include directories
#  LIBEASYSDL_LIBRARIES - The libraries needed to use EasySDL
          
FIND_PATH(LIBEASYSDL_INCLUDE_DIR ESDL.h
  HINTS
  $ENV{EASYSDLDIR}
  PATH_SUFFIXES include
  PATHS
  /usr/local
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(LIBEASYSDL_LIBRARY 
  NAMES ESDL
  HINTS
  ${PC_LIBEASYSDL_LIBDIR} ${PC_LIBEASYSDL_LIBRARY_DIRS}
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

IF(LIBEASYSDL_LIBRARIES)
	message(STATUS "Found EasySDL: ${LIBEASYSDL_LIBRARIES}" ", " ${LIBEASYSDL_INCLUDE_DIRS})
	SET(LIBEASYSDL_FOUND TRUE)
	mark_as_advanced(LIBEASYSDL_INCLUDE_DIR LIBEASYSDL_LIBRARY )
ELSE()
	message(FATAL_ERROR "EasySDL SDK is not found !")
	SET(LIBFMODEX_FOUND FALSE)
ENDIF()

