/* TAD: Vetor de inteiros e operações de busca */

#ifndef EX5_H
#define EX5_H

#include <time.h>

/*----------------*/
/* Tipo exportado */
/*----------------*/
typedef struct vetor Vetor;

/*--------------------*/
/* Funcoes exportadas */
/*--------------------*/

/* Funcao criaVetDesordenado
** Aloca e retorna um vetor de inteiros com 'tam' elementos aleatórios desordenados
*/
Vetor* criaVetDesordenado(int tam);

/* Funcao criaVetOrdenado
** Aloca e retorna um vetor de inteiros com 'tam' elementos aleatórios ordenados
*/
Vetor* criaVetOrdenado(int tam);

/* Funcao liberaVetor
** Libera a memória de um vetor previamente criado
*/
void liberaVetor(Vetor *v);

/* Funcao acessaElemento
** Retorna o valor do elemento na posição 'pos' do vetor
*/
int acessaElemento(Vetor *v, int pos);

/* Funcao tamanhoVetor
** Retorna o tamanho do vetor
*/
int tamanhoVetor(Vetor *v);

/* Funcao buscaSequencial
** Retorna 1 se a chave for encontrada, 0 caso contrário
*/
int buscaSequencial(Vetor *v, int key);

/* Funcao buscaBinaria
** Retorna 1 se a chave for encontrada, 0 caso contrário (vetor deve estar ordenado)
*/
int buscaBinaria(Vetor *v, int key);

/* Funcao calculaTempo
** Calcula a diferença de tempo entre início e fim em segundos
*/
double calculaTempo(struct timespec inicio, struct timespec fim);

/* Funcao calculaMedia
** Calcula a média de um vetor de tempos
*/
double calculaMedia(double tempos[], int n);

/* Funcao desvioPadrao
** Calcula o desvio padrão de um vetor de tempos
*/
double desvioPadrao(double tempos[], int n);

#endif
