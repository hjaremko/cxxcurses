#include "../include/cxxcurses/output/color.hpp"
#include "cxxcurses/output/color_pair.hpp"

namespace cxxcurses
{

const std::unordered_map<char, color> char_to_color {
        { 'r', color::red },
        { 'g', color::green },
        { 'y', color::yellow },
        { 'b', color::blue },
        { 'm', color::magenta },
        { 'c', color::cyan },
        { 'w', color::white }
};

}