#include "cxxcurses/output/color_pair.hpp"

namespace cxxcurses
{

std::vector<color_pair::type> color_pair::initialized_pairs {};

color_pair::color_pair( color fg, color bg )
{
    auto pair { type { fg, bg } };

    if ( auto pos = std::find( std::begin( initialized_pairs ), std::end( initialized_pairs ), pair );
            pos != std::end( initialized_pairs ) )
    {
        pair_number = static_cast<unsigned long>(std::distance( std::begin( initialized_pairs ), pos ) + 1 );
    }
    else
    {
        ::init_pair( initialized_pairs.size() + 1,
                     static_cast<short>(fg), static_cast<short>(bg) );
        initialized_pairs.push_back( pair );

        pair_number = initialized_pairs.size();
    }
}

}
