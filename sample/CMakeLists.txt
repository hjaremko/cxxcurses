cmake_minimum_required(VERSION 3.14)
project(cxxcurses_sample)

set(CMAKE_CXX_STANDARD 17)
set(CURSES_NEED_NCURSES TRUE)

find_package(Curses REQUIRED)

include_directories(SYSTEM "${CURSES_INCLUDE_DIR}")
link_directories("${CURSES_INCLUDE_DIRS}")
link_libraries(${CURSES_LIBRARIES})

add_library(project_warnings INTERFACE)

if (MSVC)
    target_compile_options(project_warnings INTERFACE /W4)
else()
    target_compile_options(project_warnings
                         INTERFACE
                         -Wall
                         -Wextra
                         -Wshadow
                         -Wnon-virtual-dtor
                         -Wold-style-cast
                         -Wcast-align
                         -Wunused
                         -Woverloaded-virtual
                         -Wpedantic
                         -Wconversion
#                         -Wsign-conversion
                         -Wmisleading-indentation
                         -Wduplicated-cond
                         -Wduplicated-branches
                         -Wlogical-op
                         -Wnull-dereference
                         -Wuseless-cast
                         -Wdouble-promotion
                         -Wformat=2
                         )
endif()

#include_directories(../include)

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE project_warnings)
#add_subdirectory(test)
