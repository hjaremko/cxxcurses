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

if(CURSES_NEED_WIDE)
    find_library(CURSES_PANEL_LIB "panelw")
else()
    find_library(CURSES_PANEL_LIB "panel")
endif()

add_library(cxxcurses_panel INTERFACE)
add_library(cxxcurses::panel ALIAS cxxcurses_panel)
target_include_directories(cxxcurses INTERFACE cxxcurses)
target_link_libraries(cxxcurses_panel INTERFACE ${CURSES_PANEL_LIB} cxxcurses)
target_compile_features(cxxcurses_panel INTERFACE cxx_std_17)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    return()
endif()

add_subdirectory(sample)
