#include <stdio.h>     
#include <stdlib.h>    
#include <ctype.h>    
#include "game.h"     
#include "io.h"       
#include "rnd.h"  // chama as funções lá do .h´s      

int g_linhas = 10;      // Tamanho padrão das linhas
int g_colunas = 10;     // Tamanho padrão das colunas
char g_modo_posicionamento = 'A';  // 'A' = automático, 'M' = manual

void rodarPartida(Jogo *jogo) {     // Controla o fluxo da partida
    while (!jogo->jogo_acabou) {    // Continua até alguém ganhar
        Jogador *atual;
        Jogador *inimigo;

        if (jogo->jogador_atual == 1) {  // Se for a vez do jogador 1
            atual = &jogo->j1;
            inimigo = &jogo->j2;
        } else {                          // Vez do jogador 2
            atual = &jogo->j2;
            inimigo = &jogo->j1;
        }

        printf("\n--- Turno de %s ---\n", atual->apelido);  // Mostra quem está jogando

        printf("Seu tabuleiro:\n");
        exibirTabuleiro(&atual->tabuleiro, 1);  // Mostra seu próprio tabuleiro

        printf("\nMapa de tiros em %s:\n", inimigo->apelido);
        exibirTabuleiro(&atual->tiros, 0);  // Mostra onde já atirou

        jogadorAtira(atual, inimigo);  // Executa o tiro

        if (frotaAfundou(&inimigo->frota)) {   // Se todos os navios afundaram
            double precisao1 = 0.0; // Guarda a precisão (acertos / tiros) do jogador 1
            double precisao2 = 0.0; // Guarda a precisão do jogador 2

            printf("\n** FIM DE JOGO **\n"); // Mensagem avisando que o jogo acabou
            printf("Vencedor: %s\n", atual->apelido); // Mostra o apelido do vencedor

            // Calcula a precisão do jogador 1 SE ele realmente atirou pelo menos uma vez
            if (jogo->j1.total_tiros > 0) 
                precisao1 = (100.0 * jogo->j1.total_acertos) / jogo->j1.total_tiros;
             // Fórmula: (acertos / tiros) * 100 para virar porcentagem

            // Calcula a precisão do jogador 2 SE ele realmente atirou
            if (jogo->j2.total_tiros > 0)
                precisao2 = (100.0 * jogo->j2.total_acertos) / jogo->j2.total_tiros;
            // Mesma fórmula do jogador 1

            printf("\nEstatisticas:\n"); // Título da parte que mostra estatísticas

            // Mostra tiros, acertos e precisão do jogador 1
            printf("%s -> tiros: %d | acertos: %d | precisao: %.1f%%\n", 
                   jogo->j1.apelido, jogo->j1.total_tiros, jogo->j1.total_acertos, precisao1);

             // Mostra tiros, acertos e precisão do jogador 2
            printf("%s -> tiros: %d | acertos: %d | precisao: %.1f%%\n",
                   jogo->j2.apelido, jogo->j2.total_tiros, jogo->j2.total_acertos, precisao2);

            printf("\nEstado final dos tabuleiros:\n"); // Título antes de mostrar tabuleiros completos
            printf("Tabuleiro de %s:\n", jogo->j1.apelido); // Diz de quem é o tabuleiro
            exibirTabuleiro(&jogo->j1.tabuleiro, 1); // Mostra o tabuleiro do jogador 1 com navios visíveis

            printf("Tabuleiro de %s:\n", jogo->j2.apelido); // Mesma coisa para o jogador 2
            exibirTabuleiro(&jogo->j2.tabuleiro, 1); // Mostra o tabuleiro final completo

            jogo->jogo_acabou = 1;   // Marca que acabou o jogo
        } else {
            jogo->jogador_atual = (jogo->jogador_atual == 1 ? 2 : 1); // Troca turno
        }
    }
}

void configurarJogo() {               // Permite mudar tamanho e modo de posicionamento
    int novo_tam; // Novo tamanho desejado
    char novo_modo; // Novo modo desejado

    printf("\n=== CONFIGURACOES ===\n"); 
    printf("Tamanho atual: %dx%d\n", g_linhas, g_colunas); //escolher o tamanho do tabuleiro

    printf("Novo tamanho (6-26): ");
    if (scanf("%d", &novo_tam) == 1) {       // Se digitou um número válido
        if (novo_tam >= 6 && novo_tam <= 26) {
            g_linhas = novo_tam;             // Atualiza tabuleiro
            g_colunas = novo_tam;
        } else {
            printf("Valor invalido, mantendo o atual.\n");
        }
    }

    printf("Modo atual: %c (M = manual, A = automatico)\n", g_modo_posicionamento);
    printf("Novo modo (M/A): ");
    scanf(" %c", &novo_modo);              // Lê o novo modo (com espaço para ignorar \n)
    novo_modo = (char) toupper((unsigned char) novo_modo); // Deixa maiúsculo

    if (novo_modo == 'M' || novo_modo == 'A')
        g_modo_posicionamento = novo_modo;  // Atualiza modo
    else
        printf("Modo invalido, mantendo o atual.\n"); 
}

int main(void) {
    Jogo jogo;             // Estrutura principal do jogo
    int opcao;             // Opção escolhida no menu
    char nome1[32], nome2[32]; // Apelidos dos jogadores

    inicializarAleatorio(); // Inicia números aleatórios

    jogo.j1.tabuleiro.celulas = NULL; // Evita lixo de memória
    jogo.j1.tiros.celulas = NULL;
    jogo.j1.frota.navios = NULL;
    jogo.j2.tabuleiro.celulas = NULL;
    jogo.j2.tiros.celulas = NULL;
    jogo.j2.frota.navios = NULL;

    do {
        printf("\n=== BATALHA NAVAL ===\n"); // Menu Principal
        printf("1) Novo jogo\n");
        printf("2) Configuracoes\n");
        printf("3) Sair\n");
        printf("> ");

        if (scanf("%d", &opcao) != 1) {  // Se digitar errado
            while (getchar() != '\n');   // Limpa o teclado
            continue;
        }

        if (opcao == 1) {   // Começar novo jogo
            printf("Apelido Jogador 1: ");
            scanf("%31s", nome1); // Lê nome do P1

            printf("Apelido Jogador 2: ");
            scanf("%31s", nome2); // Lê nome do P2

            liberarJogador(&jogo.j1); // Garante limpeza
            liberarJogador(&jogo.j2);

            inicializarJogador(&jogo.j1, nome1, g_linhas, g_colunas); // Cria P1
            inicializarJogador(&jogo.j2, nome2, g_linhas, g_colunas); // Cria P2

            jogo.jogo_acabou = 0; // Reset do jogo
            jogo.jogador_atual = 1; // Jogador 1 começa

            if (g_modo_posicionamento == 'M') {
                posicionarFrotaManual(&jogo.j1); // Posição manual P1
                posicionarFrotaManual(&jogo.j2); // Posição manual P2
            } else {
                printf("Posicionando navios auto...\n");
                posicionarFrotaAuto(&jogo.j1); // Posição automática P1
                posicionarFrotaAuto(&jogo.j2); // Posição automática P2
            }

            rodarPartida(&jogo);  // Roda o jogo inteiro

            liberarJogador(&jogo.j1); // Limpa memória
            liberarJogador(&jogo.j2);
        }

        else if (opcao == 2)
            configurarJogo();   // Abre menu de configurações

        else if (opcao == 3) 
            printf("Saindo...\n"); // Mensagem de saída


    } while (opcao != 3);   // Sai quando escolher “3”

    return 0;   // Fim do programa
}