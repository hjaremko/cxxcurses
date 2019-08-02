#ifndef CXXCURSES_PRINT_GLYPH_STRING_HPP
#define CXXCURSES_PRINT_GLYPH_STRING_HPP

#include <vector>
#include <sstream>

#include "color.hpp"
#include "color_pair.hpp"
#include "glyph.hpp"

namespace cxxcurses
{

class glyph_string : public std::vector<glyph>
{
public:
    explicit glyph_string( const std::string_view& string, color_pair color = color::white )
    {
        for ( const auto& c : string )
        {
            emplace_back( c, color );
        }
    }

    void print( const int y, const int x ) const noexcept
    {
        int i { 0 };

        for ( const auto& g : *this )
        {
            g.print( y, x + i++ );
        }
    }
};

//TODO: should be moved to glyph_string i guess
template <typename T>
glyph_string parse( glyph_string parsed, const T& arg )
{
    auto ss { std::stringstream {} };
    auto glyph_color { color_pair { color::white } };
    auto glyph_attributes { std::vector<attribute> {} };
    const auto opening_pos { std::find( std::begin( parsed ), std::end( parsed ), glyph( '{' ) ) };
    const auto closing_pos { std::find( std::begin( parsed ), std::end( parsed ), glyph( '}' ) ) };
    const auto format_len { std::distance( opening_pos, closing_pos ) };

    if ( opening_pos != std::end( parsed ) && closing_pos != std::end( parsed ) && opening_pos < closing_pos )
    {
        if ( auto attributes { std::vector<glyph>( opening_pos, closing_pos ) }; !attributes.empty() )
        {
            for ( const auto& flag : attributes )
            {
                if ( char_to_color.count( flag.data() ) )
                {
                    glyph_color = color_pair { char_to_color.at( flag.data() ) };
                }

                if ( char_to_attribute.count( flag.data() ) )
                {
                    glyph_attributes.push_back( char_to_attribute[ flag.data() ] );
                }
            }
        }

        ss << arg;
        auto parsed_arg { glyph_string { ss.str(), glyph_color } };

        for ( auto& g : parsed_arg )
        {
            g.set_attributes( glyph_attributes );
        }

        auto it { parsed.insert( closing_pos + 1, std::begin( parsed_arg ), std::end( parsed_arg ) ) };
        parsed.erase( it - format_len - 1, it );
    }

    return parsed;
}

}

#endif //CXXCURSES_PRINT_GLYPH_STRING_HPP
