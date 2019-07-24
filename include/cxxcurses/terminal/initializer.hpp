#ifndef CXXCURSES_INIT_HPP
#define CXXCURSES_INIT_HPP

#include <stdexcept>

#include "../output/print.hpp"

namespace cxxcurses::terminal
{

struct initializer
{
    initializer()
    {
        ::initscr();
        ::noecho();
        ::curs_set( 0 );

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
        fflush( stdout );
    }

private:
    void init_color_pairs() const noexcept
    {
        ::init_pair( static_cast<chtype>(color::red), COLOR_RED, COLOR_BLACK );
        ::init_pair( static_cast<chtype>(color::green), COLOR_GREEN, COLOR_BLACK );
        ::init_pair( static_cast<chtype>(color::yellow), COLOR_YELLOW, COLOR_BLACK );
        ::init_pair( static_cast<chtype>(color::blue), COLOR_BLUE, COLOR_BLACK );
        ::init_pair( static_cast<chtype>(color::magenta), COLOR_MAGENTA, COLOR_BLACK );
        ::init_pair( static_cast<chtype>(color::cyan), COLOR_CYAN, COLOR_BLACK );
        ::init_pair( static_cast<chtype>(color::white), COLOR_WHITE, COLOR_BLACK );
    }
};

}
#endif //CXXCURSES_INIT_HPP
