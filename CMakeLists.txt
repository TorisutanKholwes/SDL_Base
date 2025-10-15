cmake_minimum_required(VERSION 4.0)
project(SDLBase C)
set(CMAKE_C_STANDARD 23)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)

file(GLOB SRC_FILES "src/*.c" "src/**/*.c")

message(STATUS "Source files: ${SRC_FILES}")

add_executable(SDLBase ${SRC_FILES} )

target_include_directories(SDLBase PRIVATE include)

target_link_libraries(SDLBase PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer SDL3_ttf::SDL3_ttf)

target_compile_options(SDLBase PRIVATE -Wall -Wextra)
