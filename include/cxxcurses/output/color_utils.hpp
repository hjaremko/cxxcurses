#ifndef CXXCURSES_PRINT_COLOR_UTILS_HPP
#define CXXCURSES_PRINT_COLOR_UTILS_HPP

#include <curses.h>

#include "color.hpp"
#include "utils.hpp"
#include "attribute.hpp"

namespace cxxcurses
{

void set_colors( WINDOW* window, color c ) noexcept
{
    ::wattron( window, COLOR_PAIR( c ) );
}

template<typename ...Colors>
//TODO: WINDOW* -> cxxcurses::window
void set_colors( WINDOW* window, color c, Colors... colors ) noexcept
{
    set_colors( window, c );
    set_colors( window, colors... );
}

template<typename ...Attrs>
void set_attributes( WINDOW* window, Attrs... attrs ) noexcept
{
    ::wattron( window, (attrs | ...) );
}

void set_attributes( WINDOW* window, const std::vector<attribute>& attrs ) noexcept
{
    for ( const auto& attr : attrs )
    {
        ::wattron( window, static_cast<chtype>( attr ) );
    }
}

}

#endif //CXXCURSES_PRINT_COLOR_UTILS_HPP
