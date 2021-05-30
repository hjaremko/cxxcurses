// ------------------------------------------------------------------------------------------------
// cxxcurses - glyph_string.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2020 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_GLYPH_STRING_HPP
#define CXXCURSES_GLYPH_STRING_HPP

#include "color_pair.hpp"
#include "glyph.hpp"

#include <algorithm>
#include <sstream>
#include <string_view>
#include <vector>

namespace cxxcurses
{
class glyph_string : public std::vector<glyph>
{
public:
    glyph_string() = default;
    glyph_string( const glyph_string& ) = default;
    glyph_string( glyph_string&& ) = default;
    auto operator=( const glyph_string& ) -> glyph_string& = default;
    auto operator=( glyph_string&& ) -> glyph_string& = default;
    ~glyph_string() = default;

    explicit glyph_string( const std::string_view& string,
                           color_pair color = color::white )
    {
        for ( const auto& c : string )
        {
            emplace_back( c, color );
        }
    }

    void print( raw::window_ptr win ) const noexcept
    {
        for ( const auto& g : *this )
        {
            g.print( win );
        }
    }
};

inline auto parse_arg( std::string_view /*to_parse*/, glyph_string& /*parsed*/ )
    -> glyph_string
{
    return {};
}

template <typename T, typename... Args>
inline auto parse_arg( std::string_view to_parse,
                       glyph_string& parsed,
                       const T& arg,
                       Args&&... args ) -> glyph_string
{
    auto colors { color_pair { color::white } };
    auto attributes { std::vector<attribute> {} };

    size_t position = 0;
    for ( auto ch = std::begin( to_parse ); *ch != '}'; ++ch, ++position )
    {
        if ( char_to_color.count( *ch ) )
        {
            colors = color_pair { to_color( *ch ) };
        }

        if ( char_to_attribute.count( *ch ) )
        {
            attributes.push_back( to_attribute( *ch ) );
        }
    }

    auto ss { std::stringstream {} };
    ss << arg;
    auto parsed_arg { cxxcurses::glyph_string { ss.str(), colors } };

    for ( auto& g : parsed_arg )
    {
        g.set_attributes( attributes );
    }

    std::move(
        parsed_arg.begin(), parsed_arg.end(), std::back_inserter( parsed ) );
    to_parse.remove_prefix( std::min( position + 1, to_parse.size() ) );

    return parse( to_parse, parsed, std::forward<Args>( args )... );
}

template <typename... Args>
inline auto parse( std::string_view to_parse,
                   glyph_string& parsed,
                   Args&&... args ) -> glyph_string
{
    size_t position = 0;
    for ( auto ch : to_parse )
    {
        if ( ch != '{' )
        {
            parsed.emplace_back( ch );
        }
        else
        {
            to_parse.remove_prefix( position );
            return parse_arg( to_parse, parsed, std::forward<Args>( args )... );
        }

        ++position;
    }

    return parsed;
}

} // namespace cxxcurses
#endif // CXXCURSES_GLYPH_STRING_HPP
