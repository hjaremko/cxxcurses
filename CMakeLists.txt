cmake_minimum_required(VERSION 3.12)
project(libcxxcurses VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "C++ wrapper around ncurses")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#add_library(cxxcurses OBJECT src/output/print.cpp)
#add_library(cxxcurses SHARED src/output/print.cpp)
add_library(cxxcurses STATIC src/output/print.cpp)
add_library(project_warnings INTERFACE)

find_package(Curses REQUIRED)

target_include_directories(cxxcurses
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CURSES_INCLUDE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (MSVC)
    target_compile_options(project_warnings INTERFACE /W3)
else()
    target_compile_options(project_warnings
                         INTERFACE
                        -Werror
                         -Wall
                         -Wextra
                         -Wshadow
                         -Wnon-virtual-dtor
                         -Wold-style-cast
                         -Wcast-align
                         -Wunused
                         -Woverloaded-virtual
                         -Wpedantic
#                         -Wconversion
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

set_target_properties( cxxcurses
    PROPERTIES
    CXX_STANDARD 17
    POSITION_INDEPENDENT_CODE ON
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(cxxcurses PUBLIC ${CURSES_LIBRARIES} PRIVATE project_warnings)

#add_library(cxxcurses_shared SHARED $<TARGET_OBJECTS:cxxcurses>)
#add_library(cxxcurses_static STATIC $<TARGET_OBJECTS:cxxcurses>)
