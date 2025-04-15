#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *prox;
    struct No *ant;
} No;

typedef struct {
    No *inicio;
} ListaDupla;

ListaDupla* criarListaDupla() {
    ListaDupla *lista = (ListaDupla*)malloc(sizeof(ListaDupla));
    lista->inicio = NULL;
    return lista;
}

void inserirNoInicio(ListaDupla *lista, int valor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->prox = lista->inicio;
    novoNo->ant = NULL;

    if (lista->inicio != NULL)
        lista->inicio->ant = novoNo;

    lista->inicio = novoNo;
}

void inserirNoFim(ListaDupla *lista, int valor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->prox = NULL;

    if (lista->inicio == NULL) {
        novoNo->ant = NULL;
        lista->inicio = novoNo;
        return;
    }

    No *temp = lista->inicio;
    while (temp->prox != NULL) {
        temp = temp->prox;
    }
    temp->prox = novoNo;
    novoNo->ant = temp;
}

void imprimirListaDupla(ListaDupla *lista) {
    No *temp = lista->inicio;
    while (temp != NULL) {
        printf("%d <-> ", temp->dado);
        temp = temp->prox;
    }
    printf("NULL\n");
}

void imprimirListaDuplaReversa(ListaDupla *lista) {
    if (lista->inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No *temp = lista->inicio;
    while (temp->prox != NULL) {
        temp = temp->prox;
    }

    while (temp != NULL) {
        printf("%d <-> ", temp->dado);
        temp = temp->ant;
    }
    printf("NULL\n");
}

void removerElemento(ListaDupla *lista, int valor) {
    No *temp = lista->inicio;

    while (temp != NULL && temp->dado != valor) {
        temp = temp->prox;
    }

    if (temp == NULL) return;

    if (temp->ant != NULL)
        temp->ant->prox = temp->prox;
    else
        lista->inicio = temp->prox;

    if (temp->prox != NULL)
        temp->prox->ant = temp->ant;

    free(temp);
}

void destruirListaDupla(ListaDupla *lista) {
    No *temp = lista->inicio;
    while (temp != NULL) {
        No *prox = temp->prox;
        free(temp);
        temp = prox;
    }
    free(lista);
}
