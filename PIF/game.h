#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h" // O compilador precisa saber o que é "Tabuleiro" e "Frota" antes de usar aqui.

// Define todos os dados que pertencem a um único jogador.
typedef struct {
    Tabuleiro tabuleiro;  // O tabuleiro onde os navios dele estão posicionados
    Tabuleiro tiros;      // O tabuleiro de "radar" onde ele marca os tiros dados
    Frota frota;          // A lista de navios e seus status (vida, tamanho)
    char apelido[32];     // Buffer estático para o nome (max 31 chars + \0)
    int total_tiros;      // Contador para estatísticas
    int total_acertos;    // Contador para estatísticas
} Jogador;


// Agrupa tudo que é necessário para controlar uma partida inteira.
typedef struct {
    Jogador j1;           // Instância completa do Jogador 1
    Jogador j2;           // Instância completa do Jogador 2
    int jogador_atual;    // Flag para controlar o turno (ex: 1 ou 2)
    int jogo_acabou;      // Booleano (0 ou 1) para parar o loop principal do jogo
    int linhas_cfg;       // Configuração de tamanho do tabuleiro usada na partida
    int colunas_cfg;
} Jogo;

// Declara as funções para que outros arquivos saibam que elas existem.

// Inicializa os dados do jogador e aloca memória para os tabuleiros internos
void inicializarJogador(Jogador *j, const char *apelido, int linhas, int colunas);

// Libera a memória dos tabuleiros e da frota
void liberarJogador(Jogador *j);

// Funções de posicionamento
void posicionarFrotaAuto(Jogador *j);   // Algoritmo aleatório
void posicionarFrotaManual(Jogador *j); // Interação com usuário

// Processa a lógica de um tiro de um jogador no tabuleiro do outro
void jogadorAtira(Jogador *atirador, Jogador *alvo);

#endif
