#ifndef FLEET_H
#define FLEET_H

typedef struct {
    char nome[20];
    int tamanho;
    int acertos; // lembrar que acertos==tamanho, ja era papai  (Exemplo: se eu tenho um navio com 5 de tamanho e ele foi atigindo 5 vezes ja era)
} Navio;

typedef struct {
    Navio *navios;   // malloc e realloc //
    int quantidade;
} Frota;

void inicializarFrota(Frota *f);
void adicionarNavioNaFrota(Frota *f, const char *nome, int tamanho);
void criarFrotaPadrao(Frota *f);
void liberarFrota(Frota *f);
int frotaAfundou(Frota *f);

#endif