cmake_minimum_required(VERSION 2.6)
project(BlackJack-ESDL)

set(EXECUTABLE_OUTPUT_PATH bin)
add_definitions(-Wall -Wextra)

include_directories(include)

set(SDL_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SDL REQUIRED)

if (SDL_FOUND)
	include_directories(${SDL_INCLUDE_DIR})
	message("EasySDL: SDL Header found : ${SDL_INCLUDE_DIR}")
endif()

#include local package of EasySDL 0.6.x
ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/deps/easysdl)

file(
        GLOB_RECURSE
        source_files
        src/*.c
)

add_executable(

        blackjack
        ${source_files}

)

add_dependencies(blackjack ESDL)

target_link_libraries(

        blackjack
        ESDL

)
