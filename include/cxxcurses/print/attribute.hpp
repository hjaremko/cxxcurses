// ------------------------------------------------------------------------------------------------
// cxxcurses - attribute.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_ATTRIBUTE_HPP
#define CXXCURSES_ATTRIBUTE_HPP

#include <unordered_map>

namespace cxxcurses
{
enum class attribute
{
    normal = A_NORMAL,
    standout = A_STANDOUT,
    underline = A_UNDERLINE,
    reverse = A_REVERSE,
    blink = A_BLINK,
    dim = A_DIM,
    bold = A_BOLD,
    protect = A_PROTECT,
    invisible = A_INVIS
};

static const std::unordered_map<char, attribute> char_to_attribute {
    { 'N', attribute::normal },    { 'S', attribute::standout },
    { 'U', attribute::underline }, { 'R', attribute::reverse },
    { 'X', attribute::blink },     { 'D', attribute::dim },
    { 'B', attribute::bold },      { 'P', attribute::protect },
    { 'I', attribute::invisible }
};

inline attribute to_attribute( char c )
{
    return char_to_attribute.at( c );
}

template <typename... Attrs>
inline void apply_attributes( raw::window_ptr window, Attrs... attrs ) noexcept
{
    ::wattron( window, ( attrs | ... ) );
}

inline void apply_attributes( raw::window_ptr window,
                              const std::vector<attribute>& attrs ) noexcept
{
    for ( const auto& attr : attrs )
    {
        ::wattron( window, static_cast<chtype>( attr ) );
    }
}
} // namespace cxxcurses

#endif // CXXCURSES_ATTRIBUTE_HPP
