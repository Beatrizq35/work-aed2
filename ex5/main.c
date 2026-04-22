#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EX5.h"
#include "EX5.2.h"

#define TAMANHOS_COUNT 10
static const int TAMANHOS[] = {
    100000, 200000, 300000, 400000, 500000,
    600000, 700000, 800000, 900000, 1000000
};

int main(void) {
    srand(time(NULL));

    // =========================================================
    // QUESTÃO 1 — Busca Sequencial vs Busca Binária
    // =========================================================
    printf("\n========== QUESTAO 1 ==========\n");
    printf("%-12s %-18s %-14s %-18s %-14s\n",
           "Tamanho", "Tempo Seq (s)", "Res. Seq", "Tempo Bin (s)", "Res. Bin");

    double tempos_seq[TAMANHOS_COUNT];
    double tempos_bin[TAMANHOS_COUNT];

    for (int t = 0; t < TAMANHOS_COUNT; t++) {
        int tam = TAMANHOS[t];

        Vetor *v_des = criaVetDesordenado(tam);
        Vetor *v_ord = criaVetOrdenado(tam);

        int chave_seq = rand() % (tam * 10);
        int chave_bin = rand() % (tam * 10);

        struct timespec inicio, fim;
        int result_seq, result_bin;

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        result_seq = buscaSequencial(v_des, chave_seq);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_seq[t] = calculaTempo(inicio, fim);

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        result_bin = buscaBinaria(v_ord, chave_bin);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_bin[t] = calculaTempo(inicio, fim);

        printf("%-12d %-18.8f %-14s %-18.8f %-14s\n",
               tam,
               tempos_seq[t], result_seq ? "ENCONTRADO" : "NAO ENCONTRADO",
               tempos_bin[t], result_bin ? "ENCONTRADO" : "NAO ENCONTRADO");

        liberaVetor(v_des);
        liberaVetor(v_ord);
    }

    printf("\n%-12s %-24s %-24s\n",
           "Tamanho", "Tempo/Elem Seq (ns)", "Tempo/Elem Bin (ns)");
    for (int t = 0; t < TAMANHOS_COUNT; t++) {
        printf("%-12d %-24.4f %-24.4f\n",
               TAMANHOS[t],
               (tempos_seq[t] / TAMANHOS[t]) * 1e9,
               (tempos_bin[t] / TAMANHOS[t]) * 1e9);
    }

    // =========================================================
    // QUESTÃO 2 — Busca Sequencial: Vetor vs Lista
    // =========================================================
    printf("\n========== QUESTAO 2 ==========\n");
    printf("%-12s %-18s %-14s %-18s %-14s\n",
           "Tamanho", "Vetor (s)", "Res. Vetor", "Lista (s)", "Res. Lista");

    double tempos_vet[TAMANHOS_COUNT];
    double tempos_lst[TAMANHOS_COUNT];

    for (int t = 0; t < TAMANHOS_COUNT; t++) {
        int tam = TAMANHOS[t];

        Vetor *v = criaVetDesordenado(tam);
        Lista *l = criaListaDoVetor(v);

        int chave = rand() % (tam * 10);

        struct timespec inicio, fim;
        int result_vet, result_lst;

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        result_vet = buscaSequencial(v, chave);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_vet[t] = calculaTempo(inicio, fim);

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        result_lst = buscaSequencialLista(l, chave);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_lst[t] = calculaTempo(inicio, fim);

        printf("%-12d %-18.8f %-14s %-18.8f %-14s\n",
               tam,
               tempos_vet[t], result_vet ? "ENCONTRADO" : "NAO ENCONTRADO",
               tempos_lst[t], result_lst ? "ENCONTRADO" : "NAO ENCONTRADO");

        liberaVetor(v);
        liberaLista(l);
    }

    printf("\n%-12s %-24s %-24s\n",
           "Tamanho", "Tempo/Elem Vet (ns)", "Tempo/Elem Lst (ns)");
    for (int t = 0; t < TAMANHOS_COUNT; t++) {
        printf("%-12d %-24.4f %-24.4f\n",
               TAMANHOS[t],
               (tempos_vet[t] / TAMANHOS[t]) * 1e9,
               (tempos_lst[t] / TAMANHOS[t]) * 1e9);
    }

    return 0;
}