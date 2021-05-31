// ------------------------------------------------------------------------------------------------
// cxxcurses - color_pair.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_COLOR_PAIR_HPP
#define CXXCURSES_COLOR_PAIR_HPP

#include "color.hpp"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace cxxcurses
{
struct color_pair
{
    using type = std::pair<color, color>;

    color_pair( color fg = color::white, color bg = color::none )
    {
        auto pair { type { fg, bg } };

        if ( auto pos = std::find( std::begin( initialized_pairs ),
                                   std::end( initialized_pairs ),
                                   pair );
             pos != std::end( initialized_pairs ) )
        {
            pair_number = static_cast<unsigned long>(
                std::distance( std::begin( initialized_pairs ), pos ) + 1 );
        }
        else
        {
            ::init_pair( initialized_pairs.size() + 1,
                         static_cast<short>( fg ),
                         static_cast<short>( bg ) );
            initialized_pairs.push_back( pair );

            pair_number = initialized_pairs.size();
        }
    }

    explicit color_pair( unsigned long pair_num ) : pair_number { pair_num }
    {
        if ( pair_num > initialized_pairs.size() )
        {
            throw std::invalid_argument( "This color pair doesn't exist: " +
                                         std::to_string( pair_num ) );
        }
    }

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

inline std::vector<color_pair::type> color_pair::initialized_pairs {};

inline void apply_color( raw::window_ptr window, color_pair c ) noexcept
{
    ::wattron( window, COLOR_PAIR( c.pair_number ) );
}
} // namespace cxxcurses

#endif // CXXCURSES_COLOR_PAIR_HPP
