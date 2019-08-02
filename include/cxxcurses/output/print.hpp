#ifndef CXXCURSES_PRINT_PRINT_HPP
#define CXXCURSES_PRINT_PRINT_HPP

#include "utils.hpp"

namespace cxxcurses
{

//TODO: WINDOW* versions
void print( int y, int x, const std::string& format ) noexcept;

void print( int y, int x, const glyph_string& format ) noexcept;

void print( int y, const std::string& format ) noexcept;

void print( int y, const glyph_string& format ) noexcept;

void print( const std::string& format ) noexcept;

void print( const glyph_string& format ) noexcept;

//move and print versions
template <typename T, typename... Args>
constexpr void print( const int y, const int x, const glyph_string& format_str, const T& arg, Args&& ... args ) noexcept
{
    print( y, x, parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void print( const int y, const int x, const std::string_view format_str, Args&& ... args ) noexcept
{
    print( y, x, glyph_string { format_str }, ( std::forward<Args>( args ) )... );
}

//print at current cursor position versions
template <typename T, typename... Args>
constexpr void print( const glyph_string& format_str, const T& arg, Args&& ... args ) noexcept
{
    print( parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void print( const std::string_view format_str, Args&& ... args ) noexcept
{
    print( glyph_string { format_str }, ( std::forward<Args>( args ) )... );
}

//TODO: centered version
//centered versions
template <typename T, typename... Args>
constexpr void print( const int y, const glyph_string& format_str, const T& arg, Args&& ... args ) noexcept
{
    print( y, parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void print( const int y, const std::string_view format_str, Args&& ... args ) noexcept
{
    print( y, glyph_string { format_str }, ( std::forward<Args>( args ) )... );
}

}
#endif //CXXCURSES_PRINT_PRINT_HPP
