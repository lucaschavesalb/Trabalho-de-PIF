#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void inicializarTabuleiro(Tabuleiro *t, int linhas, int colunas) {
    int total = linhas * colunas;
    int i;

    t->linhas = linhas;
    t->colunas = colunas;
    t->celulas = (Celula *) malloc(total * sizeof(Celula));
    if (t->celulas == NULL) {
        fprintf(stderr, "Erro de memoria ao criar tabuleiro.\n");
        exit(1);
    }

    for (i = 0; i < total; i++) {
        t->celulas[i].estado = ESTADO_AGUA;
        t->celulas[i].id_navio = -1;
    }
}

void liberarTabuleiro(Tabuleiro *t) {
    if (t->celulas != NULL) {
        free(t->celulas); // [cite: 150] Uso explícito de free
        t->celulas = NULL;
    }
    t->linhas = 0;
    t->colunas = 0;
}

Celula *obterCelula(Tabuleiro *t, int linha, int coluna) {
    // Validação simples de limites para evitar crash
    if (linha < 0 || linha >= t->linhas || coluna < 0 || coluna >= t->colunas) return NULL;
    int indice = linha * t->colunas + coluna;
    return &t->celulas[indice];
}

int podeColocarNavio(Tabuleiro *t, int linha, int coluna, Orientacao o, int tamanho) {
    int i;
    // 1) checar limite
    if (o == ORIENTACAO_H) {
        if (coluna + tamanho > t->colunas) return 0;
        for (i = 0; i < tamanho; i++) {
            Celula *c = obterCelula(t, linha, coluna + i);
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