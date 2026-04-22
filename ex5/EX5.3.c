/*
** TAD: Ordenacao de vetores de inteiros
** Implementa Bolha, Insercao Direta, Selecao Direta, Quicksort e Merge Sort
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EX5.3.h"

/*---------------------------*/
/* Estrutura interna (opaca) */
/*---------------------------*/
struct vetorOrd {
    int *dados;
    int  tamanho;
};

/* Funcao criaVetorOrd
** Aloca e retorna um vetor com 'tam' inteiros aleatorios desordenados
*/
VetorOrd* criaVetorOrd(int tam) {
    VetorOrd *v = (VetorOrd*) malloc(sizeof(VetorOrd));
    if (v == NULL) { printf("Erro ao alocar VetorOrd!\n"); exit(1); }

    v->dados = (int*) malloc(tam * sizeof(int));
    if (v->dados == NULL) { printf("Erro ao alocar dados VetorOrd!\n"); exit(1); }

    v->tamanho = tam;
    for (int i = 0; i < tam; i++) {
        v->dados[i] = rand() % (tam * 10);
    }
    return v;
}

/* Funcao copiaVetorOrd
** Retorna uma copia independente do vetor recebido
** Usada para garantir que cada algoritmo receba os mesmos valores por rodada
*/
VetorOrd* copiaVetorOrd(VetorOrd *v) {
    VetorOrd *c = (VetorOrd*) malloc(sizeof(VetorOrd));
    if (c == NULL) { printf("Erro ao alocar copia VetorOrd!\n"); exit(1); }

    c->dados = (int*) malloc(v->tamanho * sizeof(int));
    if (c->dados == NULL) { printf("Erro ao alocar dados copia!\n"); exit(1); }

    c->tamanho = v->tamanho;
    memcpy(c->dados, v->dados, v->tamanho * sizeof(int));
    return c;
}

/* Funcao liberaVetorOrd
** Libera a memoria de um VetorOrd
*/
void liberaVetorOrd(VetorOrd *v) {
    free(v->dados);
    free(v);
}

/* Funcao tamanhoVetorOrd
** Retorna o tamanho do vetor
*/
int tamanhoVetorOrd(VetorOrd *v) {
    return v->tamanho;
}

/*---------------------------*/
/* Funcao auxiliar de troca  */
/*---------------------------*/
static void troca(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Funcao ordenaBolha
** Compara pares adjacentes e os troca se estiverem fora de ordem
** Complexidade: O(n^2)
*/
void ordenaBolha(VetorOrd *v) {
    int n = v->tamanho;
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v->dados[j] > v->dados[j + 1]) {
                troca(&v->dados[j], &v->dados[j + 1]);
                trocou = 1;
            }
        }
        if (!trocou) break; /* vetor ja ordenado */
    }
}

/* Funcao ordenaInsercao
** Insere cada elemento na posicao correta entre os anteriores ja ordenados
** Complexidade: O(n^2)
*/
void ordenaInsercao(VetorOrd *v) {
    int n = v->tamanho;
    for (int i = 1; i < n; i++) {
        int chave = v->dados[i];
        int j = i - 1;
        while (j >= 0 && v->dados[j] > chave) {
            v->dados[j + 1] = v->dados[j];
            j--;
        }
        v->dados[j + 1] = chave;
    }
}

/* Funcao ordenaSelecao
** Seleciona o menor elemento do subvetor restante e o posiciona
** Complexidade: O(n^2)
*/
void ordenaSelecao(VetorOrd *v) {
    int n = v->tamanho;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (v->dados[j] < v->dados[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            troca(&v->dados[i], &v->dados[min_idx]);
        }
    }
}

/* --- Quicksort ----------------------------------------------------------- */

/* particiona
** Escolhe o ultimo elemento como pivo e reorganiza o subvetor
** Retorna o indice final do pivo
*/
static int particiona(int *arr, int ini, int fim) {
    int pivo = arr[fim];
    int i    = ini - 1;
    for (int j = ini; j < fim; j++) {
        if (arr[j] <= pivo) {
            i++;
            troca(&arr[i], &arr[j]);
        }
    }
    troca(&arr[i + 1], &arr[fim]);
    return i + 1;
}

/* quicksortRec
** Recursao do Quicksort sobre o subvetor arr[ini..fim]
*/
static void quicksortRec(int *arr, int ini, int fim) {
    if (ini < fim) {
        int p = particiona(arr, ini, fim);
        quicksortRec(arr, ini,     p - 1);
        quicksortRec(arr, p + 1,   fim);
    }
}

/* Funcao ordenaQuicksort
** Divide e conquista usando pivo; media O(n log n), pior O(n^2)
*/
void ordenaQuicksort(VetorOrd *v) {
    quicksortRec(v->dados, 0, v->tamanho - 1);
}

/* --- Merge Sort ---------------------------------------------------------- */

/* intercala
** Funde dois subvetores ordenados arr[ini..meio] e arr[meio+1..fim]
*/
static void intercala(int *arr, int ini, int meio, int fim) {
    int n1  = meio - ini + 1;
    int n2  = fim - meio;

    int *esq = (int*) malloc(n1 * sizeof(int));
    int *dir = (int*) malloc(n2 * sizeof(int));
    if (!esq || !dir) { printf("Erro malloc intercala!\n"); exit(1); }

    for (int i = 0; i < n1; i++) esq[i] = arr[ini + i];
    for (int j = 0; j < n2; j++) dir[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = ini;
    while (i < n1 && j < n2) {
        if (esq[i] <= dir[j]) arr[k++] = esq[i++];
        else                   arr[k++] = dir[j++];
    }
    while (i < n1) arr[k++] = esq[i++];
    while (j < n2) arr[k++] = dir[j++];

    free(esq);
    free(dir);
}

/* mergeSortRec
** Recursao do Merge Sort sobre arr[ini..fim]
*/
static void mergeSortRec(int *arr, int ini, int fim) {
    if (ini < fim) {
        int meio = (ini + fim) / 2;
        mergeSortRec(arr, ini,      meio);
        mergeSortRec(arr, meio + 1, fim);
        intercala(arr, ini, meio, fim);
    }
}

/* Funcao ordenaMergeSort
** Divide e conquista com fusao; complexidade O(n log n)
*/
void ordenaMergeSort(VetorOrd *v) {
    mergeSortRec(v->dados, 0, v->tamanho - 1);
}
