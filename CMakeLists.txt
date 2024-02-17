cmake_minimum_required(VERSION 3.5)

project(dwm)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

add_definitions(-DXINERAMA)
add_definitions(-DVERSION="6.4")
add_definitions(-D_DEFAULT_SOURCE)
add_definitions(-D_BSD_SOURCE)
add_definitions(-D_POSIX_C_SOURCE=200809L)

set(C_SOURCES
    src/drw.c
    src/log.c
    src/util.c
    src/dwm.c
)

set(CPP_SOURCES
    src/main.cpp
)

include_directories(
    /usr/X11R6/include
    /usr/include/freetype2
    ./src
)

add_executable(dwm ${C_SOURCES} ${CPP_SOURCES})

target_link_libraries(dwm
    X11
    Xinerama
    Xrender
    Imlib2
    fontconfig
    Xft
    xkbcommon
    xkbcommon-x11
    xcb
)

install(TARGETS dwm DESTINATION /usr/local/bin/)
