// ------------------------------------------------------------------------------------------------
// cxxcurses - header-only ncurses wrapper
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_HPP
#define CXXCURSES_HPP

#include <algorithm>
#include <curses.h>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace cxxcurses
{

/*
 * Utility
 */
[[nodiscard]] std::pair<int, int> get_current_yx( WINDOW* = stdscr ) noexcept;
[[nodiscard]] std::pair<int, int> get_max_yx( WINDOW* = stdscr ) noexcept;
[[nodiscard]] auto get_attrs(::WINDOW*, int, int ) noexcept;

/*
 * Color and attributes
 */
enum class attribute;
enum class color : short;
extern const std::unordered_map<char, attribute> char_to_attribute;
extern const std::unordered_map<char, color> char_to_color;

struct color_pair;
void apply_color( WINDOW*, color_pair ) noexcept;

template <typename... Attrs>
void apply_attributes( WINDOW*, Attrs... ) noexcept;
void apply_attributes( WINDOW*, const std::vector<attribute>& ) noexcept;

/*
 * Formatted printing
 */
class glyph;
class glyph_string;
template <typename T>
glyph_string parse( glyph_string, const T& );

/*
 * Recursion bases
 */
// TODO: WINDOW* versions
void print( int y, int x, const std::string& ) noexcept;
void print( int y, int x, const glyph_string& ) noexcept;
void print( int y, const std::string& ) noexcept;
void print( int y, const glyph_string& ) noexcept;
void print( const std::string& ) noexcept;
void print( const glyph_string& ) noexcept;

/*
 * Move and print
 */
template <typename T, typename... Args>
constexpr void print( int, int, const glyph_string&, const T&, Args&&... ) noexcept;
template <typename... Args>
constexpr void print( int, int, std::string_view, Args&&... ) noexcept;

/*
 * Print at current cursor position
 */
template <typename T, typename... Args>
constexpr void print( const glyph_string&, const T&, Args&&... ) noexcept;
template <typename... Args>
constexpr void print( std::string_view, Args&&... ) noexcept;

/*
 * Print centered
 */
template <typename T, typename... Args>
constexpr void print( int, const glyph_string&, const T&, Args&&... args ) noexcept;

template <typename... Args>
constexpr void print( int, std::string_view, Args&&... args ) noexcept;

/*
 * Terminal settings
 */
class curses_error;
struct cursor;
void error_check( int, const std::string& );
int set_echo( bool ) noexcept;
struct initializer;

/*
 * Utility definitions
 */

[[nodiscard]] std::pair<int, int> get_current_yx( WINDOW* window ) noexcept
{
    auto y{ 0 };
    auto x{ 0 };
    getyx( window, y, x );

    return { y, x };
}

[[nodiscard]] std::pair<int, int> get_max_yx( WINDOW* window ) noexcept
{
    auto y{ 0 };
    auto x{ 0 };
    getmaxyx( window, y, x );

    return { y, x };
}

[[nodiscard]] auto get_attrs(::WINDOW* window, const int y, const int x ) noexcept
{
    const auto col{ mvwinch( window, y, x ) & A_COLOR };
    const auto attr{ mvwinch( window, y, x ) & A_ATTRIBUTES };

    return col | attr;
}

/*
 * Color and attributes definitions
 */
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

enum class color : short
{
    red = COLOR_RED,
    green = COLOR_GREEN,
    yellow = COLOR_YELLOW,
    blue = COLOR_BLUE,
    magenta = COLOR_MAGENTA,
    cyan = COLOR_CYAN,
    white = COLOR_WHITE,
    black = COLOR_BLACK,
};

const std::unordered_map<char, attribute> char_to_attribute{
    { 'N', attribute::normal },  { 'S', attribute::standout }, { 'U', attribute::underline },
    { 'R', attribute::reverse }, { 'X', attribute::blink },    { 'D', attribute::dim },
    { 'B', attribute::bold },    { 'P', attribute::protect },  { 'I', attribute::invisible }
};

const std::unordered_map<char, color> char_to_color{ { 'r', color::red },     { 'g', color::green },
                                                     { 'y', color::yellow },  { 'b', color::blue },
                                                     { 'm', color::magenta }, { 'c', color::cyan },
                                                     { 'w', color::white } };

struct color_pair
{
    color_pair( color fg, color bg = color::black );

    explicit color_pair( unsigned long pair_num ) : pair_number{ pair_num }
    {
        if ( pair_num > initialized_pairs.size() )
        {
            throw std::invalid_argument( "This color pair doesn't exist: " +
                                         std::to_string( pair_num ) );
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

    unsigned long pair_number{ 0 };
    static std::vector<type> initialized_pairs;
};

void apply_color( WINDOW* window, color_pair c ) noexcept
{
    ::wattron( window, COLOR_PAIR( c.pair_number ) );
}

template <typename... Attrs>
void apply_attributes( WINDOW* window, Attrs... attrs ) noexcept
{
    ::wattron( window, ( attrs | ... ) );
}

void apply_attributes( WINDOW* window, const std::vector<attribute>& attrs ) noexcept
{
    for ( const auto& attr : attrs )
    {
        ::wattron( window, static_cast<chtype>( attr ) );
    }
}

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
        int i{ 0 };

        for ( const auto& g : *this )
        {
            g.print( y, x + i++ );
        }
    }
};

// TODO: refactor and optimize
template <typename T>
glyph_string parse( glyph_string parsed, const T& arg )
{
    auto ss{ std::stringstream{} };
    auto glyph_color{ color_pair{ color::white } };
    auto glyph_attributes{ std::vector<attribute>{} };
    const auto opening_pos{ std::find( std::begin( parsed ), std::end( parsed ), glyph( '{' ) ) };
    const auto closing_pos{ std::find( std::begin( parsed ), std::end( parsed ), glyph( '}' ) ) };
    const auto format_len{ std::distance( opening_pos, closing_pos ) };

    if ( opening_pos != std::end( parsed ) && closing_pos != std::end( parsed ) &&
         opening_pos < closing_pos )
    {
        if ( auto attributes{ std::vector<glyph>( opening_pos, closing_pos ) };
             !attributes.empty() )
        {
            for ( const auto& flag : attributes )
            {
                if ( char_to_color.count( flag.data() ) )
                {
                    glyph_color = color_pair{ char_to_color.at( flag.data() ) };
                }

                if ( char_to_attribute.count( flag.data() ) )
                {
                    glyph_attributes.push_back( char_to_attribute.at( flag.data() ) );
                }
            }
        }

        ss << arg;
        auto parsed_arg{ glyph_string{ ss.str(), glyph_color } };

        for ( auto& g : parsed_arg )
        {
            g.set_attributes( glyph_attributes );
        }

        auto it{ parsed.insert(
            closing_pos + 1, std::begin( parsed_arg ), std::end( parsed_arg ) ) };
        parsed.erase( it - format_len - 1, it );
    }

    return parsed;
}

std::vector<color_pair::type> color_pair::initialized_pairs{};

color_pair::color_pair( color fg, color bg )
{
    auto pair{ type{ fg, bg } };

    if ( auto pos =
             std::find( std::begin( initialized_pairs ), std::end( initialized_pairs ), pair );
         pos != std::end( initialized_pairs ) )
    {
        pair_number =
            static_cast<unsigned long>( std::distance( std::begin( initialized_pairs ), pos ) + 1 );
    }
    else
    {
        ::init_pair(
            initialized_pairs.size() + 1, static_cast<short>( fg ), static_cast<short>( bg ) );
        initialized_pairs.push_back( pair );

        pair_number = initialized_pairs.size();
    }
}

/*
 * Print definitions
 */

inline void print( const int y, const int x, const std::string& format ) noexcept
{
    mvwprintw( stdscr, y, x, format.c_str() );
}

inline void print( const int y, const int x, const glyph_string& format ) noexcept
{
    format.print( y, x );
}

inline void print( const int y, const std::string& format ) noexcept
{
    const auto x_centered{ ( getmaxx( stdscr ) - format.size() ) / 2 };
    mvwprintw( stdscr, y, x_centered, format.c_str() );
}

inline void print( const int y, const glyph_string& format ) noexcept
{
    const auto x_centered{ ( getmaxx( stdscr ) - format.size() ) / 2 };
    format.print( y, x_centered );
}

inline void print( const std::string& format ) noexcept
{
    const auto [ y, x ] = get_current_yx();
    mvwprintw( stdscr, y, x, format.c_str() );
}

inline void print( const glyph_string& format ) noexcept
{
    const auto [ y, x ] = get_current_yx();
    format.print( y, x );
}

// move and print versions
template <typename T, typename... Args>
constexpr void print( const int y,
                      const int x,
                      const glyph_string& format_str,
                      const T& arg,
                      Args&&... args ) noexcept
{
    print( y, x, parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void
print( const int y, const int x, const std::string_view format_str, Args&&... args ) noexcept
{
    print( y, x, glyph_string{ format_str }, ( std::forward<Args>( args ) )... );
}

// print at current cursor position versions
template <typename T, typename... Args>
constexpr void print( const glyph_string& format_str, const T& arg, Args&&... args ) noexcept
{
    print( parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void print( const std::string_view format_str, Args&&... args ) noexcept
{
    print( glyph_string{ format_str }, ( std::forward<Args>( args ) )... );
}

// TODO: centered version
// centered versions
template <typename T, typename... Args>
constexpr void
print( const int y, const glyph_string& format_str, const T& arg, Args&&... args ) noexcept
{
    print( y, parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void print( const int y, const std::string_view format_str, Args&&... args ) noexcept
{
    print( y, glyph_string{ format_str }, ( std::forward<Args>( args ) )... );
}

/*
 * Terminal settings
 */
class curses_error : public std::runtime_error
{
public:
    explicit curses_error( const std::string& arg ) : runtime_error{ arg }
    {
    }
};

void error_check( int return_value, const std::string& what_msg )
{
    if ( return_value == ERR )
    {
        throw curses_error{ what_msg };
    }
}

struct cursor
{
    enum class visibility
    {
        invisible = 0,
        normal = 1,
        high = 2
    };

    static void set_visibility( visibility v )
    {
        error_check(::curs_set( static_cast<int>( v ) ),
                    "Your terminal does not support specified visibility mode" );
    }
};

int set_echo( bool mode ) noexcept
{
    if ( mode )
    {
        return ::echo();
    }

    return ::noecho();
}

struct initializer
{
    initializer()
    {
        ::initscr();
        set_echo( false );
        cursor::set_visibility( cursor::visibility::invisible );

        if (::has_colors() == FALSE )
        {
            print( "Your terminal does not support color" );
        }
        else
        {
            ::start_color();
            init_color_pairs();
        }
    }

    virtual ~initializer()
    {
        attrset( A_NORMAL );
        ::endwin();
        ::fflush( stdout );
    }

private:
    void init_color_pairs() const noexcept
    {
        color_pair( color::red, color::black );
        color_pair( color::green, color::black );
        color_pair( color::yellow, color::black );
        color_pair( color::blue, color::black );
        color_pair( color::magenta, color::black );
        color_pair( color::cyan, color::black );
        color_pair( color::white, color::black );
    }
};

} // namespace cxxcurses

#endif // CXXCURSES_HPP
