#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fleet.h"

void inicializarFrota(Frota *f) {
    f->navios = NULL;
    f->quantidade = 0; // Começo com a frota vazia, sem navio e com quantidade zero. Dps conforme eu for adicionando navios o vetor é criado com realloc
}

void adicionarNavioNaFrota(Frota *f, const char *nome, int tamanho) {
    Navio *novo = (Navio *) realloc(f->navios, (f->quantidade + 1) * sizeof(Navio)); // Breve resumo pra lembrar: dá espaço pra mais um navio, mantendo os antigos.
    Navio *n;

    if (novo == NULL) {
        fprintf(stderr, "Erro de memoria na frota.\n");
        exit(1);
    }

    f->navios = novo; // o novo que vai ser preenchido ligando com a linha 12.
    n = &f->navios[f->quantidade];
                        // sizeof(n->nome) - 1 o maximo vai ser decido aqui.
    strncpy(n->nome, nome, sizeof(n->nome) - 1); // strncpy: copiar uma sequência de caracteres de uma origem para um destino, com um limite máximo de caracteres a serem copiados, uma medida de segurança.
    n->nome[sizeof(n->nome) - 1] = '\0';
    n->tamanho = tamanho;
    n->acertos = 0;

    f->quantidade++; // dalhe navio.
}

void criarFrotaPadrao(Frota *f) {
     // A frota minima pedida de acordo com o Projeto.
    adicionarNavioNaFrota(f, "Porta-avioes", 5);
    adicionarNavioNaFrota(f, "Encouracado", 4);
    adicionarNavioNaFrota(f, "Cruzador", 3);
    adicionarNavioNaFrota(f, "Cruzador", 3);
    adicionarNavioNaFrota(f, "Destroyer", 2);
    adicionarNavioNaFrota(f, "Destroyer", 2);
}

void liberarFrota(Frota *f) {  // aqui a gnt vai liberar a memoria pedida lá encima.
    if (f->navios != NULL) {
        free(f->navios);
        f->navios = NULL;
    }
    f->quantidade = 0; // zeramos o ponteiro e a quantidade pra evitar uso indevido
}

int frotaAfundou(Frota *f) {
    int i;
    for (i = 0; i < f->quantidade; i++) { // aqui percorre todos os navios da frota e verifica se todos já foram totalmente acertados
                            // Se encontra um navio não afundado
        if (f->navios[i].acertos < f->navios[i].tamanho) return 0;
    }
    return 1;
}