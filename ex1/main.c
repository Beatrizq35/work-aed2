#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EX1.h"
#include "EX2.h"

#define TAM   1000000 
#define EXECUCOES 30

int main(void) {
    srand(time(NULL));

    // =========================================================
    // QUESTÃO 1 — Busca Sequencial e Binária
    // =========================================================
    printf("\n========== QUESTAO 1 ==========\n");

    struct timespec t_q1_inicio, t_q1_fim;
    clock_gettime(CLOCK_MONOTONIC, &t_q1_inicio);

    Vetor *v_desordenado = criaVetDesordenado(TAM);
    Vetor *v_ordenado    = criaVetOrdenado(TAM);

    double tempos_seq[EXECUCOES];
    double tempos_bin[EXECUCOES];
    int chaves_seq[EXECUCOES], chaves_bin[EXECUCOES];

    printf("Executando testes de busca...\n");

    int result_seq[EXECUCOES], result_bin[EXECUCOES];

    for (int i = 0; i < EXECUCOES; i++) {
        struct timespec inicio, fim;

        /*
        ** Primeiras 15 execuções: sorteia posição existente (garante que o valor está no vetor)
        ** Últimas 15 execuções: gera valor aleatório (pode ou não estar no vetor)
        */
        chaves_seq[i] = (i < 15) ? acessaElemento(v_desordenado, rand() % TAM)
                                  : rand() % (TAM * 10);
        chaves_bin[i] = (i < 15) ? acessaElemento(v_ordenado, rand() % TAM)
                                  : rand() % (TAM * 10);

        // Teste Sequencial
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        result_seq[i] = buscaSequencial(v_desordenado, chaves_seq[i]);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_seq[i] = calculaTempo(inicio, fim);

        // Teste Binário
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        result_bin[i] = buscaBinaria(v_ordenado, chaves_bin[i]);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_bin[i] = calculaTempo(inicio, fim);
    }

    // --- Resultados Q1 ---
    printf("\n>>> BUSCA SEQUENCIAL (vetor desordenado):\n");
    printf("%-10s %-15s %-12s %-12s\n", "Execucao", "Tempo (s)", "Chave", "Resultado");
    for (int i = 0; i < EXECUCOES; i++)
        printf("%-10d %-15.8f %-12d %-12s\n",
               i + 1, tempos_seq[i], chaves_seq[i],
               result_seq[i] ? "ENCONTRADO" : "NAO ENCONTRADO");

    printf("\n>>> BUSCA BINARIA (vetor ordenado):\n");
    printf("%-10s %-15s %-12s %-12s\n", "Execucao", "Tempo (s)", "Chave", "Resultado");
    for (int i = 0; i < EXECUCOES; i++)
        printf("%-10d %-15.8f %-12d %-12s\n",
               i + 1, tempos_bin[i], chaves_bin[i],
               result_bin[i] ? "ENCONTRADO" : "NAO ENCONTRADO");

    /* CORRIGIDO: exibe média E desvio padrão conforme enunciado */
    printf("\n--- RESUMO Q1 ---\n");
    printf("Busca Sequencial | Media: %.8fs | Desvio Padrao: %.8fs\n",
           calculaMedia(tempos_seq, EXECUCOES),
           desvioPadrao(tempos_seq, EXECUCOES));
    printf("Busca Binaria    | Media: %.8fs | Desvio Padrao: %.8fs\n",
           calculaMedia(tempos_bin, EXECUCOES),
           desvioPadrao(tempos_bin, EXECUCOES));

    clock_gettime(CLOCK_MONOTONIC, &t_q1_fim);
    printf("Tempo total Q1   : %.6fs\n", calculaTempo(t_q1_inicio, t_q1_fim));

    // =========================================================
    // QUESTÃO 2 — Vetor vs Lista (Busca Sequencial)
    // =========================================================
    printf("\n========== QUESTAO 2 ==========\n");

    struct timespec t_q2_inicio, t_q2_fim;
    clock_gettime(CLOCK_MONOTONIC, &t_q2_inicio);

    Lista *lista = criaListaDoVetor(v_desordenado);

    double tempos_vet[EXECUCOES], tempos_lst[EXECUCOES];
    int chaves_q2[EXECUCOES];

    int result_vet[EXECUCOES], result_lst[EXECUCOES];

    for (int i = 0; i < EXECUCOES; i++) {
        struct timespec inicio, fim;

        /* Mesmo mecanismo da Q1: 15 encontrados + 15 aleatórios */
        chaves_q2[i] = (i < 15) ? acessaElemento(v_desordenado, rand() % TAM)
                                 : rand() % (TAM * 10);

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        result_vet[i] = buscaSequencial(v_desordenado, chaves_q2[i]);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_vet[i] = calculaTempo(inicio, fim);

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        result_lst[i] = buscaSequencialLista(lista, chaves_q2[i]);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_lst[i] = calculaTempo(inicio, fim);
    }

    // --- Resultados Q2 ---
    printf("\n>>> COMPARATIVO BUSCA SEQUENCIAL (Vetor vs Lista):\n");
    printf("%-10s %-15s %-15s %-12s %-16s %-16s\n",
           "Execucao", "Vetor (s)", "Lista (s)", "Chave",
           "Res. Vetor", "Res. Lista");
    for (int i = 0; i < EXECUCOES; i++)
        printf("%-10d %-15.8f %-15.8f %-12d %-16s %-16s\n",
               i + 1, tempos_vet[i], tempos_lst[i], chaves_q2[i],
               result_vet[i] ? "ENCONTRADO" : "NAO ENCONTRADO",
               result_lst[i] ? "ENCONTRADO" : "NAO ENCONTRADO");

    /* CORRIGIDO: exibe média de cada estrutura conforme enunciado */
    printf("\n--- RESUMO Q2 ---\n");
    printf("Vetor | Media: %.8fs\n", calculaMedia(tempos_vet, EXECUCOES));
    printf("Lista | Media: %.8fs\n", calculaMedia(tempos_lst, EXECUCOES));

    clock_gettime(CLOCK_MONOTONIC, &t_q2_fim);
    printf("Tempo total Q2   : %.6fs\n", calculaTempo(t_q2_inicio, t_q2_fim));

    liberaVetor(v_desordenado);
    liberaVetor(v_ordenado);
    liberaLista(lista);

    return 0;
}