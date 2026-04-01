/*
** TAD: Lista Encadeada de inteiros
** Implementa criação a partir de vetor e busca sequencial
*/

#include <stdio.h>
#include <stdlib.h>
#include "EX2.h"

/*---------------------------*/
/* Estruturas internas       */
/*---------------------------*/
typedef struct no {
    int dado;
    struct no *proximo;
} No;

struct lista {
    No  *cabeca;
    int  tamanho;
};

/* Funcao auxiliar (interna): insereNaLista
** Insere um valor no final da lista encadeada
*/
static void insereNaLista(Lista *l, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar nó da lista!\n");
        exit(1);
    }

    novo->dado    = valor;
    novo->proximo = NULL;

    if (l->cabeca == NULL) {
        l->cabeca = novo;
    } else {
        No *atual = l->cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    l->tamanho++;
}

/* Funcao criaLista
** Aloca e retorna uma lista encadeada vazia
*/
Lista* criaLista(void) {
    Lista *l = (Lista*) malloc(sizeof(Lista));
    if (l == NULL) {
        printf("Erro ao alocar lista!\n");
        exit(1);
    }
    l->cabeca  = NULL;
    l->tamanho = 0;
    return l;
}

/* Funcao liberaLista
** Percorre e libera todos os nós, depois libera a estrutura lista
*/
void liberaLista(Lista *l) {
    No *atual = l->cabeca;
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(l);
}

/* Funcao criaListaDoVetor
** Aloca e retorna uma lista com os mesmos valores do Vetor (TAD do EX1)
*/
Lista* criaListaDoVetor(Vetor *v) {
    Lista *l = criaLista();
    int tam = tamanhoVetor(v);

    printf("Criando lista com %d elementos...\n", tam);
    // Percorre do último para o primeiro
    for (int i = tam - 1; i >= 0; i--) {
        insereNaLista(l, acessaElemento(v, i)); 
    }
    return l;
}

/* Funcao buscaSequencialLista
** Percorre a lista nó a nó comparando o dado com a chave
** Retorna 1 se encontrado, 0 se não encontrado
*/
int buscaSequencialLista(Lista *l, int key) {
    No *atual = l->cabeca;
    while (atual != NULL) {
        if (atual->dado == key) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}
