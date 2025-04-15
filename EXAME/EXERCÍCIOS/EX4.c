/*
🔹 Exercício 4: Grafo (Matriz de Adjacência) e Arquivo
📌 Enunciado:
Implemente a função carregarGrafo(FILE *arquivo, int *n), que lê um arquivo BINARIO contendo a matriz de adjacência 
de um grafo e armazena-a em uma matriz alocada dinamicamente. Retorne a matriz e armazene o número de vértices em *n.

📌 Conceitos envolvidos:

Grafos (matriz de adjacência)
Alocação dinâmica (malloc())
Manipulação de arquivos (fopen(), fscanf(), fclose())
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo{
    int** matriz_adj;
    int nVerticies;
} Grafo;

Grafo* criaGrafo(int n){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->nVerticies;
    grafo->matriz_adj = (int**)malloc(n * sizeof(int*));

    for(int i = 0; i < n; i++){
        grafo->matriz_adj[i] = (int*)malloc(n*sizeof(int));

        for(int j = 0; j < n; j++){
            grafo->matriz_adj[i][j] = 0;
        }
    }
}

int** carregarGrafo(char *nomeArquivo, int n){
    FILE* arquivo = fopen(nomeArquivo, "rb");
    Grafo* grafo = criaGrafo(n);
    for (int i = 0; i < n; i++) {
        fread(grafo->matriz_adj[i], sizeof(int), n, arquivo); 
    }

    fclose(arquivo);
    return grafo->matriz_adj;
}