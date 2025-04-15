#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int vertice;
    struct No* prox;
} No;

typedef struct Grafo {
    int nVertices;
    No** listaAdj;
} Grafo;

No* criaNo(int vertice) {
    No* no = (No*) malloc(sizeof(No));
    no->vertice = vertice;
    no->prox = NULL;
    return no;
}

Grafo* criaGrafo(int n) {
    Grafo* novoGrafo = (Grafo*) malloc(sizeof(Grafo));
    novoGrafo->nVertices = n;
    novoGrafo->listaAdj = (No**) malloc(n * sizeof(No*));

    for (int i = 0; i < n; i++) {
        novoGrafo->listaAdj[i] = NULL;
    }
    return novoGrafo;
}

void adicionaAresta(Grafo* grafo, int x, int y) {
    No* no = criaNo(y);

    no->prox = grafo->listaAdj[x];
    grafo->listaAdj[x] = no;
}

int buscaCaminho(Grafo* grafo, int origem, int destino, int* visitado) {
    if (origem == destino) return 1;

    visitado[origem] = 1;

    No* no = grafo->listaAdj[origem];
    while (no != NULL) {
        if (!visitado[no->vertice]) {
            if (buscaCaminho(grafo, no->vertice, destino, visitado)) {
                return 1;
            }
        }
        no = no->prox;
    }
    return 0;
}

int existeCaminho(Grafo* grafo, int origem, int destino) {
    int* visitado = (int*) malloc(grafo->nVertices * sizeof(int));
    for (int i = 0; i < grafo->nVertices; i++) {
        visitado[i] = 0;
    }
    int achou = buscaCaminho(grafo, origem, destino, visitado);
    free(visitado);
    return achou;
}

void liberaGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->nVertices; i++) {
        No* atual = grafo->listaAdj[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(grafo->listaAdj);
    free(grafo);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    if(n == 0 && m == 0){
        int xCaminho, yCaminho;
        scanf("%d %d", &xCaminho, &yCaminho);
        printf("0\n");
        return 0;
    }

    Grafo* grafo = criaGrafo(n);    

    for(int i = 0; i < m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        adicionaAresta(grafo, x, y);
    }

    int xCaminho, yCaminho;
    scanf("%d %d", &xCaminho, &yCaminho);

    printf("%d\n", existeCaminho(grafo, xCaminho, yCaminho));

    liberaGrafo(grafo);
    return 0;
}
