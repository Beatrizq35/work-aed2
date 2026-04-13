#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pontoordenacao.h"

#define TAMANHO 100000
#define RODADAS 3

int main() {
    // Cria os vetores via TAD (sem declarar array no main!)
    VetorTeste *vt = criarVetores(TAMANHO);

    clock_t inicio, fim;
    double tempo;
    double somaBolha = 0, somaInsertion = 0, somaSelection = 0,
           somaQuick = 0, somaMerge = 0;

    srand(time(NULL));

    for (int r = 1; r <= RODADAS; r++) {
        preencherVetorAleatoriamente(vt->vetorBase, TAMANHO);
        printf("\n--------------Rodada %d--------------\n", r);

        // Insertion
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        insertionSort(vt->vetorTeste, TAMANHO);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("InsertionSort: %f s\n", tempo);
        somaInsertion += tempo;

        // Bubble
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        BubbleSort(vt->vetorTeste, TAMANHO);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("BubbleSort: %f s\n", tempo);
        somaBolha += tempo;

        // Selection
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        selectionSort(vt->vetorTeste, TAMANHO);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("SelectionSort: %f s\n", tempo);
        somaSelection += tempo;

        // Quick
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        quickSort(vt->vetorTeste, 0, TAMANHO - 1);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("QuickSort: %f s\n", tempo);
        somaQuick += tempo;

        // Merge
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        mergeSort(vt->vetorTeste, 0, TAMANHO - 1);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("MergeSort: %f s\n", tempo);
        somaMerge += tempo;
    }

    printf("\n------Medias (%d rodadas)------\n", RODADAS);
    printf("Bubble:    %f s\n", somaBolha    / RODADAS);
    printf("Insertion: %f s\n", somaInsertion / RODADAS);
    printf("Selection: %f s\n", somaSelection / RODADAS);
    printf("Quick:     %f s\n", somaQuick    / RODADAS);
    printf("Merge:     %f s\n", somaMerge    / RODADAS);

    // Libera memória ao final
    destruirVetores(vt);
    return 0;
}