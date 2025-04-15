#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int frente, tras, capacidade;
    int *dados;
} Fila;

Fila* criarFila(int capacidade) {
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->capacidade = capacidade;
    f->frente = 0;
    f->tras = -1;
    f->dados = (int*)malloc(capacidade * sizeof(int));
    return f;
}

void enfileirar(Fila *f, int valor) {
    if (f->tras == f->capacidade - 1) {
        printf("Fila cheia!\n");
        return;
    }
    f->dados[++f->tras] = valor;
}

int desenfileirar(Fila *f) {
    if (estaVazia(f)) {
        printf("Fila vazia!\n");
        return -1;
    }
    return f->dados[f->frente++];
}

void destruirFila(Fila *f) {
    free(f->dados);
    free(f);
}

int estaVazia(Fila *f) {
    return f->frente > f->tras;
}

int frente(Fila *f) {
    if (estaVazia(f)) return -1;
    return f->dados[f->frente];
}



