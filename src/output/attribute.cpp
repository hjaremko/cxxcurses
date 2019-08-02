#include "../../include/cxxcurses/output/attribute.hpp"

namespace cxxcurses
{

std::unordered_map<char, attribute> char_to_attribute {
        { 'N', attribute::normal },
        { 'S', attribute::standout },
        { 'U', attribute::underline },
        { 'R', attribute::reverse },
        { 'X', attribute::blink },
        { 'D', attribute::dim },
        { 'B', attribute::bold },
        { 'P', attribute::protect },
        { 'I', attribute::invisible }
};

}
