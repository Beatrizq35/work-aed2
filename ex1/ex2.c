/*
** TAD: Lista Encadeada de inteiros
** Implementa criação, busca sequencial e liberação de memória
*/

#include <stdio.h>
#include <stdlib.h>
#include "EX1.h"
#include "EX2.h"

/*---------------------------*/
/* Estruturas internas       */
/*---------------------------*/
typedef struct no {
    int valor;
    struct no *prox;
} No;

struct lista {
    No  *cabeca;
    int  tamanho;
};

/* Funcao criaLista
** Aloca e retorna uma lista encadeada vazia
*/
Lista* criaLista(void) {
    Lista *l = (Lista*) malloc(sizeof(Lista));
    if (l == NULL) {
        printf("Erro ao alocar estrutura Lista!\n");
        exit(1);
    }
    l->cabeca   = NULL;
    l->tamanho  = 0;
    return l;
}

/* Funcao liberaLista
** Libera toda a memória alocada pela lista (nós + estrutura)
*/
void liberaLista(Lista *l) {
    No *atual = l->cabeca;
    while (atual != NULL) {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(l);
}

/* Funcao criaListaDoVetor
** Aloca e retorna uma lista encadeada com os mesmos valores do Vetor recebido.
** Os elementos são inseridos na cabeça para manter O(1) por inserção,
** o que preserva a mesma dificuldade média de busca sequencial.
*/
Lista* criaListaDoVetor(Vetor *v) {
    Lista *l = criaLista();
    int tam  = tamanhoVetor(v);

    for (int i = 0; i < tam; i++) {
        No *novo = (No*) malloc(sizeof(No));
        if (novo == NULL) {
            printf("Erro ao alocar nó da lista!\n");
            exit(1);
        }
        novo->valor = acessaElemento(v, i);
        novo->prox  = l->cabeca;
        l->cabeca   = novo;
        l->tamanho++;
    }
    return l;
}

/* Funcao buscaSequencialLista
** Percorre a lista linearmente comparando cada nó com a chave
** Retorna 1 se encontrado, 0 se não encontrado
*/
int buscaSequencialLista(Lista *l, int key) {
    No *atual = l->cabeca;
    while (atual != NULL) {
        if (atual->valor == key)
            return 1;
        atual = atual->prox;
    }
    return 0;
}