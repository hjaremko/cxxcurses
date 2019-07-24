#ifndef CXXCURSES_PRINT_COLOR_HPP
#define CXXCURSES_PRINT_COLOR_HPP

#include <unordered_map>

#include <curses.h>

namespace cxxcurses
{

enum class color : chtype
{
    red = 1,
    green = 2,
    yellow = 3,
    blue = 4,
    magenta = 5,
    cyan = 6,
    white = 7
};

std::unordered_map<char, color> char_to_color{
        { 'r', color::red },
        { 'g', color::green },
        { 'y', color::yellow },
        { 'b', color::blue },
        { 'm', color::magenta },
        { 'c', color::cyan },
        { 'w', color::white }
};

}

#endif //CXXCURSES_PRINT_COLOR_HPP
