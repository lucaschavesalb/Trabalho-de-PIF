#ifndef IO_H
#define IO_H

#include "board.h"

/* Desenha o tabuleiro no console */
void exibirTabuleiro(Tabuleiro *t, int mostrar_navios);

/* Lê uma coordenada tipo "B5" e converte para indices */
int lerCoordenada(int *linha, int *coluna, int max_linhas, int max_colunas);

/* Exibe mensagens de erro ou sucesso simples */
void exibirMensagem(const char *msg);

#endif