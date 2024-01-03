cmake_minimum_required(VERSION 3.18)
project(SEMESTRALKA_POSKO C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(SEMESTRALKA_POSKO main.c)
target_link_libraries(SEMESTRALKA_POSKO pthread ${CURSES_LIBRARIES})
