// ------------------------------------------------------------------------------------------------
// cxxcurses - terminal.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_TERMINAL_INITIALIZER_HPP
#define CXXCURSES_TERMINAL_INITIALIZER_HPP

#include <cxxcurses/print.hpp>
#include <cxxcurses/widgets.hpp>

#include <curses.h>

namespace cxxcurses
{
struct terminal
{
    terminal()
    {
        ::initscr();
        ::keypad( stdscr, TRUE );
        set_echo( false );
        cursor::set_visibility( cursor::visibility::invisible );

        if ( !::has_colors() )
        {
            main_win << format( "Your terminal does not support color" );
        }
        else
        {
            ::start_color();
            ::use_default_colors();
            init_color_pairs();
        }
    }

    terminal( const terminal& ) = delete;
    terminal( terminal&& ) = delete;
    auto operator=( const terminal& ) -> terminal& = delete;
    auto operator=( terminal&& ) -> terminal& = delete;

    ~terminal()
    {
        attrset( A_NORMAL );
        ::endwin();
        ::fflush( stdout );
    }

    static inline widget::stdscr_wrapper main_win {};

private:
    static void init_color_pairs() noexcept
    {
        color_pair( color::red, color::none );
        color_pair( color::green, color::none );
        color_pair( color::yellow, color::none );
        color_pair( color::blue, color::none );
        color_pair( color::magenta, color::none );
        color_pair( color::cyan, color::none );
        color_pair( color::white, color::none );
    }
};
} // namespace cxxcurses

#endif // CXXCURSES_TERMINAL_INITIALIZER_HPP
