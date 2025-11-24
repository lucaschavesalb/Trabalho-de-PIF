#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"
#include "io.h"
#include "rnd.h"

/* Configurações padrão */
int g_linhas = 10;
int g_colunas = 10;
char g_modo_posicionamento = 'A';

void rodarPartida(Jogo *jogo) {
    while (!jogo->jogo_acabou) {
        Jogador *atual;
        Jogador *inimigo;

        if (jogo->jogador_atual == 1) {
            atual = &jogo->j1;
            inimigo = &jogo->j2;
        } else {
            atual = &jogo->j2;
            inimigo = &jogo->j1;
        }

        printf("\n--- Turno de %s ---\n", atual->apelido);
        printf("Seu tabuleiro:\n");
        exibirTabuleiro(&atual->tabuleiro, 1);
        printf("\nMapa de tiros em %s:\n", inimigo->apelido);
        exibirTabuleiro(&atual->tiros, 0);

        jogadorAtira(atual, inimigo);

        if (frotaAfundou(&inimigo->frota)) {
            double precisao1 = 0.0;
            double precisao2 = 0.0;

            printf("\n*** FIM DE JOGO ***\n");
            printf("Vencedor: %s\n", atual->apelido);

            if (jogo->j1.total_tiros > 0)
                precisao1 = (100.0 * jogo->j1.total_acertos) / jogo->j1.total_tiros;
            if (jogo->j2.total_tiros > 0)
                precisao2 = (100.0 * jogo->j2.total_acertos) / jogo->j2.total_tiros;

            printf("\nEstatisticas:\n");
            printf("%s -> tiros: %d | acertos: %d | precisao: %.1f%%\n",
                   jogo->j1.apelido, jogo->j1.total_tiros, jogo->j1.total_acertos, precisao1);
            printf("%s -> tiros: %d | acertos: %d | precisao: %.1f%%\n",
                   jogo->j2.apelido, jogo->j2.total_tiros, jogo->j2.total_acertos, precisao2);

            // Exibir tabuleiros finais [cite: 100]
            printf("\nEstado final dos tabuleiros:\n");
            printf("Tabuleiro de %s:\n", jogo->j1.apelido);
            exibirTabuleiro(&jogo->j1.tabuleiro, 1);
            printf("Tabuleiro de %s:\n", jogo->j2.apelido);
            exibirTabuleiro(&jogo->j2.tabuleiro, 1);

            jogo->jogo_acabou = 1;
        } else {
            jogo->jogador_atual = (jogo->jogador_atual == 1) ? 2 : 1;
        }
    }
}

void configurarJogo() {
    int novo_tam;
    char novo_modo;

    printf("\n=== CONFIGURACOES ===\n");
    printf("Tamanho atual: %dx%d\n", g_linhas, g_colunas);
    printf("Novo tamanho (6-26): ");
    if (scanf("%d", &novo_tam) == 1) {
        if (novo_tam >= 6 && novo_tam <= 26) {
            g_linhas = novo_tam;
            g_colunas = novo_tam;
        } else {
            printf("Valor invalido, mantendo o atual.\n");
        }
    }

    printf("Modo atual: %c (M = manual, A = automatico)\n", g_modo_posicionamento);
    printf("Novo modo (M/A): ");
    scanf(" %c", &novo_modo);
    novo_modo = (char) toupper((unsigned char) novo_modo);

    if (novo_modo == 'M' || novo_modo == 'A') {
        g_modo_posicionamento = novo_modo;
    } else {
        printf("Modo invalido, mantendo o atual.\n");
    }
}

int main(void) {
    Jogo jogo;
    int opcao;
    char nome1[32], nome2[32];

    inicializarAleatorio(); // Em rnd.c

    // Zerar ponteiros para segurança inicial
    jogo.j1.tabuleiro.celulas = NULL;
    jogo.j1.tiros.celulas = NULL;
    jogo.j1.frota.navios = NULL;
    jogo.j2.tabuleiro.celulas = NULL;
    jogo.j2.tiros.celulas = NULL;
    jogo.j2.frota.navios = NULL;

    do {
        printf("\n=== BATALHA NAVAL ===\n");
        printf("1) Novo jogo\n");
        printf("2) Configuracoes\n");
        printf("3) Sair\n");
        printf("> ");

        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); // Limpa buffer se errar
            continue;
        }

        if (opcao == 1) {
            // Preparação
            printf("Apelido Jogador 1: ");
            scanf("%31s", nome1);
            printf("Apelido Jogador 2: ");
            scanf("%31s", nome2);

            // Limpeza de segurança antes de iniciar
            liberarJogador(&jogo.j1);
            liberarJogador(&jogo.j2);

            inicializarJogador(&jogo.j1, nome1, g_linhas, g_colunas);
            inicializarJogador(&jogo.j2, nome2, g_linhas, g_colunas);

            jogo.jogo_acabou = 0;
            jogo.jogador_atual = 1;

            if (g_modo_posicionamento == 'M') {
                posicionarFrotaManual(&jogo.j1);
                posicionarFrotaManual(&jogo.j2);
            } else {
                printf("Posicionando navios auto...\n");
                posicionarFrotaAuto(&jogo.j1);
                posicionarFrotaAuto(&jogo.j2);
            }

            rodarPartida(&jogo);

            // Libera memória ao fim da partida
            liberarJogador(&jogo.j1);
            liberarJogador(&jogo.j2);

        } else if (opcao == 2) {
            configurarJogo();
        } else if (opcao == 3) {
            printf("Saindo...\n");
        }

    } while (opcao != 3);

    return 0;
}