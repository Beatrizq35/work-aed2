#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EX1.h"
#include "EX2.h"

#define TAM       1000000
#define EXECUCOES 30

int main(void) {
    srand(time(NULL));

    // =========================================================
    // QUESTÃO 1 — Busca Sequencial e Binária
    // =========================================================
    printf("\n========== QUESTAO 1 ==========\n");
    Vetor *v_desordenado = criaVetDesordenado(TAM);
    Vetor *v_ordenado    = criaVetOrdenado(TAM);

    double tempos_seq[EXECUCOES];
    double tempos_bin[EXECUCOES];
    int chaves_seq[EXECUCOES], chaves_bin[EXECUCOES];

    printf("Executando testes de busca...\n");

    for (int i = 0; i < EXECUCOES; i++) {
        struct timespec inicio, fim;
        
        // Setup chaves
        chaves_seq[i] = (i < 15) ? acessaElemento(v_desordenado, rand() % TAM) : rand() % (TAM * 10);
        chaves_bin[i] = (i < 15) ? acessaElemento(v_ordenado, rand() % TAM) : rand() % (TAM * 10);

        // Teste Sequencial
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        buscaSequencial(v_desordenado, chaves_seq[i]);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_seq[i] = calculaTempo(inicio, fim);

        // Teste Binário
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        buscaBinaria(v_ordenado, chaves_bin[i]);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_bin[i] = calculaTempo(inicio, fim);
    }

    // PRINT ORGANIZADO Q1
    printf("\n>>> RESULTADOS BUSCA BINARIA (ORDENADO):\n");
    for(int i=0; i<EXECUCOES; i++) 
        printf("[Exec %2d] Bin: %.8fs | Chave: %d\n", i+1, tempos_bin[i], chaves_bin[i]);

    printf("\n>>> RESULTADOS BUSCA SEQUENCIAL (DESORDENADO):\n");
    for(int i=0; i<EXECUCOES; i++) 
        printf("[Exec %2d] Seq: %.8fs | Chave: %d\n", i+1, tempos_seq[i], chaves_seq[i]);

    // Médias Q1
    printf("\nRESUMO Q1:\nSeq Media: %.8fs | Bin Media: %.8fs\n", 
           calculaMedia(tempos_seq, EXECUCOES), calculaMedia(tempos_bin, EXECUCOES));

    // =========================================================
    // QUESTÃO 2 — Vetor vs Lista (Busca Sequencial)
    // =========================================================
    printf("\n========== QUESTAO 2 ==========\n");
    // Agora será instantâneo com a correção no ex2.c
    Lista *lista = criaListaDoVetor(v_desordenado);

    double tempos_vet[EXECUCOES], tempos_lst[EXECUCOES];
    int chaves_q2[EXECUCOES];

    for (int i = 0; i < EXECUCOES; i++) {
        struct timespec inicio, fim;
        chaves_q2[i] = (i < 15) ? acessaElemento(v_desordenado, rand() % TAM) : rand() % (TAM * 10);

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        buscaSequencial(v_desordenado, chaves_q2[i]);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_vet[i] = calculaTempo(inicio, fim);

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        buscaSequencialLista(lista, chaves_q2[i]);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_lst[i] = calculaTempo(inicio, fim);
    }

    printf("\n>>> COMPARATIVO FINAL (VETOR vs LISTA):\n");
    for(int i=0; i<EXECUCOES; i++)
        printf("[Exec %2d] Vetor: %.8fs | Lista: %.8fs\n", i+1, tempos_vet[i], tempos_lst[i]);

    liberaVetor(v_desordenado);
    liberaVetor(v_ordenado);
    liberaLista(lista);

    return 0;
}
