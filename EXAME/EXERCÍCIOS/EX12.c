/*
🔹 12. Converter uma Árvore Binária para Lista Duplamente Encadeada
📌 Enunciado:
Implemente a função arvoreParaLista(No *raiz), que transforma uma árvore binária em uma lista duplamente encadeada percorrendo a árvore em ordem (in-order traversal).

📌 Conceitos envolvidos:

Árvores binárias.
Listas duplamente encadeadas.
Ponteiros e manipulação de memória.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct NoArvore{
    int info;
    NoArvore* dir;
    NoArvore* esq;
} NoArvore;

typedef struct{
    NoArvore* raiz;
} Arvore;

typedef struct NoLista{
    int info;
    NoLista* prox;
    NoLista* ant;
} NoLista;

typedef struct Lista{
    NoLista* cabeça;
} Lista;

Lista* converteABemLista(Arvore* arvore){
    Lista* lista = (Lista*) malloc(sizeof(Lista));

    NoLista* novoNo = (NoLista*) malloc (sizeof(NoLista));
    novoNo->info = arvore->raiz->info;
    novoNo->prox = NULL;
    novoNo->ant = NULL;
    lista->cabeça = novoNo;

    emOrdem(arvore, lista);
}

void inserirNoLista(NoArvore* raiz, Lista* lista){
    NoLista* novoNo = (NoLista*) malloc (sizeof(NoLista));
    novoNo->info = raiz->info;
    novoNo->prox = NULL;

    NoLista* cabeca = lista->cabeça;
    while (cabeca->prox != NULL)
    {
        cabeca = cabeca->prox;
    }
    
    novoNo->ant = cabeca;
    cabeca->prox = novoNo;
}

void emOrdem(NoArvore* raiz, Lista* lista){
    if (raiz == NULL) return;
    emOrdem(raiz->esq, lista);
    inserirNoLista(raiz, lista);
    emOrdem(raiz->dir, lista);
}

