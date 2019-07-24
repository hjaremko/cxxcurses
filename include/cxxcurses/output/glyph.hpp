#ifndef CXXCURSES_PRINT_GLYPH_HPP
#define CXXCURSES_PRINT_GLYPH_HPP

#include "color.hpp"
#include "color_utils.hpp"
#include "glyph_string.hpp"
#include "attribute.hpp"

namespace cxxcurses
{

class glyph
{
public:
    explicit glyph( char c, color color = color::white ) : char_( c ), color_( color )
    {
    }

    void print( const int y, const int x ) const noexcept
    {
        const auto window = stdscr;
        set_colors( window, color_ );
        cxxcurses::set_attributes( window, attributes_ );
        mvwaddch( window, y, x, static_cast<chtype>(char_) );
        wattrset( window, A_NORMAL );
    }

    constexpr char data() const noexcept
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
    color color_{ color::white };
    std::vector<attribute> attributes_;
};

}

#endif //CXXCURSES_PRINT_GLYPH_HPP
