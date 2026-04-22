#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pontoordenacao.h"

#define TAM_INICIAL 10000
#define TAM_FINAL   100000
#define INCREMENTO  10000

int main() {
    clock_t inicio, fim;
    srand(time(NULL));

    // Cabeçalho com alinhamento à esquerda (%-12s significa 12 espaços de largura)
    printf("%-10s | %-10s | %-10s | %-10s | %-10s | %-10s\n", 
           "Tamanho", "Bubble", "Insertion", "Selection", "Quick", "Merge");
    printf("-----------|------------|------------|------------|------------|------------\n");

    for (int n = TAM_INICIAL; n <= TAM_FINAL; n += INCREMENTO) {
        VetorTeste *vt = criarVetores(n);
        if (vt == NULL) continue;

        preencherVetorAleatoriamente(vt->vetorBase, n);

        // Imprime o tamanho (primeira coluna)
        printf("%-10d | ", n);

        // --- BUBBLE SORT ---
        resetarVetor(vt->vetorTeste, vt->vetorBase, n);
        inicio = clock();
        BubbleSort(vt->vetorTeste, n);
        fim = clock();
        printf("%-10.4f | ", (double)(fim - inicio) / CLOCKS_PER_SEC);

        // --- INSERTION SORT ---
        resetarVetor(vt->vetorTeste, vt->vetorBase, n);
        inicio = clock();
        insertionSort(vt->vetorTeste, n);
        fim = clock();
        printf("%-10.4f | ", (double)(fim - inicio) / CLOCKS_PER_SEC);

        // --- SELECTION SORT ---
        resetarVetor(vt->vetorTeste, vt->vetorBase, n);
        inicio = clock();
        selectionSort(vt->vetorTeste, n);
        fim = clock();
        printf("%-10.4f | ", (double)(fim - inicio) / CLOCKS_PER_SEC);

        // --- QUICK SORT ---
        resetarVetor(vt->vetorTeste, vt->vetorBase, n);
        inicio = clock();
        quickSort(vt->vetorTeste, 0, n - 1);
        fim = clock();
        printf("%-10.4f | ", (double)(fim - inicio) / CLOCKS_PER_SEC);

        // --- MERGE SORT ---
        resetarVetor(vt->vetorTeste, vt->vetorBase, n);
        inicio = clock();
        mergeSort(vt->vetorTeste, 0, n - 1);
        fim = clock();
        printf("%-10.4f\n", (double)(fim - inicio) / CLOCKS_PER_SEC); 

        destruirVetores(vt);
    }

    return 0;
}