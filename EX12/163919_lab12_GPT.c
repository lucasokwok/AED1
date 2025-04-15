#include <stdio.h>
#include <stdlib.h>

// Estrutura do Grafo com Matriz de Adjacência
typedef struct {
    int n_vert;   // Número de vértices
    int** matriz; // Matriz de adjacência
} Grafo;

// Função para criar um grafo com n vértices
Grafo* criaGrafo(int n) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->n_vert = n;

    // Alocação da matriz de adjacência
    grafo->matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        grafo->matriz[i] = (int*)calloc(n, sizeof(int)); // Inicializa com 0
    }

    return grafo;
}

// Função para adicionar uma aresta no grafo
void adicionaAresta(Grafo* grafo, int u, int v) {
    grafo->matriz[u][v] = 1;
    grafo->matriz[v][u] = 1; // Grafo não direcionado
}

// Função recursiva para busca em profundidade (DFS)
void buscaDFS(Grafo* grafo, int vertice, int* visitado) {
    visitado[vertice] = 1;

    for (int i = 0; i < grafo->n_vert; i++) {
        if (grafo->matriz[vertice][i] == 1 && !visitado[i]) {
            buscaDFS(grafo, i, visitado);
        }
    }
}

// Função para verificar se existe caminho entre dois vértices
int existeCaminho(Grafo* grafo, int origem, int destino) {
    int* visitado = (int*)calloc(grafo->n_vert, sizeof(int));

    buscaDFS(grafo, origem, visitado);
    int resultado = visitado[destino];

    free(visitado);
    return resultado;
}

// Função para calcular o grau mínimo e máximo
void calculaGrau(Grafo* grafo, int* grauMin, int* grauMax, int* verticeMin, int* verticeMax) {
    *grauMin = grafo->n_vert + 1;
    *grauMax = -1;
    *verticeMin = -1;
    *verticeMax = -1;

    for (int i = 0; i < grafo->n_vert; i++) {
        int grau = 0;
        for (int j = 0; j < grafo->n_vert; j++) {
            if (grafo->matriz[i][j] == 1) {
                grau++;
            }
        }

        // Atualiza grau mínimo
        if (grau < *grauMin || (*grauMin == grau && i < *verticeMin)) {
            *grauMin = grau;
            *verticeMin = i;
        }

        // Atualiza grau máximo
        if (grau > *grauMax || (*grauMax == grau && i < *verticeMax)) {
            *grauMax = grau;
            *verticeMax = i;
        }
    }
}

// Função para desalocar memória do grafo
void liberaGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->n_vert; i++) {
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
    free(grafo);
}

// Função principal
int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Grafo* grafo = criaGrafo(n);

    // Leitura das arestas
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adicionaAresta(grafo, u, v);
    }

    // Leitura dos vértices para consulta
    int origem, destino;
    scanf("%d %d", &origem, &destino);

    // Verifica caminho
    int caminho = existeCaminho(grafo, origem, destino);

    // Calcula grau mínimo e máximo
    int grauMin, grauMax, verticeMin, verticeMax;
    calculaGrau(grafo, &grauMin, &grauMax, &verticeMin, &verticeMax);

    // Imprime saída no formato: caminho, depois o vértice de maior grau, depois o de menor grau
    printf("%d %d %d\n", caminho, verticeMax, verticeMin);

    // Libera memória alocada
    liberaGrafo(grafo);

    return 0;
}
