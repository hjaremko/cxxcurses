#ifndef CXXCURSES_PRINT_ATTRIBUTE_HPP
#define CXXCURSES_PRINT_ATTRIBUTE_HPP

#include <unordered_map>

#include <curses.h>

namespace cxxcurses
{

enum class attribute
{
    normal = A_NORMAL,
    standout = A_STANDOUT,
    underline = A_UNDERLINE,
    reverse = A_REVERSE,
    blink = A_BLINK,
    dim = A_DIM,
    bold = A_BOLD,
    protect = A_PROTECT,
    invisible = A_INVIS
};

extern std::unordered_map<char, attribute> char_to_attribute;

}
#endif //CXXCURSES_PRINT_ATTRIBUTE_HPP
