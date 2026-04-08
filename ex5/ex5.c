/*
** TAD: Vetor de inteiros
** Implementa criação, busca sequencial, busca binária e funções estatísticas
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "EX5.h"

/*---------------------------*/
/* Estrutura interna (opaca) */
/*---------------------------*/
struct vetor {
    int *dados;
    int tamanho;
};

/* Funcao criaVetDesordenado
** Aloca e retorna um vetor com 'tam' inteiros aleatórios desordenados
*/
Vetor* criaVetDesordenado(int tam) {
    Vetor *v = (Vetor*) malloc(sizeof(Vetor));
    if (v == NULL) {
        printf("Erro ao alocar estrutura Vetor!\n");
        exit(1);
    }

    v->dados = (int*) malloc(tam * sizeof(int));
    if (v->dados == NULL) {
        printf("Erro ao alocar dados do Vetor!\n");
        exit(1);
    }

    v->tamanho = tam;
    for (int i = 0; i < tam; i++) {
        v->dados[i] = rand() % (tam * 10);
    }

    return v;
}

/* Funcao criaVetOrdenado
** Aloca e retorna um vetor com 'tam' inteiros aleatórios em ordem crescente
*/
Vetor* criaVetOrdenado(int tam) {
    Vetor *v = (Vetor*) malloc(sizeof(Vetor));
    if (v == NULL) {
        printf("Erro ao alocar estrutura Vetor!\n");
        exit(1);
    }

    v->dados = (int*) malloc(tam * sizeof(int));
    if (v->dados == NULL) {
        printf("Erro ao alocar dados do Vetor!\n");
        exit(1);
    }

    v->tamanho = tam;
    int atual = rand() % 10;
    for (int i = 0; i < tam; i++) {
        v->dados[i] = atual;
        atual += (rand() % 5) + 1;
    }

    return v;
}

/* Funcao liberaVetor
** Libera a memória de um vetor previamente criado
*/
void liberaVetor(Vetor *v) {
    free(v->dados);
    free(v);
}

/* Funcao acessaElemento
** Retorna o valor do elemento na posição 'pos'
*/
int acessaElemento(Vetor *v, int pos) {
    return v->dados[pos];
}

/* Funcao tamanhoVetor
** Retorna o tamanho do vetor
*/
int tamanhoVetor(Vetor *v) {
    return v->tamanho;
}

/* Funcao buscaSequencial
** Percorre o vetor linearmente comparando cada elemento com a chave
** Retorna 1 se encontrado, 0 se não encontrado
*/
int buscaSequencial(Vetor *v, int key) {
    for (int i = 0; i < v->tamanho; i++) {
        if (v->dados[i] == key) {
            return 1;
        }
    }
    return 0;
}

/* Funcao buscaBinaria
** Divide o vetor ao meio a cada passo (vetor deve estar ordenado)
** Retorna 1 se encontrado, 0 se não encontrado
*/
int buscaBinaria(Vetor *v, int key) {
    int inicio = 0, fim = v->tamanho - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (key > v->dados[meio]) {
            inicio = meio + 1;
        } else if (key < v->dados[meio]) {
            fim = meio - 1;
        } else {
            return 1;
        }
    }
    return 0;
}

/* Funcao calculaTempo
** Retorna a diferença de tempo entre inicio e fim em segundos
*/
double calculaTempo(struct timespec inicio, struct timespec fim) {
    return (fim.tv_sec - inicio.tv_sec) +
           (fim.tv_nsec - inicio.tv_nsec) / 1e9;
}

/* Funcao calculaMedia
** Retorna a média aritmética de um vetor de 'n' tempos
*/
double calculaMedia(double tempos[], int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++) {
        soma += tempos[i];
    }
    return soma / n;
}

/* Funcao desvioPadrao
** Retorna o desvio padrão de um vetor de 'n' tempos
*/
double desvioPadrao(double tempos[], int n) {
    double media = calculaMedia(tempos, n);
    double soma  = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = tempos[i] - media;
        soma += diff * diff;
    }
    return sqrt(soma / n);
}