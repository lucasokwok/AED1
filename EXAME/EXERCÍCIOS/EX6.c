/*
🔹 Exercício 6: Ponteiros, Árvore e Pilha
📌 Enunciado:
Implemente a função caminhoEntreNos(No *raiz, int v1, int v2), que recebe a raiz de uma árvore binária de busca (ABB)
 e dois valores. A função deve encontrar e retornar uma pilha dinâmica contendo o caminho do nó v1 até o nó v2.

📌 Conceitos envolvidos:

Ponteiros e recursão
Pilha dinâmica
Árvore binária de busca (ABB)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;

}No ;

typedef struct Arvore{
    No* raiz;
} Arvore;

