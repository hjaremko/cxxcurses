// ------------------------------------------------------------------------------------------------
// cxxcurses - glyph.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_GLYPH_HPP
#define CXXCURSES_GLYPH_HPP

#include "attribute.hpp"
#include "color_pair.hpp"

#include <utility>

namespace cxxcurses
{
class glyph
{
public:
    explicit glyph( char c, color_pair color = color::white )
        : char_ { c }, color_ { color }
    {
    }

    explicit glyph( char c,
                    color_pair color,
                    std::vector<attribute> attributes )
        : char_ { c }, color_ { color }, attributes_ { std::move( attributes ) }
    {
    }

    void print( raw::window_ptr window ) const noexcept
    {
        apply_color( window, color_ );
        apply_attributes( window, attributes_ );
        waddch( window, static_cast<chtype>( char_ ) );
        wattrset( window, A_NORMAL );
    }

    [[nodiscard]] constexpr auto data() const noexcept -> char
    {
        return char_;
    }

    operator char() const noexcept
    {
        return char_;
    }

    void add_attribute( const attribute attr )
    {
        attributes_.push_back( attr );
    }

    void set_attributes( const std::vector<attribute>& attributes ) noexcept
    {
        attributes_ = attributes;
    }

    friend auto operator==( const glyph& lhs, const glyph& rhs ) -> bool
    {
        return lhs.char_ == rhs.char_ && lhs.color_ == rhs.color_;
    }

    friend auto operator!=( const glyph& lhs, const glyph& rhs ) -> bool
    {
        return !( rhs == lhs );
    }

    friend auto operator<( const glyph& lhs, const glyph& rhs ) -> bool
    {
        return std::tie( lhs.char_, lhs.color_ ) <
               std::tie( rhs.char_, rhs.color_ );
    }

    friend auto operator>( const glyph& lhs, const glyph& rhs ) -> bool
    {
        return rhs < lhs;
    }

    friend auto operator<=( const glyph& lhs, const glyph& rhs ) -> bool
    {
        return !( rhs < lhs );
    }

    friend auto operator>=( const glyph& lhs, const glyph& rhs ) -> bool
    {
        return !( lhs < rhs );
    }

private:
    char char_ { '\0' };
    color_pair color_;
    std::vector<attribute> attributes_;
};
} // namespace cxxcurses

#endif // CXXCURSES_GLYPH_HPP
