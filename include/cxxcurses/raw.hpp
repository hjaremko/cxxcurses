// ------------------------------------------------------------------------------------------------
// cxxcurses - raw.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2020 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_RAW_HPP
#define CXXCURSES_RAW_HPP

#include <curses.h>
#include <memory>

namespace cxxcurses::raw
{
struct window_deleter;

using window = ::WINDOW;
using window_ptr = window*;
using window_unique_ptr = std::unique_ptr<window, window_deleter>;

struct window_deleter
{
    void operator()( window_ptr window ) const
    {
        ::wborder( window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' );
        ::wclear( window );
        ::wrefresh( window );
        ::delwin( window );
    }
};

[[nodiscard]] inline auto
get_attrs( window_ptr window, const int y, const int x ) noexcept
{
    const auto col { mvwinch( window, y, x ) & A_COLOR };
    const auto attr { mvwinch( window, y, x ) & A_ATTRIBUTES };

    return col | attr;
}

} // namespace cxxcurses::raw

#endif // CXXCURSES_RAW_HPP
