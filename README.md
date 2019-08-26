# cxxcurses

<p align="center">
  <img src="https://i.imgur.com/rW7aM3J.png" alt="Example"/>
</p>

Header-only C++ wrapper aiming to provide more friendly interface
to the most used (at least by me) functions of ncurses instead of not so fun to use C interface.

```cpp
#include "cxxcurses.hpp"

#include <ostream>
#include <string>

class custom_type
{
    const std::string str{ "user defined" };
    const double pi{ 3.14 };

public:
    friend std::ostream& operator<<( std::ostream& os, const custom_type& type )
    {
        return os << "str: " << type.str << " pi: " << type.pi;
    }
};

int main()
{
    cxxcurses::initializer init;
    const auto hello_string{ std::string{ "Hello, world" } };

    cxxcurses::print( 4, "C++ curses centered example" );
    cxxcurses::print( 5, 6, "Here comes {rR} {gB} {bB}!!!", "multi", "colored", hello_string );
    cxxcurses::print( 6, 6, "Supports {R} types!", custom_type{} );

    ::getch();
    return 0;
}

```


### Building with cxxcurses

You need to have `ncurses` installed on your system (in case of Windows `pdcurses`) and link it to your project as usual.
