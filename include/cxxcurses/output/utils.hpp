#ifndef CXXCURSES_PRINT_UTILS_HPP
#define CXXCURSES_PRINT_UTILS_HPP

#include <string>
#include <sstream>
#include <utility>
#include <algorithm>

#include <curses.h>

#include "glyph_string.hpp"
#include "attribute.hpp"

namespace cxxcurses
{

[[nodiscard]] std::pair<int, int> get_current_yx( WINDOW* window = stdscr ) noexcept
{
    auto y{ 0 };
    auto x{ 0 };
    getyx( window, y, x );

    return std::make_pair( y, x );
}

[[nodiscard]] std::pair<int, int> get_max_yx( WINDOW* window = stdscr ) noexcept
{
    auto y{ 0 };
    auto x{ 0 };
    getmaxyx( window, y, x );

    return std::make_pair( y, x );
}

[[nodiscard]] auto get_attrs( ::WINDOW* window, const int y, const int x )
{
    const auto col = mvwinch( window, y, x ) & A_COLOR;
    const auto attr = mvwinch( window, y, x ) & A_ATTRIBUTES;

    return col | attr;
}

//TODO: should be moved to glyph_string i guess
template<typename T>
glyph_string parse( glyph_string parsed, const T& arg )
{
    auto ss{ std::stringstream{} };
    auto glyph_color{ color::white };
    auto glyph_attributes{ std::vector<attribute>{} };
    const auto opening_pos{ std::find( std::begin( parsed ), std::end( parsed ), glyph( '{' ) ) };
    const auto closing_pos{ std::find( std::begin( parsed ), std::end( parsed ), glyph( '}' ) ) };
    const auto format_len{ std::distance( opening_pos, closing_pos ) };

    if ( opening_pos != std::end( parsed ) && closing_pos != std::end( parsed ) && opening_pos < closing_pos )
    {
        auto attributes = std::vector<glyph>( opening_pos, closing_pos );

        if ( !attributes.empty() )
        {
            for ( const auto& flag : attributes )
            {
                if ( char_to_color.count( flag.data() ) )
                {
                    glyph_color = char_to_color[ flag.data() ];
                }

                if ( char_to_attribute.count( flag.data() ) )
                {
                    glyph_attributes.push_back( char_to_attribute[ flag.data() ] );
                }
            }
        }

        ss << arg;
        auto parsed_arg{ glyph_string{ ss.str(), glyph_color } };

        for ( auto& g : parsed_arg )
        {
            g.set_attributes( glyph_attributes );
        }

        auto it{ parsed.insert( closing_pos + 1, parsed_arg.begin(), parsed_arg.end() ) };
        parsed.erase( it - format_len - 1, it );
    }

    return parsed;
}

}

#endif //CXXCURSES_PRINT_UTILS_HPP
