#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
} ListaCircular;

ListaCircular* criarListaCircular() {
    ListaCircular *lista = (ListaCircular*)malloc(sizeof(ListaCircular));
    lista->inicio = NULL;
    return lista;
}

void inserirNoInicio(ListaCircular *lista, int valor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;

    if (lista->inicio == NULL) {
        novoNo->prox = novoNo; // Aponta para si mesmo
        lista->inicio = novoNo;
    } else {
        No *temp = lista->inicio;
        while (temp->prox != lista->inicio) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
    }
}

void inserirNoFim(ListaCircular *lista, int valor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;

    if (lista->inicio == NULL) {
        novoNo->prox = novoNo;
        lista->inicio = novoNo;
    } else {
        No *temp = lista->inicio;
        while (temp->prox != lista->inicio) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
        novoNo->prox = lista->inicio;
    }
}

void imprimirListaCircular(ListaCircular *lista) {
    if (lista->inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    No *temp = lista->inicio;
    do {
        printf("%d -> ", temp->dado);
        temp = temp->prox;
    } while (temp != lista->inicio);
    printf("(volta ao início)\n");
}

void destruirListaCircular(ListaCircular *lista) {
    if (lista->inicio == NULL) {
        free(lista);
        return;
    }

    No *temp = lista->inicio;
    No *proxNo;
    do {
        proxNo = temp->prox;
        free(temp);
        temp = proxNo;
    } while (temp != lista->inicio);

    free(lista);
}
