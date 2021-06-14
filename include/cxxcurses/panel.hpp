#pragma once
#include <panel.h>
#include <cxxcurses/raw.hpp>

namespace cxxcurses
{
namespace raw
{
struct panel_deleter;

using panel_ptr = ::PANEL*;
using panel_unique_ptr = std::unique_ptr<PANEL, panel_deleter>;

using screen_ptr = ::SCREEN*;

struct panel_deleter
{
    void operator()( panel_ptr p ) const
    {
        ::del_panel(p);
    }
};
}; // namespace raw

class panel
{
public:
    panel() = delete;
    panel(raw::window_ptr w) : raw_panel_(::new_panel(w)) { ; }
    panel(const panel& p) : raw_panel_(::new_panel(p.window())) { ; }
    panel(panel&&) = default;
    ~panel() = default;

    void bottom() { ::bottom_panel(raw_panel_.get()); }
    void top()    { ::top_panel   (raw_panel_.get()); }
    void show()   { ::show_panel  (raw_panel_.get()); }
    void hide()   { ::hide_panel  (raw_panel_.get()); }
    void move( int x, int y) { ::move_panel(raw_panel_.get(), x, y); }
    void replace(raw::window_ptr w)  { ::replace_panel(raw_panel_.get(), w); }

    [[nodiscard]] auto window() const -> raw::window_ptr { return ::panel_window(raw_panel_.get()); }
    [[nodiscard]] auto above()  const -> raw::panel_ptr  { return ::panel_above(raw_panel_.get()); }
    [[nodiscard]] auto below()  const -> raw::panel_ptr  { return ::panel_below(raw_panel_.get()); }

    [[nodiscard]] auto hidden() const -> bool { return ::panel_hidden(raw_panel_.get()); }

    template<typename T>
    void setData(T* data) { ::set_panel_userptr(raw_panel_.get(), data); }
    template<typename T>
    [[nodiscard]] auto data() const -> T* { return static_cast<T*>((void*)::panel_userptr(raw_panel_.get())); }

    static void update() { ::update_panels(); }
    [[nodiscard]] static auto ceiling(raw::screen_ptr sp) -> raw::panel_ptr { return ceiling_panel(sp); }
    [[nodiscard]] static auto ground (raw::screen_ptr sp) -> raw::panel_ptr { return ground_panel(sp); }
protected:
    raw::panel_unique_ptr raw_panel_;
};

template<typename DataType>
class DataPanel : public panel
{
public:
    using panel::panel;
    [[nodiscard]] auto data() const -> DataType* { return static_cast<DataType*>((void*)::panel_userptr(raw_panel_.get())); }
};

}; // namespace cxxcurses
