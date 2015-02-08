cmake_minimum_required(VERSION 2.6)
project(BlackJack-ESDL)

set(EXECUTABLE_OUTPUT_PATH bin)
add_definitions(-Wall -Wextra)
#set(LD_LIBRARY_PATH "/usr/local/lib")
# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

#set(CMAKE_C_FLAGS "`sdl-config --cflags`")

execute_process(COMMAND sdl-config --libs
                OUTPUT_VARIABLE SDLCONF_OS)

include_directories(include)

set(SDL_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SDL REQUIRED)

if (SDL_FOUND)
	include_directories(${SDL_INCLUDE_DIR})
	message("EasySDL: SDL Header found : ${SDL_INCLUDE_DIR}")
endif()

file(
        GLOB_RECURSE
        source_files
        src/*.c
)

add_executable(

        blackjack
        ${source_files}

)

#add_dependencies(blackjack ESDL)

target_link_libraries(

        blackjack
        ESDL
        ${SDLCONF_OS}

)
