#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fleet.h"

void inicializarFrota(Frota *f) {
    f->navios = NULL;
    f->quantidade = 0;
}

void adicionarNavioNaFrota(Frota *f, const char *nome, int tamanho) {
    // [cite: 150] Uso explícito de realloc
    Navio *novo = (Navio *) realloc(f->navios, (f->quantidade + 1) * sizeof(Navio));
    Navio *n;

    if (novo == NULL) {
        fprintf(stderr, "Erro de memoria na frota.\n");
        exit(1);
    }

    f->navios = novo;
    n = &f->navios[f->quantidade];

    strncpy(n->nome, nome, sizeof(n->nome) - 1);
    n->nome[sizeof(n->nome) - 1] = '\0';
    n->tamanho = tamanho;
    n->acertos = 0;

    f->quantidade++;
}

void criarFrotaPadrao(Frota *f) {
    // [cite: 13-16] Configuração padrão da frota
    adicionarNavioNaFrota(f, "Porta-avioes", 5);
    adicionarNavioNaFrota(f, "Encouracado", 4);
    adicionarNavioNaFrota(f, "Cruzador", 3);
    adicionarNavioNaFrota(f, "Cruzador", 3);
    adicionarNavioNaFrota(f, "Destroyer", 2);
    adicionarNavioNaFrota(f, "Destroyer", 2);
}

void liberarFrota(Frota *f) {
    if (f->navios != NULL) {
        free(f->navios);
        f->navios = NULL;
    }
    f->quantidade = 0;
}

int frotaAfundou(Frota *f) {
    int i;
    for (i = 0; i < f->quantidade; i++) {
        if (f->navios[i].acertos < f->navios[i].tamanho) return 0;
    }
    return 1;
}