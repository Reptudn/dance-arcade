cmake_minimum_required(VERSION 3.10)
project(ddr_game)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

include_directories(
	${SDL2_INCLUDE_DIRS}
	${SDL2_MIXER_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/include
)
link_directories(${SDL2_LIBRARY_DIRS})

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ddr ${SOURCES})
target_link_libraries(
	ddr
	${SDL2_LIBRARIES}
	${SDL2_MIXER_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
)

# add_custom_target(install_deps
#     COMMAND ${CMAKE_COMMAND} -E echo "Trying to install dependencies..."
#     COMMAND bash -c "
#         if command -v dnf >/dev/null 2>&1; then
#             sudo dnf install -y SDL2-devel SDL2_mixer-devel SDL2_ttf-devel SDL2_image-devel pkgconf-pkg-config;
#         elif command -v apt-get >/dev/null 2>&1; then
#             sudo apt-get update && sudo apt-get install -y libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev pkg-config;
#         elif command -v brew >/dev/null 2>&1; then
#             brew install sdl2 sdl2_mixer sdl2_ttf sdl2_image pkg-config;
#         else
#             echo 'Please install SDL2, SDL2_mixer, SDL2_ttf, SDL2_image, and pkg-config manually.';
#             exit 1;
#         fi
#     "
#     COMMENT "Attempting to install dependencies for your platform"
# )

target_compile_options(ddr PRIVATE -Wall -Wextra -pedantic -Werror)
# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
# 	target_compile_options(ddr PRIVATE -g -O0 -fsanitize=address -fsanitize=undefined)
# else()
# 	target_compile_options(ddr PRIVATE -O2)