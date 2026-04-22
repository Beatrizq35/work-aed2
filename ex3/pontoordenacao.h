#ifndef PONTOORDENACAO_H
#define PONTOORDENACAO_H

#include <time.h>  // necessário para struct timespec

typedef struct {
    int *vetorBase;
    int *vetorTeste;
    unsigned tamanho;
} VetorTeste;

VetorTeste* criarVetores(unsigned tamanho);
void destruirVetores(VetorTeste *vt);
void preencherVetorAleatoriamente(int *v, unsigned n);
void resetarVetor(int *destino, int *origem, int tamanho);



void BubbleSort(int *v, int n);
void insertionSort(int *v, int n);
void selectionSort(int *v, int n);
void quickSort(int *v, int inicio, int fim);
void mergeSort(int *v, int inicio, int fim);

#endif