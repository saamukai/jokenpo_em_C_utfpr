// UNIVERSIDADE TECNOLOGICA FEDERAL DO PARAN�, CAMPUS TOLEDO
// ENGENHARIA DA COMPUTA��O
// FUNDAMENTOS DA PROGRAMA��O
// SAMUEL JONATHAN

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "graphics.h"
#include "game.h"

void handleInputs(gameData * game) // VERIFICA AS TECLAS PRESSIONADAS E PARTIR DELAS DETERMINAS FUN��ES S�O CHAMADAS
{
    int entrada = getch();

    if(entrada != -1)
        game->ultimaTecla = entrada;

    if((game->contRound)<4) // USUARIO PODE JOGAR SOMENTE EM 3 ROUNDS, A MENOS QUE REINICIE A RODADA COM A TECLA "I"
    {
        switch(entrada)
        {
            case '1':
            {
                game->contRound++;
                clear();
                cabecario(game);
                setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
                mvprintw(12,35, "loading...");
                refresh();
                Sleep(2000);
                game->escolhaJog=1; // COMO NA ENUM ESCOLHA, PEDRA = 1, JOG ESCOLHE PEDRA
                game->escolhaPC = (rand()%3+1); // ESCOLHA RANDOMICA DO COMPUTADOR
                game->winner=verificaWin(game->escolhaJog, game->escolhaPC); // VERIFICA VENCEDOR DO ROUND, VERIFINWIN NA GAME.C
                resultaRound(game);
            }
                break;

            case '2':
            {
                game->contRound++;
                clear();
                cabecario(game);
                setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
                mvprintw(12,35, "loading...");
                refresh();
                Sleep(2000);
                cabecario(game);
                game->escolhaJog=2; // JOG ESCOLHE PAPEL
                game->escolhaPC = (rand()%3+1); // ESCOLHA RANDOMICA DO COMPUTADOR
                game->winner=verificaWin(game->escolhaJog, game->escolhaPC); // VERIFICA VENCEDOR DO ROUND, VERIFINWIN NA GAME.C
                resultaRound(game);

            }
                break;

            case '3':
            {
                game->contRound++;
                clear();
                cabecario(game);
                setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
                mvprintw(12,35, "loading...");
                refresh();
                Sleep(2000);
                cabecario(game);
                game->escolhaJog=3; // JOG ESCOLHE TESOURA
                game->escolhaPC = (rand()%3+1); // ESCOLHA RANDOMICA DO COMPUTADOR
                game->winner=verificaWin(game->escolhaJog, game->escolhaPC); // VERIFICA VENCEDOR DO ROUND, VERIFINWIN NA GAME.C
                resultaRound(game);
            }
                break;
        }
    }

    switch (entrada)
    {
        case 'c':
        case 'C': // CHAMA A TELA DE CONTROLES
            controles(game);
            break;

        case 'i':
        case 'I': // INICIA UMA NOVA RODADA E CHAMA A TELA INFO
        {
            game->ultimaTecla=-1;
            game->scoreJog=0;
            game->scorePC=0;
            game->contRound=1;
            game->escolhaJog=0;
            game->escolhaPC=0;
            game->winner=0;
            game->salvaScoreLose=0;
            game->salvaScoreWin=0;
            leRelatorio(game);
            telaInfo(game);
        }
            break;

        case 's':
        case 'S': // 'S'TART  NO JOGO, CHAMA TELAGAME
            telaGame(game);
            break;

        case 'a': // "AVAN�A O ROUND", CHAMA NOVAMENTE A TELA GAME
        case 'A':
            telaGame(game);
            break;

        case 'q':  // FINALIZA O JOGO
        case 'Q':
        {
            cabecario(game);
            setColor(COLOR_WHITE, COLOR_RED, A_BOLD);
            mvprintw(10,23, " VOCE ESCOLHEU SAIR DO JOGO :(");
            refresh();
            Sleep(2000);
            endwin();
            exit(EXIT_SUCCESS);
        }
            break;
    }
}

void telaLoading (gameData * game) // PRIMEIRA TELA A SER EXIBIDA, LOADING
{
    clear();
    setColor(COLOR_WHITE, COLOR_RED, A_BOLD);
    mvprintw(5,45,"'JOKENPO' 'JOKENPO' 'JOKENPO'");
    mvprintw(6,45,"'JOKENPO' 'JOKENPO' 'JOKENPO'");
    mvprintw(7,45,"'JOKENPO' 'JOKENPO' 'JOKENPO'");
    mvprintw(8,45,"'JOKENPO' 'JOKENPO' 'JOKENPO'");
    mvprintw(9,45,"'JOKENPO' 'JOKENPO' 'JOKENPO'");
    mvprintw(10,45,"'JOKENPO' 'JOKENPO' 'JOKENPO'");
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvprintw(15,55,"loading...");
    setColor(COLOR_BLUE, COLOR_BLACK, A_BOLD);
    mvprintw(23,50,"MADE IN UTFPR, 2022");
    mvprintw(24,48,"Engenharia da Computacao");
    mvprintw(25,50,"Samuel Jonathan");
    refresh();
    Sleep(2000);
    clear();
    refresh();
}

