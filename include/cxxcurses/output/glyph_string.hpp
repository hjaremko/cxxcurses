#ifndef CXXCURSES_PRINT_GLYPH_STRING_HPP
#define CXXCURSES_PRINT_GLYPH_STRING_HPP

#include <vector>

#include "color.hpp"
#include "glyph.hpp"

namespace cxxcurses
{

class glyph_string : public std::vector<glyph>
{
public:
    explicit glyph_string(const std::string& string, color_pair color = color::white )
    {
        for ( const auto& c : string )
        {
            emplace_back( c, color );
        }
    }

    void print( const int y, const int x ) const noexcept
    {
        int i{ 0 };

        for ( const auto& g : *this )
        {
            g.print( y, x + i++ );
        }
    }
};

}

#endif //CXXCURSES_PRINT_GLYPH_STRING_HPP
