/*
🔹 Exercício 5: Recursão e Lista Encadeada
📌 Enunciado:
Implemente a função recursiva removerPares(Lista *l), que recebe a cabeça de uma lista encadeada e 
remove todos os números pares, retornando a nova lista.

📌 Conceitos envolvidos:

Ponteiros e recursão
Lista encadeada
Liberação de memória (free())
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int dado;
    No* prox;
} No;

No* removerPares(No *l) {
    if (!l) return NULL;
    if (l->dado % 2 == 0) {
        No *prox = l->prox;
        free(l);
        return removerPares(prox);
    }
    l->prox = removerPares(l->prox);
    return l;
}
