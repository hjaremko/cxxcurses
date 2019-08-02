#ifndef CXXCURSES_INIT_HPP
#define CXXCURSES_INIT_HPP

#include "../cxxcurses.hpp"
#include "../output/print.hpp"

namespace cxxcurses::terminal
{

struct initializer
{
    initializer()
    {
        ::initscr();
        set_echo( false );
        cursor::set_visibility( cursor::visibility::invisible );

        if ( ::has_colors() == FALSE )
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
        color_pair(color::red, color::black);
        color_pair(color::green, color::black);
        color_pair(color::yellow, color::black);
        color_pair(color::blue, color::black);
        color_pair(color::magenta, color::black);
        color_pair(color::cyan, color::black);
        color_pair(color::white, color::black);
    }
};

}
#endif //CXXCURSES_INIT_HPP