void cabecario(gameData*game) // CABECARIO QUE VIRA A VIR SER REPETIDO NAS OUTRAS TELAS
{
    clear();
    setColor(COLOR_BLUE, COLOR_BLACK, A_BOLD);
    mvprintw(3,1,"----------------------------------------------------------------------------------\n");
    mvprintw(4,25,"'JOKENPO' 'JOKENPO' 'JOKENPO'\n");
    mvprintw(5,25,"'JOKENPO' 'JOKENPO' 'JOKENPO'\n");
    mvprintw(6,25,"'JOKENPO' 'JOKENPO' 'JOKENPO'\n");
    mvprintw(7,1,"----------------------------------------------------------------------------------\n");
}

void leRelatorio(gameData*game) // LE O RELATORIO E IMPRIME NA TELA DE INFORMA��ES
{
    FILE *file;
    file = fopen("relatorio.txt", "r");
    fscanf(file, "%d %d", &(game->salvaScoreWin), &(game->salvaScoreLose));
    fclose(file);
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvprintw(8,22,"Voce ja ganhou %d vezes e perdeu %d vezes.\n\n", game->salvaScoreWin, game->salvaScoreLose);
    refresh();
}

void telaInfo (gameData*game) // TELA DE COMO FUNCIONA O JOGO
{
    cabecario(game);
    leRelatorio(game);
    setColor(COLOR_WHITE, COLOR_YELLOW, A_BOLD);
    mvprintw(10,28," JOKENPO 'MELHOR DE 3' ");
    setColor(COLOR_WHITE, COLOR_BLUE, A_BOLD);
    mvprintw(12,32," COMO FUNCIONA? ");
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    printw("\n\n\tO jogo eh um Jokenpo (Pedra, Papel ou Tesoura) contra a maquina no formato ''Melhor de 3''.");;
    printw("\n\tPara jogar basta escolhar sua opcao e apertar a tecla da opcao desejada.");
    printw("\n\tA escolha da maquina sera mostrada na tela juntamente com a sua.");
    printw("\n\tO vencedor de cada round tambem sera mostrado, ao todo serao 3 rounds.");
    printw("\n\tO vencedor da RODADA sera aquele que obtiver o maior numero de vitorias nos rounds");
    printw("\n\n\tCaso voce ocasionalmente nunca tenha jogado jokenpo, ai vai como funciona:");
    printw("\n\t\tPapel vence Pedra, porem perde da Tesoura");
    printw("\n\t\tPedra vence Tesoura, porem perde do Papel");
    printw("\n\t\tTesoura vence Papel, porem perde da Pedra");
    printw("\n\n\n\t\tPara ver os controles do jogo pressione a tecla 'c'.");
    printw("\n\tCaso voce ja saiba os controles e deseja iniciar o jogo, tecle 's'");
}

void resultaRound(gameData*game) // FUNCAO RESULTA ROUND, IMPRIME O QUE CADA UM ESCOLHEU
{
    cabecario(game);
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvprintw(10,26,"Voce escolheu: ");
    imprimeEscolha(game->escolhaJog);
    mvprintw(11,35," x ");
    mvprintw(12,23,"Computador escolheu: ");
    imprimeEscolha(game->escolhaPC);
    if (game->winner==1)  // FAZ VERIFICA��ES SE EMPATOU, PERDEU OU GANHOU E IMPRIME NA TELA
    {
        setColor(COLOR_WHITE, COLOR_GREEN, A_BOLD);
        mvprintw(14, 30,"VOCE VENCEU!!\n");
        game->scoreJog++;
    }
    else if(game->winner == 2)
    {
        setColor(COLOR_WHITE, COLOR_RED, A_BOLD);
        mvprintw(14, 30,"VOCE PERDEU!!\n");
        game->scorePC++;
    }
    else
    {
        setColor(COLOR_BLACK, COLOR_WHITE, A_BOLD);
        mvprintw(14, 33,"EMPATE!!\n");
    }

    setColor(COLOR_WHITE, COLOR_YELLOW, A_BOLD);  // IMPRIME NA TELA O RESULTADO DO ROUND JOGADO
    if((game->contRound)!=(4))
        mvprintw(8,28," RESULTADO %d ROUND \n", game->contRound-1);
    else
        mvprintw(8,25," RESULTADO ROUND FINAL: \n");
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if((game->contRound)!=(4))
        mvprintw(16,14,"Para avancar para o proximo round pressione a tecla 'a'");

    if((game->contRound)==4)  // SE FOR ULTIMO ROUND, IMPRIME NA TELA PLACAR DE PONTOS FINAIS
    {
        refresh();
        Sleep(700);
        setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
        mvprintw(16, 20,"Aguarde, carregando relatorio final");
        refresh();
        Sleep(2000);
        cabecario(game);
        setColor(COLOR_WHITE, COLOR_YELLOW, A_BOLD);
        mvprintw(9, 27, " PLACAR DE PONTOS FINAIS ");
        setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
        mvprintw(11, 23, "Computador: %d", game->scorePC);
        mvprintw(12, 23, "Voce::::::: %d", game->scoreJog);
        if ((game->scoreJog)>(game->scorePC))                        // RESULTADO DA RODADA, MELHOR DE 3
        {
            setColor(COLOR_WHITE, COLOR_GREEN, A_BOLD);
            mvprintw(14,13, "Voce foi o grande vencedor da rodada! Parabens");
        }
        else if ((game->scoreJog)==(game->scorePC))
        {
            setColor(COLOR_BLACK, COLOR_WHITE, A_BOLD);
            mvprintw(14,13, "Otima rodada, houve um empate, jogue novamente");
        }
        else
        {
            setColor(COLOR_WHITE, COLOR_RED, A_BOLD);
            mvprintw(14,15, "Voce perdeu, eh uma desonra, treine mais!");
        }
        refresh();
        Sleep(700);
        setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
        mvprintw(16,25, "Salvando dados, aguarde...");
        salvaRelatorio(game);  // SALVA DADOS NO RELATORIO
        refresh();
        Sleep(3000);
        mvprintw(18,30,"Dados salvos!");
        refresh();
        Sleep(700);
        mvprintw(20,8,"Para voltar ao menu 'Como Funciona' e jogar novamente, pressione a tecla 'i'");
        mvprintw(22,18,"Caso queira sair do jogo, pressione a tecla 'Q'");
        refresh();
    }
}

