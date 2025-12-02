#include <stdlib.h>   
#include <time.h>     
#include "rnd.h"   // chama as funções lá do .h´s

void inicializarAleatorio(void) {                // Inicia o gerador de números aleatórios
    srand((unsigned) time(NULL));                // Usa o tempo atual como semente (cada execução gera valores diferentes)
}

int obterNumeroAleatorio(int min, int max) {    // Devolve um aleatório entre min e max
    return min + rand() % (max - min + 1);      // Fórmula para gerar número dentro do intervalo
}