#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
} ListaEncadeada;

ListaEncadeada* criarLista() {
    ListaEncadeada *lista = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
    lista->inicio = NULL;
    return lista;
}

void inserirNoInicio(ListaEncadeada *lista, int valor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->prox = lista->inicio;
    lista->inicio = novoNo;
}

void inserirNoFim(ListaEncadeada *lista, int valor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novoNo;
        return;
    }

    No *temp = lista->inicio;
    while (temp->prox != NULL) {
        temp = temp->prox;
    }
    temp->prox = novoNo;
}

void removerElemento(ListaEncadeada *lista, int valor) {
    No *temp = lista->inicio, *anterior = NULL;

    while (temp != NULL && temp->dado != valor) {
        anterior = temp;
        temp = temp->prox;
    }

    if (temp == NULL) return;

    if (anterior == NULL)
        lista->inicio = temp->prox;
    else
        anterior->prox = temp->prox;

    free(temp);
}

void imprimirLista(ListaEncadeada *lista) {
    No *temp = lista->inicio;
    while (temp != NULL) {
        printf("%d -> ", temp->dado);
        temp = temp->prox;
    }
    printf("NULL\n");
}

void destruirLista(ListaEncadeada *lista) {
    No *temp = lista->inicio;
    while (temp != NULL) {
        No *prox = temp->prox;
        free(temp);
        temp = prox;
    }
    free(lista);
}
