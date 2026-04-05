#include <stdlib.h>  //malloc
#include <stdio.h>
#include <time.h>
#include "pontoordenacao.h"

#define TAMANHO 100000
#define RODADAS 3

int main() {

static int vetorBase[TAMANHO];
static int vetorTeste[TAMANHO];
clock_t inicio, fim;
double tempo;

// soma dos tempos em s dos metodos de ordenaçao
double somaBolha = 0, somaInsertion = 0, somaSelection = 0, somaQuick =0, somaMerge = 0;

srand(time(NULL));

for(int r =1; r<= RODADAS;r++){

// prenche o vetor base com numeros aleatorios em cada rodada 
preencherVetorAleatoriamente(vetorBase, TAMANHO);
printf("\n--------------Rodada %d--------------\n", r);
// teste do insertion
resetarVetor(vetorTeste, vetorBase, TAMANHO);
inicio = clock();
insertionSort(vetorTeste, 100000);
fim = clock();
tempo =((double) (fim-inicio)/ CLOCKS_PER_SEC);
printf("Insertion sort: %f s\n", tempo);
somaInsertion += tempo;

//testando o bolha
resetarVetor(vetorTeste, vetorBase, TAMANHO);
inicio= clock();
BubbleSort(vetorTeste, TAMANHO);
fim = clock();
tempo = ((double) (fim-inicio)/CLOCKS_PER_SEC);
printf("tempo bolha:%f\n", tempo);
somaBolha += tempo;

//testando o selection 
resetarVetor(vetorTeste, vetorBase, TAMANHO);
inicio = clock();
selectionSort(vetorTeste,TAMANHO);
fim = clock();
tempo = ((double) (fim-inicio)/CLOCKS_PER_SEC);
printf("tempo selection:%f\n", tempo);
somaSelection += tempo;

// testatando o quick
resetarVetor(vetorTeste, vetorBase, TAMANHO);
inicio = clock();
quickSort(vetorTeste,0,TAMANHO-1);
fim = clock();
tempo = ((double) (fim-inicio)/CLOCKS_PER_SEC);
printf("tempo quicksort:%f\n", tempo);
somaQuick += tempo;

// testando o mergesort 

resetarVetor(vetorTeste, vetorBase, TAMANHO);
inicio= clock();
mergeSort(vetorTeste,0, TAMANHO-1);
fim = clock();
tempo = ((double) (fim-inicio)/CLOCKS_PER_SEC);
printf("tempo mergesort:%f\n", tempo);
somaMerge += tempo;
}
// calculo das medias 
double mediaBolha = somaBolha / RODADAS;
double mediaInsertion = somaInsertion / RODADAS;
double mediaSelection = somaSelection / RODADAS;    
double mediaQuick = somaQuick / RODADAS;
double mediaMerge = somaMerge / RODADAS;

printf("\n--------------Resultados Medias de Tempo para %d rodadas--------------", RODADAS);

printf("\n\nMedia Bolha: %f s\n", mediaBolha);
printf("Media Insertion: %f s\n", mediaInsertion);
printf("Media Selection: %f s\n", mediaSelection);
printf("Media Quick: %f s\n", mediaQuick);
printf("Media Merge: %f s\n", mediaMerge);



}


