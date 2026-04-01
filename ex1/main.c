#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EX1.h"
#include "EX2.h"

#define TAM       1000000
#define EXECUCOES 30

int main(void) {

    // =========================================================
    // INICIALIZAÇÃO
    // =========================================================
    srand(time(NULL));

    // =========================================================
    // QUESTÃO 1 — Busca Sequencial (vetor) e Busca Binária
    // =========================================================
    printf("\n========== QUESTAO 1 ==========\n");
    printf("Preenchendo vetores... Aguarde.\n");

    Vetor *v_desordenado = criaVetDesordenado(TAM);
    Vetor *v_ordenado    = criaVetOrdenado(TAM);

    double tempos_seq[EXECUCOES];
    double tempos_bin[EXECUCOES];

    printf("Iniciando buscas (30 execucoes para cada algoritmo)...\n\n");

    for (int i = 0; i < EXECUCOES; i++) {
        struct timespec inicio, fim;
        int chave;

        // --- Chave para busca sequencial ---
        if (i < 15) {
            int pos = rand() % TAM;
            chave = acessaElemento(v_desordenado, pos); // garante que existe
        } else {
            chave = rand() % (TAM * 10); // pode não existir
        }

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        buscaSequencial(v_desordenado, chave);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_seq[i] = calculaTempo(inicio, fim);

        printf("[Q1 - Exec %2d] Seq: %.8fs | Chave: %d\n",
               i + 1, tempos_seq[i], chave);

        // --- Chave para busca binária (vetor ordenado) ---
        if (i < 15) {
            int pos = rand() % TAM;
            chave = acessaElemento(v_ordenado, pos);
        } else {
            chave = rand() % (TAM * 10);
        }

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        buscaBinaria(v_ordenado, chave);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_bin[i] = calculaTempo(inicio, fim);

        printf("[Q1 - Exec %2d] Bin: %.8fs | Chave: %d\n",
               i + 1, tempos_bin[i], chave);
    }

    double media_seq  = calculaMedia(tempos_seq, EXECUCOES);
    double desvio_seq = desvioPadrao(tempos_seq, EXECUCOES);
    double media_bin  = calculaMedia(tempos_bin, EXECUCOES);
    double desvio_bin = desvioPadrao(tempos_bin, EXECUCOES);

    printf("\n======== RESULTADOS - QUESTAO 1 ========\n");
    printf("%-20s | %-14s | %-14s\n", "ALGORITMO", "MEDIA (s)", "DESVIO PADRAO");
    printf("----------------------------------------------------\n");
    printf("%-20s | %14.8f | %14.8f\n", "Busca Sequencial", media_seq, desvio_seq);
    printf("%-20s | %14.8f | %14.8f\n", "Busca Binaria",    media_bin, desvio_bin);
    printf("====================================================\n");

    // =========================================================
    // QUESTÃO 2 — Busca Sequencial: Vetor vs Lista Encadeada
    // =========================================================
    printf("\n========== QUESTAO 2 ==========\n");

    // Cria a lista com os MESMOS valores do vetor desordenado
    Lista *lista = criaListaDoVetor(v_desordenado);

    double tempos_seq_vet[EXECUCOES];
    double tempos_seq_lst[EXECUCOES];

    // Gera as 30 chaves antecipadamente para que vetor e lista
    // usem os MESMOS valores em cada execução
    int chaves[EXECUCOES];
    for (int i = 0; i < EXECUCOES; i++) {
        if (i < 15) {
            int pos = rand() % TAM;
            chaves[i] = acessaElemento(v_desordenado, pos); // garante que existe
        } else {
            chaves[i] = rand() % (TAM * 10); // pode não existir
        }
    }

    printf("Iniciando buscas sequenciais (vetor e lista)...\n\n");

    for (int i = 0; i < EXECUCOES; i++) {
        struct timespec inicio, fim;
        int chave = chaves[i];

        // --- Busca Sequencial no VETOR ---
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        buscaSequencial(v_desordenado, chave);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_seq_vet[i] = calculaTempo(inicio, fim);

        // --- Busca Sequencial na LISTA ---
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        buscaSequencialLista(lista, chave);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_seq_lst[i] = calculaTempo(inicio, fim);

        printf("[Q2 - Exec %2d] Vetor: %.8fs | Lista: %.8fs | Chave: %d\n",
               i + 1, tempos_seq_vet[i], tempos_seq_lst[i], chave);
    }

    double media_vet = calculaMedia(tempos_seq_vet, EXECUCOES);
    double media_lst = calculaMedia(tempos_seq_lst, EXECUCOES);

    printf("\n======== RESULTADOS - QUESTAO 2 ========\n");
    printf("%-20s | %-14s\n", "ESTRUTURA", "MEDIA (s)");
    printf("------------------------------------\n");
    printf("%-20s | %14.8f\n", "Busca Seq. Vetor", media_vet);
    printf("%-20s | %14.8f\n", "Busca Seq. Lista", media_lst);
    printf("====================================\n");

    // =========================================================
    // LIBERAÇÃO DE MEMÓRIA
    // =========================================================
    liberaVetor(v_desordenado);
    liberaVetor(v_ordenado);
    liberaLista(lista);

    return 0;
}
