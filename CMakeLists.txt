cmake_minimum_required(VERSION 2.6)
project(BlackJack-ESDL)

set(EXECUTABLE_OUTPUT_PATH bin)
add_definitions(-Wall -Wextra)
#set(LD_LIBRARY_PATH "/usr/local/lib")


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

set(FMODEX_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(FMODEX REQUIRED)

set(EasySDL_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(EasySDL REQUIRED)

set(BUILD_LIBRARIES "${LIBEASYSDL_LIBRARIES} ${LIBFMODEX_LIBRARIES}")

file(
        GLOB_RECURSE
        source_files
        src/*.c
)

add_executable(

        blackjack
        ${source_files}

)

target_link_libraries(

        blackjack
        ${SDLCONF_OS}
        ${BUILD_LIBRARIES}

)
