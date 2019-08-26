// ------------------------------------------------------------------------------------------------
// cxxcurses - initializer.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_TERMINAL_INITIALIZER_HPP
#define CXXCURSES_TERMINAL_INITIALIZER_HPP

namespace cxxcurses
{
struct initializer
{
    initializer()
    {
        ::initscr();
        set_echo( false );
        cursor::set_visibility( cursor::visibility::invisible );

        if (::has_colors() == FALSE )
        {
            print( "Your terminal does not support color" );
        }
        else
        {
            ::start_color();
            init_color_pairs();
        }
    }

    virtual ~initializer()
    {
        attrset( A_NORMAL );
        ::endwin();
        ::fflush( stdout );
    }

private:
    void init_color_pairs() const noexcept
    {
        color_pair( color::red, color::black );
        color_pair( color::green, color::black );
        color_pair( color::yellow, color::black );
        color_pair( color::blue, color::black );
        color_pair( color::magenta, color::black );
        color_pair( color::cyan, color::black );
        color_pair( color::white, color::black );
    }
};
} // namespace cxxcurses

#endif // CXXCURSES_TERMINAL_INITIALIZER_HPP
