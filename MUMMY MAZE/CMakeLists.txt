cmake_minimum_required(VERSION 3.20)
project(MUMMY_MAZE)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    # Windows-specific setup
    find_package(Curses REQUIRED)
    if(NOT CURSES_FOUND)
        message(FATAL_ERROR "Curses not found on Windows! Install PDCurses.")
    endif()
else()
    # macOS/Linux setup
    find_package(Curses REQUIRED)
endif()

add_executable(MUMMY_MAZE main.cpp player.h player.cpp)
target_include_directories(MUMMY_MAZE PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(MUMMY_MAZE PRIVATE ${CURSES_LIBRARIES})