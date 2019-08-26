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

namespace cxxcurses
{
class glyph
{
public:
    explicit glyph( char c, color_pair color = color::white ) : char_{ c }, color_{ color }
    {
    }

    void print( const int y, const int x ) const noexcept
    {
        const auto window = stdscr;
        apply_color( window, color_ );
        apply_attributes( window, attributes_ );
        mvwaddch( window, y, x, static_cast<chtype>( char_ ) );
        wattrset( window, A_NORMAL );
    }

    [[nodiscard]] constexpr char data() const noexcept
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

    friend bool operator==( const glyph& lhs, const glyph& rhs )
    {
        return lhs.char_ == rhs.char_ && lhs.color_ == rhs.color_;
    }

    friend bool operator!=( const glyph& lhs, const glyph& rhs )
    {
        return !( rhs == lhs );
    }

    friend bool operator<( const glyph& lhs, const glyph& rhs )
    {
        return std::tie( lhs.char_, lhs.color_ ) < std::tie( rhs.char_, rhs.color_ );
    }

    friend bool operator>( const glyph& lhs, const glyph& rhs )
    {
        return rhs < lhs;
    }

    friend bool operator<=( const glyph& lhs, const glyph& rhs )
    {
        return !( rhs < lhs );
    }

    friend bool operator>=( const glyph& lhs, const glyph& rhs )
    {
        return !( lhs < rhs );
    }

private:
    char char_{ '\0' };
    color_pair color_;
    std::vector<attribute> attributes_;
};
} // namespace cxxcurses

#endif // CXXCURSES_GLYPH_HPP
