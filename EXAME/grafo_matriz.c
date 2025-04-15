#include <stdio.h>
#include <stdlib.h>

/* Estrutura do Grafo */
typedef struct {
    int numVertices;
    int **matrizAdj;
} Grafo;

/* Cria um novo grafo com Matriz de Adjacência */
Grafo* criarGrafoMatriz(int numVertices) {
    Grafo *G = (Grafo*) malloc(sizeof(Grafo));
    G->numVertices = numVertices;

    // Alocação dinâmica da matriz de adjacência
    G->matrizAdj = (int**) malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        G->matrizAdj[i] = (int*) calloc(numVertices, sizeof(int)); // Inicializa com 0 (sem arestas)
    }

    return G;
}

/* Adiciona uma aresta ao grafo */
void adicionarArestaMatriz(Grafo *G, int origem, int destino) {
    G->matrizAdj[origem][destino] = 1;
    G->matrizAdj[destino][origem] = 1; // Grafo não direcionado
}

/* Função auxiliar para busca em profundidade (DFS) */
int DFSUtil(Grafo *G, int atual, int destino, int *visitado) {
    if (atual == destino) return 1; // Se encontrou o destino, há caminho

    visitado[atual] = 1; // Marca o nó como visitado

    for (int i = 0; i < G->numVertices; i++) {
        if (G->matrizAdj[atual][i] && !visitado[i]) { // Se há aresta e não foi visitado
            if (DFSUtil(G, i, destino, visitado)) 
                return 1; // Se encontrou o destino, retorna verdadeiro
        }
    }

    return 0; // Se terminou a busca e não encontrou, não há caminho
}

/* Função para verificar se há caminho entre dois vértices */
int existeCaminhoDFS(Grafo *G, int origem, int destino) {
    int *visitado = (int*) calloc(G->numVertices, sizeof(int)); // Inicializa vetor de visitados

    int resultado = DFSUtil(G, origem, destino, visitado); // Chama DFS

    free(visitado); // Libera memória alocada para o vetor de visitados
    return resultado;
}

/* Imprime a matriz de adjacência do grafo */
void imprimirGrafoMatriz(Grafo *G) {
    printf("Matriz de Adjacência:\n");
    for (int i = 0; i < G->numVertices; i++) {
        for (int j = 0; j < G->numVertices; j++) {
            printf("%d ", G->matrizAdj[i][j]);
        }
        printf("\n");
    }
}

/* Libera a memória do grafo */
void liberarGrafoMatriz(Grafo *G) {
    for (int i = 0; i < G->numVertices; i++) {
        free(G->matrizAdj[i]);
    }
    free(G->matrizAdj);
    free(G);
}

/* Exemplo de uso */
int main() {
    Grafo *G = criarGrafoMatriz(6);
    adicionarArestaMatriz(G, 0, 1);
    adicionarArestaMatriz(G, 1, 2);
    adicionarArestaMatriz(G, 2, 3);
    adicionarArestaMatriz(G, 3, 4);
    adicionarArestaMatriz(G, 4, 0);

    imprimirGrafoMatriz(G);

    // Testando caminhos
    printf("\nVerificando caminhos:\n");
    printf("Existe caminho entre 0 e 3? %s\n", existeCaminhoDFS(G, 0, 3) ? "Sim" : "Não");
    printf("Existe caminho entre 1 e 5? %s\n", existeCaminhoDFS(G, 1, 5) ? "Sim" : "Não");
    printf("Existe caminho entre 2 e 0? %s\n", existeCaminhoDFS(G, 2, 0) ? "Sim" : "Não");
    printf("Existe caminho entre 4 e 1? %s\n", existeCaminhoDFS(G, 4, 1) ? "Sim" : "Não");
    printf("Existe caminho entre 3 e 5? %s\n", existeCaminhoDFS(G, 3, 5) ? "Sim" : "Não");

    liberarGrafoMatriz(G);

    return 0;
}
