        //Atividade 11 AED1 2024 Prof Luis
        //Lucas de Oliveira Kwok 163919

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

        No* criaNo(int vertice){
            No* no = (No*)malloc(sizeof(No));
            no->vertice = vertice;
            no->prox = NULL;

            return no;
        }

        Grafo* criaGrafo(int n){
            Grafo* novoGrafo = (Grafo*)malloc(sizeof(Grafo));
            novoGrafo->nVertices = n;
            novoGrafo->listaAdj = (No**)malloc(n * sizeof(No*));
            for (int i = 0; i < n; i++) {
                novoGrafo->listaAdj[i] = criaNo(i);
            }
            return novoGrafo;
        }

        /*
        void adicionaAresta(Grafo* grafo, int x, int y){
            No* no = criaNo(y);

            if(grafo->listaAdj[x]->prox != NULL){
                No* temp = grafo->listaAdj[x]->prox;
                grafo->listaAdj[x]->prox = no;
                no->prox = temp;
            }else{
                grafo->listaAdj[x]->prox = no;
            }
        }
        */

        void adicionaAresta(Grafo* grafo, int x, int y){
            // ida e volta
            No* no1 = criaNo(y);
            no1->prox = grafo->listaAdj[x]->prox;
            grafo->listaAdj[x]->prox = no1;

            No* no2 = criaNo(x);
            no2->prox = grafo->listaAdj[y]->prox;
            grafo->listaAdj[y]->prox = no2;
        }

        /*
        int verificaCaminho(No** listaAdj, int x, int y){
            No* no = listaAdj[x];
            while (no != NULL)
            {
                if(no->vertice == y){
                    return 1;
                }else{
                    if(verificaCaminho(listaAdj, no->vertice, y)) return 1;
                }
                no = no->prox;
            }

            return 0;
        }
        */
    
        int buscaCaminho(Grafo* grafo, int origem, int destino, int* visitado) {
            if (origem == destino) return 1;

            visitado[origem] = 1;

            No* no = grafo->listaAdj[origem];
            while (no != NULL) {
                if (visitado[no->vertice] == 0) { 
                    if (buscaCaminho(grafo, no->vertice, destino, visitado)) {
                        return 1;
                    }
                }
                no = no->prox;
            }
            
            return 0;
        }

        int existeCaminho(Grafo* grafo, int origem, int destino) {
            int* visitado = (int*)malloc(grafo->nVertices * sizeof(int));

            for(int i = 0; i < grafo->nVertices; i++){
                visitado[i] = 0;
            }

            int existeCaminho = buscaCaminho(grafo, origem, destino, visitado);
            free(visitado);
            
            return existeCaminho;
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
                printf("0");
                return 0;
            }
            Grafo* grafo = criaGrafo(n);

            for(int i = 0; i < m; i++){
                int x,y;
                scanf("%d %d", &x, &y);
                adicionaAresta(grafo, x, y);
            }

            int xCaminho, yCaminho;
            scanf("%d %d", &xCaminho, &yCaminho);

            /*
            for(int i = 0; i < grafo->nVertices; i++){
                verificaCaminho(grafo->listaAdj[i], yCaminho);
            }
            */

            printf("%d", existeCaminho(grafo, xCaminho, yCaminho));
            liberaGrafo(grafo);
            return 0;
        }
