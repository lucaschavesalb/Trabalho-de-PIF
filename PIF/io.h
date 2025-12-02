#ifndef IO_H  
#define IO_H

// Protege o arquivo para não ser incluído duas vezes

#include "board.h" // Precisa do tipo Tabuleiro


void exibirTabuleiro(Tabuleiro *t, int mostrar_navios);  // Desenha o tabuleiro na tela


int lerCoordenada(int *linha, int *coluna, int max_linhas, int max_colunas); // Lê coordenadas tipo "B4"


void exibirMensagem(const char *msg);  // Mostra mensagens simples

#endif // Fim da proteção