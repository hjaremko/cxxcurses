// ------------------------------------------------------------------------------------------------
// cxxcurses - print.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_PRINT_HPP
#define CXXCURSES_PRINT_HPP

#include "print/glyph_string.hpp"
#include "utility.hpp"

namespace cxxcurses
{
// TODO: WINDOW*(cxxcurses::window) versions
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
    const auto [ y, x ] = get_current_yx();
    mvwprintw( stdscr, y, x, format.c_str() );
}

inline void print( const glyph_string& format ) noexcept
{
    const auto [ y, x ] = get_current_yx();
    format.print( y, x );
}

// move and print versions
template <typename T, typename... Args>
constexpr void print( const int y,
                      const int x,
                      const glyph_string& format_str,
                      const T& arg,
                      Args&&... args ) noexcept
{
    print( y, x, parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void
print( const int y, const int x, const std::string_view format_str, Args&&... args ) noexcept
{
    print( y, x, glyph_string{ format_str }, ( std::forward<Args>( args ) )... );
}

// print at current cursor position versions
template <typename T, typename... Args>
constexpr void print( const glyph_string& format_str, const T& arg, Args&&... args ) noexcept
{
    print( parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void print( const std::string_view format_str, Args&&... args ) noexcept
{
    print( glyph_string{ format_str }, ( std::forward<Args>( args ) )... );
}

// TODO: centered version
// centered versions
template <typename T, typename... Args>
constexpr void
print( const int y, const glyph_string& format_str, const T& arg, Args&&... args ) noexcept
{
    print( y, parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void print( const int y, const std::string_view format_str, Args&&... args ) noexcept
{
    print( y, glyph_string{ format_str }, ( std::forward<Args>( args ) )... );
}
} // namespace cxxcurses

#endif // CXXCURSES_PRINT_HPP
