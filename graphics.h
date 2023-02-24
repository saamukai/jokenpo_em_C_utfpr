#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

// https://pubs.opengroup.org/onlinepubs/7908799/xcurses/curses.h.html
#include <curses.h> // chtype in setColor

void initScreen();
void setColor(short int fg, short int bg, chtype attr);

#endif // GRAPHICS_H_INCLUDED
