#include <stdlib.h>
#include <time.h>
#include "rnd.h"

void inicializarAleatorio(void) {
    srand((unsigned) time(NULL));
}

int obterNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}