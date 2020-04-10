// ------------------------------------------------------------------------------------------------
// cxxcurses - cursor.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_TERMINAL_CURSOR_HPP
#define CXXCURSES_TERMINAL_CURSOR_HPP

namespace cxxcurses
{
struct cursor
{
    enum class visibility
    {
        invisible = 0,
        normal = 1,
        high = 2
    };

    static void set_visibility( visibility v )
    {
        error_check(
            ::curs_set( static_cast<int>( v ) ),
            "Your terminal does not support specified visibility mode" );
    }
};
} // namespace cxxcurses

#endif // CXXCURSES_TERMINAL_CURSOR_HPP
