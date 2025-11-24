#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    Tabuleiro tabuleiro;
    Tabuleiro tiros;
    Frota frota;
    char apelido[32];
    int total_tiros;
    int total_acertos;
} Jogador;

typedef struct {
    Jogador j1;
    Jogador j2;
    int jogador_atual;
    int jogo_acabou;
    int linhas_cfg;  // Configuracao atual
    int colunas_cfg;
} Jogo;

void inicializarJogador(Jogador *j, const char *apelido, int linhas, int colunas);
void liberarJogador(Jogador *j);
void posicionarFrotaAuto(Jogador *j); // Usa RND
void posicionarFrotaManual(Jogador *j); // Usa IO
void jogadorAtira(Jogador *atirador, Jogador *alvo);

#endif