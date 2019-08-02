#include <stdexcept>
#include <utility>

#ifndef CXXCURSES_TERMINAL_CURSOR_VISIBILITY_HPP
#define CXXCURSES_TERMINAL_CURSOR_VISIBILITY_HPP

namespace cxxcurses::terminal
{
class curses_error : public std::runtime_error
{
public:
    explicit curses_error( const std::string& arg ) : runtime_error { arg }
    {
    }
};

void error_check( int return_value, const std::string& what_msg )
{
    if ( return_value == ERR )
    {
        throw curses_error { what_msg };
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
        error_check( ::curs_set( static_cast<int>( v ) ),
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
}

#endif //CXXCURSES_TERMINAL_CURSOR_VISIBILITY_HPP
