cmake_minimum_required(VERSION 3.14)
project(cxxcurses_sample)

set(CMAKE_CXX_STANDARD 17)
set(CURSES_NEED_NCURSES TRUE)

find_package(Curses REQUIRED)

include_directories(SYSTEM "${CURSES_INCLUDE_DIR}")
link_directories("${CURSES_INCLUDE_DIRS}")
link_libraries(${CURSES_LIBRARIES})

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME})
