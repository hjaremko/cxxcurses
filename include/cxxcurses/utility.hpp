// ------------------------------------------------------------------------------------------------
// cxxcurses - utility.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_UTILITY_HPP
#define CXXCURSES_UTILITY_HPP

#include <curses.h>

namespace cxxcurses
{
[[nodiscard]] std::pair<int, int> get_current_yx( WINDOW* window = stdscr ) noexcept
{
    auto y{ 0 };
    auto x{ 0 };
    getyx( window, y, x );

    return { y, x };
}

[[nodiscard]] std::pair<int, int> get_max_yx( WINDOW* window = stdscr ) noexcept
{
    auto y{ 0 };
    auto x{ 0 };
    getmaxyx( window, y, x );

    return { y, x };
}

[[nodiscard]] auto get_attrs(::WINDOW* window, const int y, const int x ) noexcept
{
    const auto col{ mvwinch( window, y, x ) & A_COLOR };
    const auto attr{ mvwinch( window, y, x ) & A_ATTRIBUTES };

    return col | attr;
}
} // namespace cxxcurses

#endif // CXXCURSES_UTILITY_HPP
