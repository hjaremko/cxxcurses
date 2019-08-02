#ifndef CXXCURSES_PRINT_COLOR_HPP
#define CXXCURSES_PRINT_COLOR_HPP

#include <unordered_map>

#include <curses.h>

namespace cxxcurses
{

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

struct color_pair
{
    color_pair( color fg, color bg = color::black )
    {
        auto pair { type {fg, bg } };

        if (auto pos = std::find(std::begin(initialized_pairs), std::end(initialized_pairs), pair);
            pos != std::end(initialized_pairs ) )
        {
            pair_number = static_cast<unsigned long>(std::distance(std::begin(initialized_pairs), pos) + 1 );
        }
        else
        {
            ::init_pair(static_cast<chtype>(initialized_pairs.size() + 1),
                        static_cast<short>(fg), static_cast<short>(bg));
            initialized_pairs.push_back(pair );

            pair_number = initialized_pairs.size();
        }
    }

    explicit color_pair( unsigned long pair_num ) : pair_number { pair_num }
    {
        if (pair_num > initialized_pairs.size())
            throw std::invalid_argument( "This color pair doesn't exist: " + std::to_string(pair_num) );
    }

    using type = std::pair<color, color>;

    friend bool operator==(const color_pair &lhs, const color_pair &rhs) {
        return lhs.pair_number == rhs.pair_number;
    }

    friend bool operator!=(const color_pair &lhs, const color_pair &rhs) {
        return !(rhs == lhs);
    }

    friend bool operator<(const color_pair &lhs, const color_pair &rhs) {
        return lhs.pair_number < rhs.pair_number;
    }

    friend bool operator>(const color_pair &lhs, const color_pair &rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const color_pair &lhs, const color_pair &rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const color_pair &lhs, const color_pair &rhs) {
        return !(lhs < rhs);
    }

    unsigned long pair_number { 0 };
    static std::vector<type> initialized_pairs;
};

std::vector<color_pair::type> color_pair::initialized_pairs {};
std::unordered_map<char, color> char_to_color {
        { 'r', color::red },
        { 'g', color::green },
        { 'y', color::yellow },
        { 'b', color::blue },
        { 'm', color::magenta },
        { 'c', color::cyan },
        { 'w', color::white }
};

}

#endif //CXXCURSES_PRINT_COLOR_HPP
