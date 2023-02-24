#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define MAX_SCREEN_SIZE 120

typedef struct point
{
    int x, y;
} point;

typedef enum escolha // ENUMERA ESCOLHAS
{
    PEDRA = 1,
    PAPEL = 2,
    TESOURA = 3
} escolha;

typedef struct gameData // ESTTRUTURA DO JOGO, VARIAVEIS UTILIZADAS
{
    int escolhaJog;
    int escolhaPC;

    int salvaScoreWin;
    int salvaScoreLose;

    int ultimaTecla;

    int contRound;

    int screenRows, screenCols;

    int scoreJog;
    int scorePC;
    int winner;

} gameData;

        // ALGUMAS FUNÇÕES UTILIZADAS NO JOGO, OUTRA FUNÇÕES FORAM DEFINIDAS NA PROPRIA MAIN.C
void initGame(gameData *game, int rows, int cols);
int positionMatch(point p1, point p2);
void imprimeEscolha(int escolha);
int verificaWin(int jog1, int jog2);

#endif
