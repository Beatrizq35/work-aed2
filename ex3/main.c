#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h> 
#include "pontoordenacao.h"

#define TAMANHO 100000
#define RODADAS 10

// Funções auxiliares para estatística (caso não estejam no seu .h)
double calcularMedia(double tempos[], int n) {
    double soma = 0;
    for (int i = 0; i < n; i++) soma += tempos[i];
    return soma / n;
}

double calcularDesvioPadrao(double tempos[], int n) {
    double media = calcularMedia(tempos, n);
    double somaVariancia = 0;
    for (int i = 0; i < n; i++) {
        somaVariancia += pow(tempos[i] - media, 2);
    }
    return sqrt(somaVariancia / n);
}

int main() {
    // Cria os vetores via TAD
    VetorTeste *vt = criarVetores(TAMANHO);

    clock_t inicio, fim;
    double tempo;
    
    // Arrays para armazenar os tempos de cada rodada para o cálculo do desvio padrão
    double temposBubble[RODADAS];
    double temposInsertion[RODADAS];
    double temposSelection[RODADAS];
    double temposQuick[RODADAS];
    double temposMerge[RODADAS];

    srand(time(NULL));

    for (int r = 0; r < RODADAS; r++) {
        preencherVetorAleatoriamente(vt->vetorBase, TAMANHO);
        printf("\n-------------- Rodada %d --------------\n", r + 1);

        // InsertionSort
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        insertionSort(vt->vetorTeste, TAMANHO);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        temposInsertion[r] = tempo;
        printf("InsertionSort: %f s\n", tempo);

        // BubbleSort
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        BubbleSort(vt->vetorTeste, TAMANHO);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        temposBubble[r] = tempo;
        printf("BubbleSort:    %f s\n", tempo);

        // SelectionSort
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        selectionSort(vt->vetorTeste, TAMANHO);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        temposSelection[r] = tempo;
        printf("SelectionSort: %f s\n", tempo);

        // QuickSort
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        quickSort(vt->vetorTeste, 0, TAMANHO - 1);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        temposQuick[r] = tempo;
        printf("QuickSort:     %f s\n", tempo);

        // MergeSort
        resetarVetor(vt->vetorTeste, vt->vetorBase, TAMANHO);
        inicio = clock();
        mergeSort(vt->vetorTeste, 0, TAMANHO - 1);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        temposMerge[r] = tempo;
        printf("MergeSort:     %f s\n", tempo);
    }

    // --- Relatório Final ---
    printf("\n======================================================\n");
    printf("%-15s | %-15s | %-15s\n", "ALGORITMO", "MEDIA (s)", "DESVIO PADRAO");
    printf("------------------------------------------------------\n");

    printf("%-15s | %-15.6f | %-15.6f\n", "Bubble", 
           calcularMedia(temposBubble, RODADAS), calcularDesvioPadrao(temposBubble, RODADAS));
    
    printf("%-15s | %-15.6f | %-15.6f\n", "Insertion", 
           calcularMedia(temposInsertion, RODADAS), calcularDesvioPadrao(temposInsertion, RODADAS));
    
    printf("%-15s | %-15.6f | %-15.6f\n", "Selection", 
           calcularMedia(temposSelection, RODADAS), calcularDesvioPadrao(temposSelection, RODADAS));
    
    printf("%-15s | %-15.6f | %-15.6f\n", "Quick", 
           calcularMedia(temposQuick, RODADAS), calcularDesvioPadrao(temposQuick, RODADAS));
    
    printf("%-15s | %-15.6f | %-15.6f\n", "Merge", 
           calcularMedia(temposMerge, RODADAS), calcularDesvioPadrao(temposMerge, RODADAS));
    printf("======================================================\n");

    // Libera memória
    destruirVetores(vt);
    return 0;
}