/*
8. Copiar uma Árvore Binária Percorrendo por Nível e Utilizando Fila
📌 Enunciado:
Implemente a função copiarArvorePorNivel(No *raiz), que copia uma árvore binária qualquer (não necessariamente de busca)
percorrendo-a por nível (BFS) utilizando uma fila.

📌 Conceitos envolvidos:

Árvores binárias.
Filas dinâmicas (BFS).
Ponteiros e alocação dinâmica.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int info;
    No* dir;
    No* esq;
} No;

typedef struct {
    No* raiz;
} Arvore;

No* criaNo(int info){
    No* novo = (No*)malloc(sizeof(No));
    novo->info = info;
    novo->dir = NULL;
    novo->esq = NULL;

    return novo;
}

typedef struct Fila{
    int** dados;
    int frente;
    int capacidade;
    int fim;
} Fila;

Fila* criaFila(int capacidade){
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->capacidade = capacidade;
    fila->dados = (int*)malloc(capacidade * sizeof(int));
    fila->fim = -1;
    fila->frente = 0;

    return fila;
}

void enfileirar(Fila* fila, int info){
    if(fila->fim == fila->capacidade - 1){
        return; // fila cheia
    }

    fila->fim++;
    fila->dados[fila->fim] = info;
}

int desenfileirar(Fila* fila){
    return fila->dados[fila->frente++];

    /*
    OU 
    int temp = fila->dados[fila->frente];
    fila->frente++;
    return temp;
    */
}

No* copiarArvorePorNivel(No *raiz){
    Fila *filaOriginal = criarFila(100);
    Fila *filaInvertida = criarFila(100);
    
    enfileirar(filaOriginal, raiz);

    while(filaOriginal->frente != filaOriginal->fim){
        No *atual = desenfileirar(filaOriginal);

        // GUARDA O NÓ NA FILA INVERTIDA
        enfileirar(filaInvertida, atual);

        // GARANTE BFS (esquerda primeiro, depois direita)
        if (atual->esq) enfileirar(filaOriginal, atual->esq);
        if (atual->dir) enfileirar(filaOriginal, atual->dir);
    }

    No *raizCopia = NULL;
    while (filaInvertida->frente != filaInvertida->fim) {
        No *original = desenfileirar(filaInvertida);
        No *novo = criarNo(original->info);

        if (!raizCopia) {
            raizCopia = novo;
        } else {
            // Insere os nós na árvore invertida (pode ser ajustado para diferentes regras)
            No *temp = raizCopia;
            while (temp->esq) temp = temp->esq;
            temp->esq = novo;
        }
    }
}

