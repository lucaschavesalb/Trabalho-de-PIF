#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"
#include "io.h"
#include "rnd.h"

void inicializarJogador(Jogador *j, const char *apelido, int linhas, int colunas) {
    strncpy(j->apelido, apelido, sizeof(j->apelido) - 1);
    j->apelido[sizeof(j->apelido) - 1] = '\0';

    inicializarTabuleiro(&j->tabuleiro, linhas, colunas);
    inicializarTabuleiro(&j->tiros, linhas, colunas);
    inicializarFrota(&j->frota);
    criarFrotaPadrao(&j->frota);

    j->total_tiros = 0;
    j->total_acertos = 0;
}

void liberarJogador(Jogador *j) {
    liberarTabuleiro(&j->tabuleiro);
    liberarTabuleiro(&j->tiros);
    liberarFrota(&j->frota);
}

void posicionarFrotaAuto(Jogador *j) {
    int i;
    for (i = 0; i < j->frota.quantidade; i++) {
        Navio *n = &j->frota.navios[i];
        int colocado = 0;

        while (!colocado) {
            // Usa o módulo RND indiretamente via rand() ou wrapper
            int linha = rand() % j->tabuleiro.linhas;
            int coluna = rand() % j->tabuleiro.colunas;
            Orientacao o = (rand() % 2 == 0) ? ORIENTACAO_H : ORIENTACAO_V;

            if (podeColocarNavio(&j->tabuleiro, linha, coluna, o, n->tamanho)) {
                colocarNavio(&j->tabuleiro, linha, coluna, o, n->tamanho, i);
                colocado = 1;
            }
        }
    }
}

void posicionarFrotaManual(Jogador *j) {
    int i;
    printf("\nPosicionando navios de %s (manual)\n", j->apelido);
    exibirTabuleiro(&j->tabuleiro, 1); // Usa módulo IO

    for (i = 0; i < j->frota.quantidade; i++) {
        Navio *n = &j->frota.navios[i];
        int colocado = 0;

        while (!colocado) {
            int linha, coluna;
            char ch;
            Orientacao o;

            printf("\nNavio: %s (tamanho %d)\n", n->nome, n->tamanho);
            printf("Digite coordenada inicial (ex: A1): ");

            if (!lerCoordenada(&linha, &coluna, j->tabuleiro.linhas, j->tabuleiro.colunas)) {
                exibirMensagem("Coordenada invalida.");
                continue;
            }

            printf("Orientacao (H = horizontal, V = vertical): ");
            scanf(" %c", &ch);
            ch = (char) toupper((unsigned char) ch);

            if (ch == 'H')      o = ORIENTACAO_H;
            else if (ch == 'V') o = ORIENTACAO_V;
            else {
                exibirMensagem("Orientacao invalida.");
                continue;
            }

            if (!podeColocarNavio(&j->tabuleiro, linha, coluna, o, n->tamanho)) {
                exibirMensagem("Nao e possivel posicionar o navio aqui (colisao ou fora do limite).");
                continue;
            }

            colocarNavio(&j->tabuleiro, linha, coluna, o, n->tamanho, i);
            colocado = 1;
            exibirTabuleiro(&j->tabuleiro, 1);
        }
    }
}

void jogadorAtira(Jogador *atirador, Jogador *alvo) {
    int linha, coluna;
    int deu_certo = 0;

    while (!deu_certo) {
        printf("%s, digite coordenada do tiro (ex: B5): ", atirador->apelido);

        if (!lerCoordenada(&linha, &coluna, alvo->tabuleiro.linhas, alvo->tabuleiro.colunas)) {
            exibirMensagem("Entrada invalida.");
            continue;
        }

        Celula *cel_alvo = obterCelula(&alvo->tabuleiro, linha, coluna);
        Celula *cel_tiro = obterCelula(&atirador->tiros, linha, coluna);

        // Validação extra caso coordenada seja válida mas lógica do jogo impeça
        if (cel_tiro->estado != ESTADO_AGUA) {
            exibirMensagem("Voce ja atirou nesta posicao.");
            continue;
        }

        atirador->total_tiros++;

        if (cel_alvo->estado == ESTADO_NAVIO) {
            exibirMensagem("ACERTOU!");
            cel_alvo->estado = ESTADO_ACERTO;
            cel_tiro->estado = ESTADO_ACERTO;
            atirador->total_acertos++;

            if (cel_alvo->id_navio >= 0 && cel_alvo->id_navio < alvo->frota.quantidade) {
                Navio *n = &alvo->frota.navios[cel_alvo->id_navio];
                n->acertos++;
                if (n->acertos == n->tamanho) {
                    printf("AFUNDOU o navio: %s\n", n->nome);
                }
            }
        } else {
            exibirMensagem("AGUA.");
            cel_alvo->estado = ESTADO_ERRO;
            cel_tiro->estado = ESTADO_ERRO;
        }

        deu_certo = 1;
    }
}