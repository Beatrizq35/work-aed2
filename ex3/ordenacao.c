#include <stdlib.h> // malloc, free, exit
#include <string.h> // printf
#include <time.h>
#include <string.h> //para usar o memcpy para copiar o vetor base pro de teste
#include "pontoordenacao.h"
//Ao usar o ponteiro *v, você está passando apenas o endereço de memória onde o vetor começa. É muito mais rápido e econômico.

void insertionSort(int *v, int tamanho){
    int i, Pivot, j;

    for(i=1;i<tamanho;i++){
        Pivot =v[i];
        j=i-1;
        while(j>=0 && v[j]>Pivot){
            v[j+1] = v[j];
            j=j-1;
        }
        v[j+1] = Pivot;
    }
}

void selectionSort(int *v, int tamanhoVetor){
unsigned penultimo = tamanhoVetor-1;
int tmp;
unsigned i, cont;
unsigned posMenor;

for(i=0;i<penultimo;i++) {
    posMenor = i;
    for(cont =i+1; cont < tamanhoVetor;cont++) {
     if(v[cont]< v[posMenor]){
        posMenor = cont;
     }
}
    tmp = v[i];
    v[i]= v[posMenor];
    v[posMenor] = tmp;
}
}

void quickSort(int *v, int inicio, int fim){
 int i,j;
 int Pivot;
 int tmp;

 if(inicio < fim){
    Pivot = v[(inicio+fim)/2];
    i= inicio;
    j=fim;
 while(i<=j){
    while(v[i]< Pivot) i++;
    while(v[j]>Pivot) j--;
        if(i<=j){
            tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
            i++;
            j--; 
        }
}
    quickSort(v,inicio,j);
    quickSort(v,i, fim);
    }
}

//void BubbleSort(int *v, int tamanho){
//int i,j,tmp;

//for(i=0;i<tamanho-1;i++){

//for(j=0 ; j< tamanho-i-1; j++){    
 //if(v[i] > v[i+1]){
//tmp = v[i];
//v[i] = v[i+1];
//v[i+1] = tmp;
//     }
//    }
//}
//}
void BubbleSort(int *v, int tamanho) {
    int i, j, tmp;
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) { // O loop interno usa j
            if (v[j] > v[j + 1]) {              // Compara v[j] com o próximo
                tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
}

void mergeSort(int *v, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        // Chamadas recursivas
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);

        // --- Início da Intercalação ---
        int tam = fim - inicio + 1;
        int *vaux = (int *) malloc(tam * sizeof(int)); // Alocação local
        
        int a = inicio;      // Início da 1ª metade
        int b = meio + 1;    // Início da 2ª metade
        int s = 0;           // Índice do vaux (começa em 0 aqui)

        while (a <= meio && b <= fim) {
            if (v[a] < v[b]) {
                vaux[s++] = v[a++];
            } else {
                vaux[s++] = v[b++];
            }
        }

        while (a <= meio) vaux[s++] = v[a++];
        while (b <= fim) vaux[s++] = v[b++];

        // Copia de volta para o vetor original v
        for (int i = 0; i < tam; i++) {
            v[inicio + i] = vaux[i];
        }

        free(vaux); // Libera a memória alocada nesta etapa
    }
}

void preencherVetorAleatoriamente(int *v, unsigned tamanho)
{unsigned cont;
//srand(time(NULL));  botei no main para não ficar repetindo a semente a cada chamada da função, o que fazia com que os vetores fossem preenchidos com os mesmos números em cada rodada
for(cont=0; cont < tamanho; cont++ ){
    v[cont] = rand() %10000000;
}
}

void resetarVetor(int *destino, int *origem, int tamanho){
memcpy(destino, origem, tamanho*sizeof(int));
}



