// ------------------------------------------------------------------------------------------------
// cxxcurses - misc.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_TERMINAL_HPP
#define CXXCURSES_TERMINAL_HPP

#include <curses.h>
#include <exception>
#include <stdexcept>
#include <string>

namespace cxxcurses
{
class curses_error : public std::runtime_error
{
public:
    explicit curses_error( const std::string& arg ) : runtime_error { arg }
    {
    }
};

inline void error_check( int return_value, const std::string& what_msg )
{
    if ( return_value == ERR )
    {
        throw curses_error { what_msg };
    }
}

inline auto set_echo( bool mode ) noexcept -> int
{
    if ( mode )
    {
        return ::echo();
    }

    return ::noecho();
}
} // namespace cxxcurses

#include "terminal/cursor.hpp"
#include "terminal/terminal.hpp"

#endif // CXXCURSES_TERMINAL_HPP
