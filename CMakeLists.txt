cmake_minimum_required(VERSION 2.6)
project(BlackJack-ESDL)

set(EXECUTABLE_OUTPUT_PATH bin)
add_definitions(-Wall -Wextra)
#set(SDLCONF_OS "sdl-config --libs")

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
set_target_properties(blackjack PROPERTIES INSTALL_RPATH_USE_LINK_PATH FALSE)
#add_dependencies(blackjack ESDL)

target_link_libraries(

        blackjack
        ESDL
        ${SDLCONF_OS}

)
