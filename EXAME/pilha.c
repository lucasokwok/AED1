#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int topo;
    int capacidade;
    int *dados;
} Pilha;

Pilha* criarPilha(int capacidade) {
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->capacidade = capacidade;
    p->topo = -1;
    p->dados = (int*)malloc(capacidade * sizeof(int));
    return p;
}

void empilhar(Pilha *p, int valor) {
    if (p->topo == p->capacidade - 1) {
        printf("Pilha cheia!\n");
        return;
    }
    p->dados[++p->topo] = valor;
}

int desempilhar(Pilha *p) {
    if (estaVazia(p)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    return p->dados[p->topo--];
}

void destruirPilha(Pilha *p) {
    free(p->dados);
    free(p);
}

int estaVazia(Pilha *p) {
    return p->topo == -1;
}

int topo(Pilha *p) {
    if (estaVazia(p)) return -1;
    return p->dados[p->topo];
}

int estaVazia(Pilha *p) {
    return p->topo == -1;
}

void destruirPilha(Pilha *p) {
    free(p->dados);
    free(p);
}
