#ifndef EX5_3_H
#define EX5_3_H

/*
** TAD: Ordenacao de vetores de inteiros
** Algoritmos: Bolha, Insercao Direta, Selecao Direta, Quicksort, Merge Sort
*/

/* Tipo opaco para vetor ordenável */
typedef struct vetorOrd VetorOrd;

/* Criacao e liberacao */
VetorOrd* criaVetorOrd(int tam);
VetorOrd* copiaVetorOrd(VetorOrd *v);
void      liberaVetorOrd(VetorOrd *v);
int       tamanhoVetorOrd(VetorOrd *v);

/* Algoritmos de ordenacao */
void ordenaBolha(VetorOrd *v);
void ordenaInsercao(VetorOrd *v);
void ordenaSelecao(VetorOrd *v);
void ordenaQuicksort(VetorOrd *v);
void ordenaMergeSort(VetorOrd *v);

#endif /* EX5_3_H */
