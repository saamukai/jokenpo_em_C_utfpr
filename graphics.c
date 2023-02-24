#include <curses.h>
#include "graphics.h"

// 8 colors for standard Curses
#define PALLETE_SIZE (COLOR_WHITE - COLOR_BLACK + 1)

//////////////////////////////////////////////////////////////////////
// Funções auxiliares para a biblioteca Curses
//////////////////////////////////////////////////////////////////////
void initScreen()
{
#ifdef XCURSES
    Xinitscr(argc, argv);
#else
    initscr();
#endif

    if (has_colors())
    {
        int bg = 0, fg = 0;

        start_color();

        for(bg = COLOR_BLACK; bg <= COLOR_WHITE; bg++)
            for(fg = COLOR_BLACK; fg <= COLOR_WHITE; fg++)
                init_pair(bg*PALLETE_SIZE + fg + 1, fg, bg); // color 0 is system default (reserved)
    }

    // Trata a tecla Enter como \n
    //nl();
    // Teclas digitadas pelo usuário não aparecem na tela
    noecho();
    // 0 para cursor invisível
    curs_set(0);
    // Define getch como non-blocking de acordo com o timeout abaixo
    nodelay(stdscr, TRUE);
    // Timeout em 0 determina getch como non-blocking, não espera entrada do usuário
    timeout(0);
    // Habilita teclas de function (F1, F2, ...), flechas, etc
    keypad(stdscr, TRUE);
}

void setColor(short int fg, short int bg, chtype attr)
{
    chtype color = COLOR_PAIR(bg*PALLETE_SIZE + fg + 1);
    color |= attr;
    attrset(color);
}

