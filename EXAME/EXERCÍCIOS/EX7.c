/*

🔹 Exercício 7: Grafo e Busca em Profundidade (DFS)
📌 Enunciado:
Implemente a função DFS(Grafo *g, int v), que recebe um grafo representado por lista de adjacência e um vértice de início v.
A função deve realizar uma busca em profundidade (DFS) e veriricar se existe caminho entre eles.

📌 Conceitos envolvidos:

Ponteiros e recursão
Grafos (lista de adjacência)
Pilha para DFS
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int vertice;
    No* prox;
}No;

typedef struct Grafo{
    No** lista_adj;
    int nVertices;
} Grafo;

Grafo* criaGrafo(int n){
    Grafo* grafo = (Grafo*) malloc (sizeof(Grafo));
    grafo->nVertices = n;
    grafo->lista_adj = (No**) malloc (n * sizeof(Grafo*));

    for (int i = 0; i < n; i++)
    grafo->lista_adj[i] = NULL;

    return grafo;
}

No* criaNo(int n){
    No* novo = (No*) malloc (sizeof(No));
    novo->vertice = n;
    novo->prox = NULL;
}

void adicionaAresta(Grafo* grafo, int origem, int destino){
    No* novo = (No*) malloc (sizeof(No));
    novo->vertice = destino;
    novo->prox = grafo->lista_adj[origem];
    grafo->lista_adj[origem] = novo;

    No* novo2 = (No*) malloc (sizeof(No));
    novo2->vertice = origem;
    novo2->prox = grafo->lista_adj[destino];
    grafo->lista_adj[destino] = novo2;
}

int DFSAux(Grafo *g, int v, int destino, int* visitado){
    if (v == destino) return 1;
    visitado[v] = 1;
    No* temp = g->lista_adj[v];

    while (temp != NULL)
    {
        if (visitado[temp->vertice] == 0){
            if(DFSAux(g, temp->vertice, destino, visitado)){
                return 1;
            }
            temp = temp->prox;
        }
    }

    return 0;
}

int DFS (Grafo* g, int origem, int destino){
    int *visitado = (int*)malloc(g->nVertices * sizeof(int));

    for(int i = 0; i < g->nVertices; i++){
        visitado[i] = 0;
    }

    int resultado = DFSAux(g, origem, destino, visitado);

    free(visitado);

    return resultado;
}