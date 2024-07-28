cmake_minimum_required(VERSION 3.16)
project(mini-wars)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES src/*.cpp)

add_executable(Game ${SOURCES})

target_include_directories(Game PUBLIC inc)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

target_compile_options(Game PRIVATE -Wall -Wextra -Wpedantic -Werror)