# Batalha Naval - PIFSI 2025.2

Projeto desenvolvido para a disciplina *Projetos de Sistemas de Informação (CESAR School), implementando o clássico jogo de tabuleiro **Batalha Naval* em *C*.

O objetivo principal é exercitar conceitos avançados da linguagem C, como *alocação dinâmica de memória, ponteiros, structs e modularização*, em um jogo interativo para dois jogadores.

*Professor responsável:* João Victor Tinoco

---

## Equipe

* Heitor Castilhos
* Lucas Chaves
* Luiz Gustavo

---

## Sobre o Projeto

O projeto permite que dois jogadores disputem partidas no estilo PvP local. Ele suporta:

* Tabuleiros de tamanho configurável (de 6x6 até 26x26).
* Posicionamento de navios *manual* ou *automático*.
* Sistema de turnos com validação de tiros repetidos.
* Relatório de estatísticas ao final da partida, incluindo precisão de tiros.

O desenvolvimento enfatiza boas práticas de *organização de código, **separação de responsabilidades* e *gerenciamento eficiente de memória*.

---

## Estrutura e Decisões de Design

### Organização do Código

O sistema foi dividido em módulos coesos para manter a lógica limpa e facilitar manutenção:

| Arquivo     | Responsabilidade                                        |
| ----------- | ------------------------------------------------------- |
| board.c/h | Gerencia o tabuleiro e o estado das células.            |
| fleet.c/h | Gerencia a frota de navios e suas operações.            |
| game.c/h  | Controla o fluxo do jogo: turnos, regras e vitória.     |
| io.c/h    | Centraliza toda entrada/saída (printf/scanf).           |
| rnd.c/h   | Funções utilitárias para geração de números aleatórios. |
| main.c    | Ponto de entrada e menu de configurações.               |

---

### Gerenciamento de Memória

* *Tabuleiro*: alocado dinamicamente como vetor unidimensional (Cell*) de tamanho linhas * colunas.
  Isso permite redimensionamento em tempo de execução sem desperdício de memória.
  Acesso via aritmética de ponteiros:

  c
  índice = linha * colunas + coluna;
  
* *Frota*: utiliza realloc para ajustar dinamicamente o vetor de navios conforme necessário.
* *Liberação de memória*: toda memória é liberada ao final do jogo ou reinício, seguindo a ordem inversa da alocação.

---

### Representação de Dados

* *Structs*: modelam Jogador, Tabuleiro, Frota e Navio, encapsulando dados relacionados.
* *Enums*: representam estados (AGUA, NAVIO, ACERTO, ERRO) e orientações, evitando "números mágicos" e melhorando legibilidade.

---

## Funcionalidades Implementadas

* Tabuleiro dinâmico e configurável (6x6 a 26x26).
* Posicionamento manual de navios (com validação de colisão).
* Posicionamento automático de navios (aleatório).
* Sistema de turnos com validação de tiros repetidos.
* Detecção de vitória (afundar toda a frota).
* Estatísticas finais de precisão de tiros.

---

## Como Compilar e Executar

O projeto conta com um *Makefile* para automatizar a compilação.

### Pré-requisitos

* Compilador GCC
* Make (opcional, mas recomendado)

### Passos

1. Abra o terminal na pasta raiz do projeto.
2. Compile o código:

bash
make


3. Execute o jogo:

bash
# Linux/Mac
./batalha_naval

# Windows
batalha_naval.exe


4. Para limpar arquivos objetos e executáveis:

bash
make clean


---

## Bibliotecas Utilizadas

Apenas bibliotecas padrão do C:
<stdio.h>, <stdlib.h>, <string.h>, <time.h>, <ctype.h>, <stdbool.h>

---

*Desenvolvido em Novembro de 2025*
