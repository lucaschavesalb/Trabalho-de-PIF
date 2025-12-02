#ifndef RND_H
#define RND_H
// Evita incluir o arquivo mais de uma vez

/* Inicializa a semente do rand */
void inicializarAleatorio(void);

/* Retorna inteiro entre min e max (inclusivo) - apenas helper se precisar */
int obterNumeroAleatorio(int min, int max);

#endif // Fecha proteção