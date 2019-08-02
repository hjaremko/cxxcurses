#ifndef CXXCURSES_PRINT_COLOR_HPP
#define CXXCURSES_PRINT_COLOR_HPP

#include <unordered_map>

#include <curses.h>

namespace cxxcurses
{

enum class color : short
{
    red = COLOR_RED,
    green = COLOR_GREEN,
    yellow = COLOR_YELLOW,
    blue = COLOR_BLUE,
    magenta = COLOR_MAGENTA,
    cyan = COLOR_CYAN,
    white = COLOR_WHITE,
    black = COLOR_BLACK,
};

extern const std::unordered_map<char, color> char_to_color;

}

#endif //CXXCURSES_PRINT_COLOR_HPP
