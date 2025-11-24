#ifndef RND_H
#define RND_H

/* Inicializa a semente do rand */
void inicializarAleatorio(void);

/* Retorna inteiro entre min e max (inclusivo) - apenas helper se precisar */
int obterNumeroAleatorio(int min, int max);

#endif