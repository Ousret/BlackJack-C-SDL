cmake_minimum_required(VERSION 2.6)
project(BlackJack-ESDL)

file(
        GLOB_RECURSE
        source_files
        src/*.c
)

add_executable(
        blackjack
        ${source_files}
)

set(EXECUTABLE_OUTPUT_PATH bin)
add_definitions(-Wall -Wextra)

#Needed for every SDL based program except NT system. 
execute_process(COMMAND sdl-config --libs
                OUTPUT_VARIABLE SDLCONF_OS)

include_directories(include)

set(SDL_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SDL REQUIRED)

if (SDL_FOUND)
	include_directories(${SDL_INCLUDE_DIR})
	message("EasySDL: SDL Header found : ${SDL_INCLUDE_DIR}")
endif()

#Find local FMODex lib
message("This program use FMODex, licence at: http://www.fmod.com/files/public/LICENSE.TXT (NO COMMERCIAL USE)")
message("FMOD Sound System, copyright © Firelight Technologies Pty, Ltd., 1994-2014.")
message("Audio engine : FMOD Sound System by Firelight Technologies")
message("FMOD by Firelight Technologies")

set(FMODEX_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(FMODEX REQUIRED)
if (NOT LIBFMODEX_FOUND)
	message(STATUS "EasySDL: FMODex lib cannot be found, re clone EasySDL may solve this !")
else()
	target_link_libraries(blackjack ${LIBFMODEX_LIBRARIES})
	include_directories(${LIBFMODEX_INCLUDE_DIRS})
endif()

set(EasySDL_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(EasySDL REQUIRED)

if (LIBEASYSDL_FOUND)
	target_link_libraries(blackjack ${SDLCONF_OS})
	target_link_libraries(blackjack ${LIBEASYSDL_LIBRARIES})
	include_directories(${LIBEASYSDL_INCLUDE_DIRS})
endif()


