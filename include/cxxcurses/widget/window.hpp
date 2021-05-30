// ------------------------------------------------------------------------------------------------
// cxxcurses - window.hpp header file
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2020 Hubert Jaremko
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// ------------------------------------------------------------------------------------------------

#ifndef CXXCURSES_WINDOW_WINDOW_HPP
#define CXXCURSES_WINDOW_WINDOW_HPP

#include <curses.h>
#include <cxxcurses/raw.hpp>
#include <cxxcurses/widget/widget.hpp>

namespace cxxcurses::widget
{

class window_interface : public widget_interface
{
public:
    virtual void get_char() const = 0;
    [[nodiscard]] virtual auto current_yx() const noexcept
        -> std::pair<int, int> = 0;
    [[nodiscard]] virtual auto max_yx() const noexcept
        -> std::pair<int, int> = 0;
    [[nodiscard]] virtual auto get() const -> raw::window_ptr = 0;
    virtual void move_cursor( int y, int x ) const = 0;
};

class stdscr_wrapper : public window_interface
{
public:
    void draw() const override
    {
        wrefresh( stdscr );
    }

    void refresh() const override
    {
        wrefresh( stdscr );
    }

    void get_char() const override
    {
        wgetch( stdscr );
    }

    [[nodiscard]] auto current_yx() const noexcept
        -> std::pair<int, int> override
    {
        auto y { 0 };
        auto x { 0 };
        getyx( get(), y, x );

        return { y, x };
    }

    [[nodiscard]] auto max_yx() const noexcept -> std::pair<int, int> override
    {
        auto y { 0 };
        auto x { 0 };
        getmaxyx( get(), y, x );

        return { y, x };
    }

    [[nodiscard]] auto get() const -> raw::window_ptr override
    {
        return stdscr;
    }

    void move_cursor( int y, int x ) const override
    {
        wmove( get(), y, x );
    }
};

class window : public window_interface
{
public:
    struct dimensions
    {
        int y { 0 };
        int x { 0 };
        int height { 0 };
        int width { 0 };
    };

    explicit window( dimensions dims, widget_interface& hook )
        : dimensions_( dims ), hook_( hook ), raw_window_( make_window() )
    {
        hook_.refresh();
        this->refresh();
        this->draw_border();
    }

    window( const window& ) = delete;
    window( window&& ) = delete;
    auto operator=( const window& ) -> window& = delete;
    auto operator=( window&& ) -> window& = delete;
    ~window() override = default;

    void draw() const override
    {
        ::wclear( raw_window_.get() );

        for ( const auto& w : children_ )
        {
            w->draw();
        }

        hook_.refresh();
        this->draw_border();
        this->refresh();
    }

    void add_widget( widget::pointer w )
    {
        children_.emplace_back( std::move( w ) );
    }

    void refresh() const override
    {
        hook_.refresh();
        ::wrefresh( raw_window_.get() );

        for ( const auto& w : children_ )
        {
            w->refresh();
        }
    }

    void get_char() const override
    {
        hook_.refresh();
        this->refresh();
        wgetch( raw_window_.get() );
    }

    [[nodiscard]] auto get() const -> raw::window_ptr override
    {
        return raw_window_.get();
    }

    [[nodiscard]] auto current_yx() const noexcept
        -> std::pair<int, int> override
    {
        auto y { 0 };
        auto x { 0 };
        getyx( get(), y, x );

        return { y, x };
    }

    [[nodiscard]] auto max_yx() const noexcept -> std::pair<int, int> override
    {
        auto y { 0 };
        auto x { 0 };
        getmaxyx( get(), y, x );

        return { y, x };
    }

    void move_cursor( int y, int x ) const override
    {
        wmove( get(), y, x );
    }

private:
    void draw_border() const
    {
        ::box( raw_window_.get(), 0, 0 );
    }

    [[nodiscard]] auto make_window() const -> raw::window_unique_ptr
    {
        return raw::window_unique_ptr { ::newwin( dimensions_.height,
                                                  dimensions_.width,
                                                  dimensions_.y,
                                                  dimensions_.x ) };
    }

    dimensions dimensions_;
    widget_interface& hook_;
    widget_list children_;
    raw::window_unique_ptr raw_window_;
};

} // namespace cxxcurses::widget

#endif // CXXCURSES_WINDOW_WINDOW_HPP
