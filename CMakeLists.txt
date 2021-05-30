cmake_minimum_required(VERSION 3.16)
project(cxxcurses CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
add_library(Curses::ncurses INTERFACE IMPORTED)
target_include_directories(Curses::ncurses SYSTEM INTERFACE ${CURSES_INCLUDE_DIRS})
target_link_libraries(Curses::ncurses INTERFACE ${CURSES_LIBRARIES})

add_library(cxxcurses INTERFACE)
add_library(cxxcurses::cxxcurses ALIAS cxxcurses)
target_include_directories(cxxcurses INTERFACE include)
target_link_libraries(cxxcurses INTERFACE Curses::ncurses)
target_compile_features(cxxcurses INTERFACE cxx_std_17)

add_subdirectory(sample)
