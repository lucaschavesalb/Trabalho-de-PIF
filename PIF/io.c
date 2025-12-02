#include <stdio.h>      
#include <ctype.h>      
#include <string.h>     
#include "io.h" // Inclui o cabeçalho que declara as funções deste arquivo

void exibirTabuleiro(Tabuleiro *t, int mostrar_navios) {   // Mostra o tabuleiro na tela
    int l, c;   // Variáveis de linha (l) e coluna (c)

    printf("\n   ");   // Espaço inicial para alinhar os números das colunas

    for (c = 0; c < t->colunas; c++) {      // Escreve os números das colunas
        printf("%2d ", c + 1);              // Mostra 1, 2, 3... com largura de 2 caracteres
    }
    printf("\n");    // Pula para a próxima linha

    for (l = 0; l < t->linhas; l++) {        // Para cada linha do tabuleiro
        printf("%c |", 'A' + l);            // Mostra A, B, C, D… antes da linha

        for (c = 0; c < t->colunas; c++) {   // Para cada coluna
            Celula *cel = obterCelula(t, l, c);   // Obtém a célula atual
            char ch;   // Caractere que vai representar essa célula na tela

            if (cel->estado == ESTADO_ACERTO)          ch = 'X';   // Acertou um navio
            else if (cel->estado == ESTADO_ERRO)       ch = '.';   // Tiro na água
            else if (cel->estado == ESTADO_NAVIO && mostrar_navios) ch = 'N'; // Navio visível
            else                                        ch = '~';  // Água sem revelar navio

            printf(" %c ", ch);     // Imprime o símbolo da célula
        }
        printf("|\n");  // Fecha a linha do tabuleiro
    }
}

int lerCoordenada(int *linha, int *coluna, int max_linhas, int max_colunas) { // Lê algo tipo "B5"
    char entrada[16];    // Guarda o que o usuário digitou
    char letra;
    int numero;
    int l, c;

    if (scanf("%15s", entrada) != 1) return 0;   // Se falhou ao ler, retorna erro

    letra = entrada[0];  // Primeiro caractere deve ser uma letra
    if (!isalpha((unsigned char) letra)) return 0;  // Se não for letra → erro

    letra = (char) toupper((unsigned char) letra);  // Converte para MAIÚSCULA
    l = letra - 'A';  // Converte 'A' em 0, 'B' em 1, etc.

    if (sscanf(entrada + 1, "%d", &numero) != 1) return 0;  // Lê o número após a letra
    c = numero - 1;   // Números começam em 1, índices começam em 0

    if (l < 0 || l >= max_linhas || c < 0 || c >= max_colunas) return 0;  // Fora do tabuleiro → erro

    *linha = l;    // Salva a linha lida
    *coluna = c;   // Salva a coluna lida
    return 1;      // Sucesso!
}

void exibirMensagem(const char *msg) {  // Imprime uma mensagem simples na tela
    printf("%s\n", msg);
}