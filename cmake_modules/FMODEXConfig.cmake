# - FMODex finder - by TAHRI Ahmed R. @Ousret
# - https://github.com/Ousret
# Once done this will define
#  LIBFMODEX_FOUND - System has FMODex
#  LIBFMODEX_INCLUDE_DIRS - The FMODex include directories
#  LIBFMODEX_LIBRARIES - The libraries needed to use FMODex
#  LIBFMODEX_DEFINITIONS - Compiler switches required for using FMODex

find_package(PkgConfig)
pkg_check_modules(PC_LIBFMODEX QUIET libfmodex)
set(LIBFMODEX_DEFINITIONS ${PC_LIBFMODEX_CFLAGS_OTHER})
          
FIND_PATH(LIBFMODEX_INCLUDE_DIR fmodex/fmod.h
  HINTS
  $ENV{FMODDIR}
  PATH_SUFFIXES fmodex fmodex
  PATHS
  /usr/local/include
  /sw # Fink
  /opt/local/include # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(LIBFMODEX_LIBRARY 
  NAMES fmodex fmodex64 libfmodex libfmodex64
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

set(LIBFMODEX_LIBRARIES ${LIBFMODEX_LIBRARY} )
set(LIBFMODEX_INCLUDE_DIRS ${LIBFMODEX_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBFMODEX_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(fmodex  DEFAULT_MSG
                                  LIBFMODEX_LIBRARY LIBFMODEX_INCLUDE_DIR)

IF(LIBFMODEX_LIBRARIES)
	message(STATUS "Found FMODex: ${LIBFMODEX_LIBRARIES}" ", " ${LIBFMODEX_INCLUDE_DIRS})
	SET(LIBFMODEX_FOUND TRUE)
	mark_as_advanced(LIBFMODEX_INCLUDE_DIR LIBFMODEX_LIBRARY )
ELSE()
	message(FATAL_ERROR "FMODex is not installed yet, cannot continue ! Reinstall EasySDL may solve this.")
	message(STATUS "???? FMODex: ${LIBFMODEX_LIBRARIES}" ", " ${LIBFMODEX_INCLUDE_DIRS})
	SET(LIBFMODEX_FOUND FALSE)
ENDIF()

