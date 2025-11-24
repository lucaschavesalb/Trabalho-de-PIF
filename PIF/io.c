#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "io.h"

void exibirTabuleiro(Tabuleiro *t, int mostrar_navios) {
    int l, c;

    printf("\n   ");
    for (c = 0; c < t->colunas; c++) {
        printf("%2d ", c + 1);
    }
    printf("\n");

    for (l = 0; l < t->linhas; l++) {
        printf("%c |", 'A' + l);
        for (c = 0; c < t->colunas; c++) {
            Celula *cel = obterCelula(t, l, c);
            char ch;

            if (cel->estado == ESTADO_ACERTO)      ch = 'X'; // [cite: 147] Legenda X
            else if (cel->estado == ESTADO_ERRO)   ch = '.'; // [cite: 147] Legenda .
            else if (cel->estado == ESTADO_NAVIO && mostrar_navios) ch = 'N';
            else                                   ch = '~';

            printf(" %c ", ch);
        }
        printf("|\n");
    }
}

int lerCoordenada(int *linha, int *coluna, int max_linhas, int max_colunas) {
    char entrada[16];
    char letra;
    int numero;
    int l, c;

    if (scanf("%15s", entrada) != 1) return 0;

    letra = entrada[0];
    if (!isalpha((unsigned char) letra)) return 0;

    letra = (char) toupper((unsigned char) letra);
    l = letra - 'A';

    // Tenta ler o número a partir do segundo caractere
    if (sscanf(entrada + 1, "%d", &numero) != 1) return 0;
    c = numero - 1;

    // Validação de limites [cite: 152]
    if (l < 0 || l >= max_linhas || c < 0 || c >= max_colunas) return 0;

    *linha = l;
    *coluna = c;
    return 1;
}

void exibirMensagem(const char *msg) {
    printf("%s\n", msg);
}