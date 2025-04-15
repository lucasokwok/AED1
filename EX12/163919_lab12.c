//Atividade 12 AED1 2024 Prof Luis
//Lucas de Oliveira Kwok 163919

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nVertices;
    int** matriz;
} Grafo;

Grafo* criaGrafo(int n) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->nVertices = n;
    grafo->matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        grafo->matriz[i] = (int*)malloc(n * sizeof(int));
        //inicializa matriz
        for (int j = 0; j < n; j++) {
            grafo->matriz[i][j] = 0;
        }
    }
    return grafo;
}


void adicionaAresta(Grafo* grafo, int u, int v) {
    //nao digrafo
    grafo->matriz[u][v] = 1;
    grafo->matriz[v][u] = 1;
}

void buscaCaminho(Grafo* grafo, int vertice, int* visitado) {
    visitado[vertice] = 1;
    for (int i = 0; i < grafo->nVertices; i++) {
        if (grafo->matriz[vertice][i] == 1 && !visitado[i]) {
            buscaCaminho(grafo, i, visitado);
        }
    }
}

int existeCaminho(Grafo* grafo, int origem, int destino) {
    int* visitado = (int*)malloc(grafo->nVertices * sizeof(int));

    for (int i = 0; i < grafo->nVertices; i++) {
        visitado[i] = 0;
    }

    buscaCaminho(grafo, origem, visitado);
    int resultado = visitado[destino];
    free(visitado);
    return resultado;
}

void calculaGrau(Grafo* grafo, int* grauMin, int* grauMax, int* verticeMin, int* verticeMax) {
    //comeca pelo mais alto possivel
    *grauMin = grafo->nVertices + 1;
    //grau impossivel = -1 pq se grauMin=0 problema
    *grauMax = -1;
    *verticeMin = -1;
    *verticeMax = -1;
    for (int i = 0; i < grafo->nVertices; i++) {
        int grau = 0;
        for (int j = 0; j < grafo->nVertices; j++) {
            if (grafo->matriz[i][j] == 1) {
                grau++;
            }
        }

        if (grau < *grauMin || (*grauMin == grau && i < *verticeMin)) {
            *grauMin = grau;
            *verticeMin = i;
        }
        if (grau > *grauMax || (*grauMax == grau && i < *verticeMax)) {
            *grauMax = grau;
            *verticeMax = i;
        }
    }
}

void liberaGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->nVertices; i++) {
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
    free(grafo);
}

int main() {
    int n, m;

    scanf("%d %d", &n, &m);

    Grafo* grafo = criaGrafo(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adicionaAresta(grafo, u, v);
    }
    int origem, destino;

    scanf("%d %d", &origem, &destino);

    int caminho = existeCaminho(grafo, origem, destino);
    int grauMin, grauMax, verticeMin, verticeMax;

    calculaGrau(grafo, &grauMin, &grauMax, &verticeMin, &verticeMax);
    printf("%d %d %d\n", caminho, verticeMin, verticeMax);

    liberaGrafo(grafo);
    return 0;
}
