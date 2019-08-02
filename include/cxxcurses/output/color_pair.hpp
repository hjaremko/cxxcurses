#ifndef CXXCURSES_OUTPUT_COLOR_PAIR_HPP
#define CXXCURSES_OUTPUT_COLOR_PAIR_HPP

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

#include <curses.h>

#include "color.hpp"

namespace cxxcurses
{

struct color_pair
{
    color_pair( color fg, color bg = color::black );

    explicit color_pair( unsigned long pair_num ) : pair_number { pair_num }
    {
        if ( pair_num > initialized_pairs.size() )
        {
            throw std::invalid_argument( "This color pair doesn't exist: " + std::to_string( pair_num ) );
        }
    }

    using type = std::pair<color, color>;

    friend bool operator==( const color_pair& lhs, const color_pair& rhs )
    {
        return lhs.pair_number == rhs.pair_number;
    }

    friend bool operator!=( const color_pair& lhs, const color_pair& rhs )
    {
        return !( rhs == lhs );
    }

    friend bool operator<( const color_pair& lhs, const color_pair& rhs )
    {
        return lhs.pair_number < rhs.pair_number;
    }

    friend bool operator>( const color_pair& lhs, const color_pair& rhs )
    {
        return rhs < lhs;
    }

    friend bool operator<=( const color_pair& lhs, const color_pair& rhs )
    {
        return !( rhs < lhs );
    }

    friend bool operator>=( const color_pair& lhs, const color_pair& rhs )
    {
        return !( lhs < rhs );
    }

    unsigned long pair_number { 0 };
    static std::vector<type> initialized_pairs;
};

}

#endif //CXXCURSES_OUTPUT_COLOR_PAIR_HPP
