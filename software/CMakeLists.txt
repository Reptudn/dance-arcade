cmake_minimum_required(VERSION 3.10)
project(ddr_game)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(ddr ${SOURCES})
target_link_libraries(ddr ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
