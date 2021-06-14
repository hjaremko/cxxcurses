add_executable(cxxcurses_sample main.cpp)
target_link_libraries(cxxcurses_sample cxxcurses::cxxcurses)

add_executable(cxxcurses_panel_sample panel.cpp)
target_link_libraries(cxxcurses_panel_sample cxxcurses::panel)
