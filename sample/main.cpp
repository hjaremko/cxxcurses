#include "cxxcurses/cxxcurses.hpp"

#include <ostream>
#include <string>

class custom_type
{
public:
    friend auto operator<<( std::ostream& os, const custom_type& type )
        -> std::ostream&
    {
        return os << "str: " << type.str << " pi: " << type.pi;
    }

private:
    const std::string str { "user defined" };
    const double pi { 3.14 };
};

auto main() -> int
{
    namespace cc = cxxcurses;
    const auto& main_win = cc::terminal::main_win;
    cc::terminal init;

    const auto hello_string { std::string { "Hello, world" } };

    main_win << cc::format( 4 )( "C++ curses centered example" );
    main_win << cc::format( 5, 6 )(
        "Here comes {rR} {gB} {bB}!!!", "multi", "colored", hello_string );
    main_win << cc::format( 6, 6 )( "Supports {R} types!", custom_type {} );

    auto some_window { cc::widget::window { { 10, 5, 5, 30 },
                                            cc::terminal::main_win } };

    some_window << cc::format( 2, 2 )( "Hello from sub-window!" );
    some_window.get_char();

    return 0;
}
