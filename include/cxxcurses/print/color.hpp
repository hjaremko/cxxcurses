// ------------------------------------------------------------------------------------------------
// cxxcurses - color.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_COLOR_HPP
#define CXXCURSES_COLOR_HPP

#include <unordered_map>

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

const std::unordered_map<char, color> char_to_color{ { 'r', color::red },     { 'g', color::green },
                                                     { 'y', color::yellow },  { 'b', color::blue },
                                                     { 'm', color::magenta }, { 'c', color::cyan },
                                                     { 'w', color::white } };
} // namespace cxxcurses

#endif // CXXCURSES_COLOR_HPP
