cmake_minimum_required(VERSION 4.0)
project(SDLBase C)
set(CMAKE_C_STANDARD 23)

find_package(SDL3 REQUIRED)

file(GLOB SRC_FILES "src/*.c" "src/*.h" "src/**/*.c" "src/**/*.h")

message(STATUS "Source files: ${SRC_FILES}")

add_executable(SDLBase ${SRC_FILES} )

target_link_libraries(SDLBase PRIVATE SDL3::SDL3)