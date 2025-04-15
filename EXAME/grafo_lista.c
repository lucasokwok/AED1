#include <stdio.h>
#include <stdlib.h>

/* Estrutura do Nó da Lista de Adjacência */
typedef struct No {
    int vertice;
    struct No *prox;
} No;

/* Estrutura do Grafo */
typedef struct {
    int numVertices;
    No **listaAdj;
} Grafo;

/* Cria um novo grafo com lista de adjacência */
Grafo* criarGrafoLista(int numVertices) {
    Grafo *G = (Grafo*) malloc(sizeof(Grafo));
    G->numVertices = numVertices;
    G->listaAdj = (No**) malloc(numVertices * sizeof(No*));

    for (int i = 0; i < numVertices; i++)
        G->listaAdj[i] = NULL;

    return G;
}

/* Adiciona uma aresta ao grafo */
void adicionarArestaLista(Grafo *G, int origem, int destino) {
    No *novo = (No*) malloc(sizeof(No));
    novo->vertice = destino;
    novo->prox = G->listaAdj[origem];
    G->listaAdj[origem] = novo;

    novo = (No*) malloc(sizeof(No));
    novo->vertice = origem;
    novo->prox = G->listaAdj[destino];
    G->listaAdj[destino] = novo;
}

/* Função auxiliar para busca em profundidade (DFS) */
int DFSUtil(Grafo *G, int atual, int destino, int *visitado) {
    if (atual == destino) return 1; // Se encontrou o destino, há caminho

    visitado[atual] = 1; // Marca o nó como visitado
    No *temp = G->listaAdj[atual];

    while (temp) {
        if (!visitado[temp->vertice]) {
            if (DFSUtil(G, temp->vertice, destino, visitado))
                return 1; // Se encontrou o destino, retorna verdadeiro
        }
        temp = temp->prox;
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

/* Imprime o grafo */
void imprimirGrafoLista(Grafo *G) {
    for (int i = 0; i < G->numVertices; i++) {
        No *temp = G->listaAdj[i];
        printf("Vértice %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertice);
            temp = temp->prox;
        }
        printf("NULL\n");
    }
}

/* Libera a memória do grafo */
void liberarGrafoLista(Grafo *G) {
    for (int i = 0; i < G->numVertices; i++) {
        No *temp = G->listaAdj[i];
        while (temp) {
            No *prox = temp->prox;
            free(temp);
            temp = prox;
        }
    }
    free(G->listaAdj);
    free(G);
}

/* Exemplo de uso */
int main() {
    Grafo *G = criarGrafoLista(6);
    adicionarArestaLista(G, 0, 1);
    adicionarArestaLista(G, 1, 2);
    adicionarArestaLista(G, 2, 3);
    adicionarArestaLista(G, 3, 4);
    adicionarArestaLista(G, 4, 0);

    imprimirGrafoLista(G);

    // Testando caminhos
    printf("\nVerificando caminhos:\n");
    printf("Existe caminho entre 0 e 3? %s\n", existeCaminhoDFS(G, 0, 3) ? "Sim" : "Não");
    printf("Existe caminho entre 1 e 5? %s\n", existeCaminhoDFS(G, 1, 5) ? "Sim" : "Não");
    printf("Existe caminho entre 2 e 0? %s\n", existeCaminhoDFS(G, 2, 0) ? "Sim" : "Não");
    printf("Existe caminho entre 4 e 1? %s\n", existeCaminhoDFS(G, 4, 1) ? "Sim" : "Não");
    printf("Existe caminho entre 3 e 5? %s\n", existeCaminhoDFS(G, 3, 5) ? "Sim" : "Não");

    liberarGrafoLista(G);

    return 0;
}
