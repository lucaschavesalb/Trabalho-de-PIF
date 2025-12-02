#include <stdio.h>
#include <stdlib.h>
#include "board.h" // chama as funções lá do .h 

void inicializarTabuleiro(Tabuleiro *t, int linhas, int colunas) {
    int total = linhas * colunas; // quantas células existem no tabuleiro
    int i;

    t->linhas = linhas;
    t->colunas = colunas;
    t->celulas = (Celula *) malloc(total * sizeof(Celula)); // reserva espaço
    if (t->celulas == NULL) {
        fprintf(stderr, "Erro de memoria ao criar tabuleiro.\n");
        exit(1);
    }

    for (i = 0; i < total; i++) { // pecorrer o tabuleiro inteiro
        t->celulas[i].estado = ESTADO_AGUA;
        t->celulas[i].id_navio = -1;
    }
}

void liberarTabuleiro(Tabuleiro *t) {
    if (t->celulas != NULL) {
        free(t->celulas); // Uso do free
        t->celulas = NULL;
    }
    t->linhas = 0;
    t->colunas = 0;
}

Celula *obterCelula(Tabuleiro *t, int linha, int coluna) {
    //linha negativa //passou da última linha: se tem 10(0a9)   // passou do limite da coluna
    if (linha < 0 || linha >= t->linhas || coluna < 0 || coluna >= t->colunas) return NULL; // retornar null não usar x ou y coord. 
                                        // msm coisa da primeira sendo feito com colunas
    int indice = linha * t->colunas + coluna; // Ex: indice 2*10 + 3 = 23 ( tabu tem 10 colunas, linha 2 e coluna 3)
    return &t->celulas[indice]; // devolve o endereço da célula real do tabuleiro pra poder alterar ela direto
}

int podeColocarNavio(Tabuleiro *t, int linha, int coluna, Orientacao o, int tamanho) {
    int i;
    // 1) checar limite
    if (o == ORIENTACAO_H) {      // -1
        if (coluna + tamanho > t->colunas) return 0; // Se for colocar horizontalmente, o navio vai andando nas colunas. tabu 10(0...9 começa coluna 8 tamn 3 ocuparia 8,9,10-> não existe)
        for (i = 0; i < tamanho; i++) {
            Celula *c = obterCelula(t, linha, coluna + i); // Coluna vai aumentando (coluna + i) porque é horizontal.
            if (c == NULL || c->estado != ESTADO_AGUA) return 0;
        }
    } else {
        
     // 2) checar colisão
        if (linha + tamanho > t->linhas) return 0;
        for (i = 0; i < tamanho; i++) {
            Celula *c = obterCelula(t, linha + i, coluna);
            if (c == NULL || c->estado != ESTADO_AGUA) return 0;
        }
    }
    return 1;
}

void colocarNavio(Tabuleiro *t, int linha, int coluna, Orientacao o, int tamanho, int id_navio) {
    int i;
    if (o == ORIENTACAO_H) {
        for (i = 0; i < tamanho; i++) {
            Celula *cel = obterCelula(t, linha, coluna + i);
            if(cel) {
                cel->estado = ESTADO_NAVIO;
                cel->id_navio = id_navio;
            }
        }
    } else {
        for (i = 0; i < tamanho; i++) {
            Celula *cel = obterCelula(t, linha + i, coluna);
            if(cel) {
                cel->estado = ESTADO_NAVIO;
                cel->id_navio = id_navio;
            }
        }
    }
}