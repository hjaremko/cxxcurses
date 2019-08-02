#include "../../include/cxxcurses/output/print.hpp"

namespace cxxcurses
{

inline void print( const int y, const int x, const std::string& format ) noexcept
{
    mvwprintw( stdscr, y, x, format.c_str() );
}

inline void print( const int y, const int x, const glyph_string& format ) noexcept
{
    format.print( y, x );
}

inline void print( const int y, const std::string& format ) noexcept
{
    const auto x_centered{ ( getmaxx( stdscr ) - format.size() ) / 2 };
    mvwprintw( stdscr, y, x_centered, format.c_str() );
}

inline void print( const int y, const glyph_string& format ) noexcept
{
    const auto x_centered{ ( getmaxx( stdscr ) - format.size() ) / 2 };
    format.print( y, x_centered );
}

inline void print( const std::string& format ) noexcept
{
    const auto [y, x] = get_current_yx();
    mvwprintw( stdscr, y, x, format.c_str() );
}

inline void print( const glyph_string& format ) noexcept
{
    const auto [y, x] = get_current_yx();
    format.print( y, x );
}

}