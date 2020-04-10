cmake_minimum_required(VERSION 3.14)
project(cxxcurses_sample)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_CXX_STANDARD 17)
set(CURSES_NEED_NCURSES TRUE)

find_package(Curses REQUIRED)

include_directories(SYSTEM "${CURSES_INCLUDE_DIR}")
include_directories("../include")
link_directories("${CURSES_INCLUDE_DIRS}")

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
