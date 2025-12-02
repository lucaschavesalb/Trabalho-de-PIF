#ifndef BOARD_H
#define BOARD_H

typedef enum {
    ESTADO_AGUA, 
    ESTADO_NAVIO, 
    ESTADO_ACERTO, 
    ESTADO_ERRO
} EstadoCelula; // Cada casa do tabuleiro pode ter 4 situações!

typedef enum {
    ORIENTACAO_H,
    ORIENTACAO_V
} Orientacao;

typedef struct {
    EstadoCelula estado;
    int id_navio;   // -1 se não tiver navio, ajuda celula a checar rápido
} Celula; // chão quadriculado

typedef struct {
    int linhas;
    int colunas;
    Celula *celulas; //* malloc(linhas * colunas) sabendo que ocorre ( t->celulas = malloc(sizeof(Celula) * linhas * colunas); )
} Tabuleiro;

//  Protótipos das funções
void inicializarTabuleiro(Tabuleiro *t, int linhas, int colunas); // Cria o tabuleiro
void liberarTabuleiro(Tabuleiro *t); // Libera memória
Celula *obterCelula(Tabuleiro *t, int linha, int coluna); // pegar célula 
int podeColocarNavio(Tabuleiro *t, int linha, int coluna, Orientacao o, int tamanho); // validar colocação
void colocarNavio(Tabuleiro *t, int linha, int coluna, Orientacao o, int tamanho, int id_navio); // colocar navio

#endif