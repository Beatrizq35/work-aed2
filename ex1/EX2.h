/* TAD: Lista Encadeada de inteiros */

#ifndef EX2_H
#define EX2_H

#include <time.h>

/*----------------*/
/* Tipo exportado */
/*----------------*/
typedef struct lista Lista;

/*--------------------*/
/* Funcoes exportadas */
/*--------------------*/

/* Funcao criaLista
** Aloca e retorna uma lista encadeada vazia
*/
Lista* criaLista(void);

/* Funcao liberaLista
** Libera toda a memória alocada pela lista
*/
void liberaLista(Lista *l);

/* Funcao criaListaDoVetor
** Aloca e retorna uma lista encadeada com os valores de um vetor (TAD Vetor do EX1)
** Inclui EX1.h internamente — recebe o ponteiro opaco Vetor*
*/
#include "EX1.h"
Lista* criaListaDoVetor(Vetor *v);

/* Funcao buscaSequencialLista
** Retorna 1 se a chave for encontrada, 0 caso contrário
*/
int buscaSequencialLista(Lista *l, int key);

#endif