void salvaRelatorio (gameData*game) // SALVA OS DADOS NO RELATORIO
{
    if((game->scoreJog)>(game->scorePC))
    {
        FILE *file1;
        file1 = fopen("relatorio.txt", "w");
        fprintf(file1,"%d %d", (game->salvaScoreWin+1), game->salvaScoreLose);
        fclose(file1);
    }
    else if ((game->scoreJog)==(game->scorePC))
    {
        FILE *file2;
        file2 = fopen("relatorio.txt", "w");
        fprintf(file2,"%d %d", game->salvaScoreWin, game->salvaScoreLose);
        fclose(file2);
    }
    else if ((game->scoreJog)<(game->scorePC))
    {
        FILE *file2;
        file2 = fopen("relatorio.txt", "w");
        fprintf(file2,"%d %d", game->salvaScoreWin, (game->salvaScoreLose+1));
        fclose(file2);
    }
}

void controles (gameData*game) // TELA DE CONTROLES A SEREM USADOS NO JOGO
{
    cabecario(game);
    setColor(COLOR_WHITE, COLOR_YELLOW, A_BOLD);
    mvprintw(8,28," JOKENPO 'MELHOR DE 3' ");
    setColor(COLOR_WHITE, COLOR_BLUE, A_BOLD);
    mvprintw(10,34," CONTROLES ");
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvprintw(12, 20, "Tecla: '1' - Escolhe Pedra");
    mvprintw(13, 20, "Tecla: '2' - Escolhe Papel");
    mvprintw(14, 20, "Tecla: '3' - Escolhe Tesoura");
    mvprintw(15, 20, "Tecla: 'a' - Proximo Round");
    mvprintw(16, 20, "Tecla: 'c' - Tela de Controles");
    mvprintw(17, 20, "Tecla: 'i' - Tela de 'Como Funciona'");
    mvprintw(18, 20, "Tecla: 's' - Inicia os Rounds");
    mvprintw(19, 20, "Tecla: 'q' - Finaliza o Jogo");
    mvprintw(22, 10, "Para voltar ao menu de informacoes pressione a tecla 'i'");
    mvprintw(23, 15, "Para iniciar o jogo pressione a tecla 's'");
}

void telaGame (gameData*game) //TELA GAME = TELA ONDE S�O IMPRIMIDAS AS OP��ES DISPONIVEIS PRO USUARIOS
{
    cabecario(game);
    setColor(COLOR_WHITE, COLOR_YELLOW, A_BOLD);
    mvprintw(8,29," JOKENPO 'MELHOR DE 3' ");
        // DIZ EM QUE ROUND USUARIOS EST�
    if ((game->contRound)==0)
        mvprintw(10,22," VOCE ESTA NO PRIMEIRO ROUND ");
    else if ((game->contRound)!=3)
        mvprintw(10,29," VOCE ESTA NO %d ROUND ", game->contRound);
    if ((game->contRound)==3)
        mvprintw(10,28," VOCE ESTA NO ROUND FINAL ");
        // OP��ES A SEREM ESCOLHIDAS PELO USU�RIO
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvprintw(12,20,"Tecle o numero da opcao desejada:");
    mvprintw(13,23, "1. Pedra");
    mvprintw(14,23, "2. Papel");
    mvprintw(15,23, "3. Tesoura");
}

int main (int argc, char *argv[])
{
    int cols = 0, rows = 0;

    gameData game;

    initScreen();

    getmaxyx(stdscr, rows, cols);

    initGame(&game, rows, cols);

    telaLoading(&game);

    telaInfo(&game);

    while(1)
    {
        handleInputs(&game);
    }

    endwin();

    return 0;

}
