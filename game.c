#include <string.h>
#include "game.h"
#include <curses.h>

void initGame(gameData *game, int rows, int cols) //INICIALIZA VARIAVEIS P/ O JOGO
{
    int x = 0;
    int y =0;
    game->ultimaTecla=-1;
    game->scoreJog=0;
    game->scorePC=0;
    game->contRound=1;
    game->escolhaJog=0;
    game->escolhaPC=0;
    game->winner=0;
    game->salvaScoreLose=0;
    game->salvaScoreWin=0;

    game->screenRows = rows;
    game->screenCols = cols;
}

 void imprimeEscolha(int escolha) // RESPONSÁVEL POR IMPRIMIR ESCOLHA
 {
    if(escolha == PEDRA){
        printw("PEDRA");
    }
    else if(escolha == PAPEL){
        printw("PAPEL");
    }
    else{
        printw("TESOURA");
    }
}

int positionMatch(point p1, point p2)
{
    if(p1.x == p2.x && p1.y == p2.y)
        return 1;
    else
        return 0;
}

int verificaWin(int jog1, int jog2) // VERIFICA VENCEDOR
{
    int winner;
    if(jog1 == jog2){ // EMPATE
        winner = 0;
    }

    if(jog1==PEDRA && jog2==TESOURA){ winner = 1; }
    if(jog1==PEDRA && jog2==PAPEL){ winner = 2; }

    if(jog1==PAPEL && jog2==PEDRA){ winner = 1; }
    if(jog1==PAPEL && jog2==TESOURA){ winner = 2; }

    if(jog1==TESOURA && jog2==PAPEL){ winner = 1; }
    if(jog1==TESOURA && jog2==PEDRA){ winner = 2; }

    return winner;
}
