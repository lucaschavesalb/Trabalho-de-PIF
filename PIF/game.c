#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"
#include "io.h" // chama as funções lá do .h´s 
#include "rnd.h"

// Inicializa a estrutura do jogador, configurando nome e alocando memória para os tabuleiros
void inicializarJogador(Jogador *j, const char *apelido, int linhas, int colunas) {
    // Copia o apelido para a struct de forma segura (limita ao tamanho do buffer)
    strncpy(j->apelido, apelido, sizeof(j->apelido) - 1);
    // Garante que a string termine com o caractere nulo (fim de string em C)
    j->apelido[sizeof(j->apelido) - 1] = '\0';

    // Chama funções de 'game.h' passando o endereço (&) para modificar os dados originais
    inicializarTabuleiro(&j->tabuleiro, linhas, colunas); // Tabuleiro onde ficam os navios
    inicializarTabuleiro(&j->tiros, linhas, colunas);     // Tabuleiro de registro de tiros (radar)
    inicializarFrota(&j->frota);                          // Prepara o vetor de navios
    criarFrotaPadrao(&j->frota);                          // Preenche a frota com os navios padrão

    // Zera os contadores de estatísticas
    j->total_tiros = 0;
    j->total_acertos = 0;
}

// Libera toda a memória alocada dinamicamente para evitar vazamentos (memory leaks)
void liberarJogador(Jogador *j) {
    liberarTabuleiro(&j->tabuleiro);
    liberarTabuleiro(&j->tiros);
    liberarFrota(&j->frota);
}

// Algoritmo para posicionar os navios aleatoriamente 
void posicionarFrotaAuto(Jogador *j) {
    int i;
    // Itera sobre cada navio disponível na frota
    for (i = 0; i < j->frota.quantidade; i++) {
        Navio *n = &j->frota.navios[i]; // Ponteiro para o navio atual
        int colocado = 0; // Flag de controle do loop while

        // Tenta gerar coordenadas até encontrar uma válida
        while (!colocado) {
            // Gera linha/coluna aleatória dentro dos limites (resto da divisão)
            int linha = rand() % j->tabuleiro.linhas;
            int coluna = rand() % j->tabuleiro.colunas;
            // Define orientação aleatória (par = Horizontal, ímpar = Vertical)
            Orientacao o = (rand() % 2 == 0) ? ORIENTACAO_H : ORIENTACAO_V;

            // Verifica se o navio cabe e não colide com outros
            if (podeColocarNavio(&j->tabuleiro, linha, coluna, o, n->tamanho)) {
                colocarNavio(&j->tabuleiro, linha, coluna, o, n->tamanho, i);
                colocado = 1; // Sucesso: sai do while e vai para o próximo navio
            }
        }
    }
}

// Permite ao usuário escolher as coordenadas dos navios
void posicionarFrotaManual(Jogador *j) {
    int i;
    printf("\nPosicionando navios de %s (manual)\n", j->apelido);
    exibirTabuleiro(&j->tabuleiro, 1); // Mostra o tabuleiro (1 indica modo de visualização)

    for (i = 0; i < j->frota.quantidade; i++) {
        Navio *n = &j->frota.navios[i];
        int colocado = 0;

        // Loop de validação de entrada
        while (!colocado) {
            int linha, coluna;
            char ch;
            Orientacao o;

            printf("\nNavio: %s (tamanho %d)\n", n->nome, n->tamanho);
            printf("Digite coordenada inicial (ex: A1): ");

            // Lê a coordenada e converte para índices numéricos. Retorna falso se inválido.
            if (!lerCoordenada(&linha, &coluna, j->tabuleiro.linhas, j->tabuleiro.colunas)) {
                exibirMensagem("Coordenada invalida.");
                continue; // Reinicia o loop while
            }

            printf("Orientacao (H = horizontal, V = vertical): ");
            scanf(" %c", &ch); // O espaço antes de %c ignora quebras de linha pendentes
            ch = (char) toupper((unsigned char) ch); // Converte para maiúscula

            // Define o enum de orientação baseado no char
            if (ch == 'H')      o = ORIENTACAO_H;
            else if (ch == 'V') o = ORIENTACAO_V;
            else {
                exibirMensagem("Orientacao invalida.");
                continue;
            }

            // Validação lógica do jogo (limites e colisão)
            if (!podeColocarNavio(&j->tabuleiro, linha, coluna, o, n->tamanho)) {
                exibirMensagem("Nao e possivel posicionar o navio aqui (colisao ou fora do limite).");
                continue;
            }

            // Se passou em tudo, coloca o navio e atualiza a tela
            colocarNavio(&j->tabuleiro, linha, coluna, o, n->tamanho, i);
            colocado = 1;
            exibirTabuleiro(&j->tabuleiro, 1);
        }
    }
}

// Lógica de ataque: Atirador ataca o tabuleiro do Alvo
void jogadorAtira(Jogador *atirador, Jogador *alvo) {
    int linha, coluna;
    int deu_certo = 0; // Flag para garantir que o jogador faça uma jogada válida

    while (!deu_certo) {
        printf("%s, digite coordenada do tiro (ex: B5): ", atirador->apelido);

        // Validação da entrada da coordenada (sintaxe)
        if (!lerCoordenada(&linha, &coluna, alvo->tabuleiro.linhas, alvo->tabuleiro.colunas)) {
            exibirMensagem("Entrada invalida.");
            continue;
        }

        // Obtém ponteiros para as células correspondentes nos dois tabuleiros envolvidos
        Celula *cel_alvo = obterCelula(&alvo->tabuleiro, linha, coluna); // Onde o inimigo tem os navios
        Celula *cel_tiro = obterCelula(&atirador->tiros, linha, coluna); // Onde eu marco meus tiros

        // Validação lógica: Impede atirar onde já foi atirado (não é ÁGUA virgem)
        if (cel_tiro->estado != ESTADO_AGUA) {
            exibirMensagem("Voce ja atirou nesta posicao.");
            continue;
        }

        atirador->total_tiros++; // Incrementa estatística

        // Verifica se havia um navio na célula do inimigo
        if (cel_alvo->estado == ESTADO_NAVIO) {
            exibirMensagem("ACERTOU!");
            cel_alvo->estado = ESTADO_ACERTO; // Atualiza tabuleiro do inimigo (dano)
            cel_tiro->estado = ESTADO_ACERTO; // Atualiza meu radar (marca hit)
            atirador->total_acertos++;

            // Lógica para verificar afundamento
            if (cel_alvo->id_navio >= 0 && cel_alvo->id_navio < alvo->frota.quantidade) {
                Navio *n = &alvo->frota.navios[cel_alvo->id_navio]; // Ponteiro para o navio atingido
                n->acertos++; // Incrementa contador de danos do navio
                
                // Se danos totais == tamanho do navio, ele afundou
                if (n->acertos == n->tamanho) {
                    printf("AFUNDOU o navio: %s\n", n->nome);
                }
            }
        } else {
            // Se não tinha navio, é água (erro)
            exibirMensagem("AGUA.");
            cel_alvo->estado = ESTADO_ERRO; // Marca erro no inimigo
            cel_tiro->estado = ESTADO_ERRO; // Marca erro no meu radar
        }

        deu_certo = 1; // Jogada válida concluída
    }
}
