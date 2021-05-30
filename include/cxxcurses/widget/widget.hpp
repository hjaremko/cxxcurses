// ------------------------------------------------------------------------------------------------
// cxxcurses - widget.hpp
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2020 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_WIDGET_WIDGET_HPP
#define CXXCURSES_WIDGET_WIDGET_HPP

#include <memory>
#include <vector>

namespace cxxcurses::widget
{

class widget_interface
{
public:
    virtual void draw() const = 0;
    virtual void refresh() const = 0;
    virtual ~widget_interface() = default;

    widget_interface() = default;
    widget_interface( const widget_interface& ) = delete;
    widget_interface( widget_interface&& ) = default;
    auto operator=( widget_interface&& ) -> widget_interface& = default;
    auto operator=( const widget_interface& ) -> widget_interface& = delete;
};

using pointer = std::unique_ptr<widget_interface>;
using widget_list = std::vector<widget::pointer>;

} // namespace cxxcurses::widget

#endif // CXXCURSES_WIDGET_WIDGET_HPP
