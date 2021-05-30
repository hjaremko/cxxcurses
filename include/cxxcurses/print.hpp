// ------------------------------------------------------------------------------------------------
// cxxcurses - print.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2020 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_PRINT_HPP
#define CXXCURSES_PRINT_HPP

#include "print/glyph_string.hpp"
#include "widgets.hpp"

#include <optional>
#include <ostream>

namespace cxxcurses
{

struct printer
{
    template <typename... Args>
    auto operator()( std::string_view str, Args&&... args ) -> printer
    {
        parse( str, format_str, ( std::forward<Args>( args ) )... );
        return *this;
    }

    using coords_t = std::pair<std::optional<int>, std::optional<int>>;
    const coords_t coords {};
    glyph_string format_str {};
};

// move and print
inline auto format( const int y, const int x ) -> printer
{
    return { std::make_pair( y, x ) };
}

// centered
inline auto format( const int y ) -> printer
{
    return { std::make_pair( y, std::nullopt ) };
}

template <typename... Args>
inline auto format( std::string_view str, Args&&... args ) -> printer
{
    auto format_str { glyph_string {} };
    parse( str, format_str, ( std::forward<Args>( args ) )... );
    return printer { std::make_pair( std::nullopt, std::nullopt ), format_str };
}

inline auto operator<<( const widget::window_interface& w,
                        const printer& formatted )
    -> const widget::window_interface&
{
    const auto x =
        formatted.coords.second
            ? *formatted.coords.second
            : ( w.max_yx().second - formatted.format_str.size() ) / 2;

    const auto y =
        formatted.coords.first ? *formatted.coords.first : w.current_yx().first;

    w.move_cursor( y, x );
    formatted.format_str.print( w.get() );
    return w;
}

} // namespace cxxcurses
#endif // CXXCURSES_PRINT_HPP
