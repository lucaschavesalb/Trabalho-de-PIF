#ifndef FLEET_H
#define FLEET_H

typedef struct {
    char nome[20];
    int tamanho;
    int acertos;
} Navio;

typedef struct {
    Navio *navios;    /* malloc / realloc */
    int quantidade;
} Frota;

void inicializarFrota(Frota *f);
void adicionarNavioNaFrota(Frota *f, const char *nome, int tamanho);
void criarFrotaPadrao(Frota *f);
void liberarFrota(Frota *f);
int frotaAfundou(Frota *f);

#endif