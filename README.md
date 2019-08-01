# cxxcurses

<p align="center">
  <img src="https://i.imgur.com/rW7aM3J.png" alt="Example"/>
</p>

Custom C++ wrapper aiming to provide more friendly interface
to the most used (at least by me) functions of ncurses instead of not so fun to use C interface.

### Prerequisites

You need to have `ncurses` installed or in case of building on Windows `pdcurses`.

### Building
#### Linux
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

#### Windows Visual Studio
```
$ mkdir build
$ cd build
$ cmake .. -DCURSES_LIBRARY="pdcurses" -DCURSES_INCLUDE_PATH="<path to pdcurses>"
$ msbuild libcxxcurses.sln
```

#### Windows MinGW
```
$ mkdir build
$ cd build
$ cmake .. -G "MinGW Makefiles" -DCURSES_LIBRARY="pdcurses" -DCURSES_INCLUDE_PATH="<path to pdcurses>"
$ mingw32-make
```
