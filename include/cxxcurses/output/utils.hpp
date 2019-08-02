#ifndef CXXCURSES_PRINT_UTILS_HPP
#define CXXCURSES_PRINT_UTILS_HPP

#include <string>
#include <sstream>
#include <utility>
#include <algorithm>

#include <curses.h>

#include "glyph_string.hpp"
#include "attribute.hpp"
#include "color_pair.hpp"

namespace cxxcurses
{

[[nodiscard]] std::pair<int, int> get_current_yx( WINDOW* window = stdscr ) noexcept
{
    auto y { 0 };
    auto x { 0 };
    getyx( window, y, x );

    return { y, x };
}

[[nodiscard]] std::pair<int, int> get_max_yx( WINDOW* window = stdscr ) noexcept
{
    auto y { 0 };
    auto x { 0 };
    getmaxyx( window, y, x );

    return { y, x };
}

[[nodiscard]] auto get_attrs( ::WINDOW* window, const int y, const int x ) noexcept
{
    const auto col { mvwinch( window, y, x ) & A_COLOR };
    const auto attr { mvwinch( window, y, x ) & A_ATTRIBUTES };

    return col | attr;
}

}

#endif //CXXCURSES_PRINT_UTILS_HPP
