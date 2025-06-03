cmake_minimum_required(VERSION 3.10)
project(ddr_game)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
link_directories(${SDL2_LIBRARY_DIRS})

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ddr ${SOURCES})
target_link_libraries(ddr ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})

target_compile_options(ddr PRIVATE -Wall -Wextra -pedantic)
# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
# 	target_compile_options(ddr PRIVATE -g -O0 -fsanitize=address -fsanitize=undefined)
# else()
# 	target_compile_options(ddr PRIVATE -O2)