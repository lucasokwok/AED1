//Atividade 2 AED1 2024 Prof Luis
//Lucas de Oliveira Kwok 163919

#include <stdio.h>
#include <stdlib.h>

/* Estrutura de um noh da lista encadeada */
struct no{
    int info; // valor armazenado no noh
    struct no *prox; // ponteiro para o proximo noh
};

typedef struct no No;

/* Estrutura das caixas */
struct cx {
    No **caixa; // ponteiro para as caixas
    int N; // numero de caixas
};

typedef struct cx Caixa;

No* inicializa(){
    return NULL;
}

Caixa* aloca_caixas(int N){
    Caixa *novaCaixa = (Caixa *)malloc(sizeof(Caixa));

    novaCaixa->N = N;
    novaCaixa->caixa = (No**)malloc(N * sizeof(No*));
    for (int cont = 0; cont < N; cont++) {
        novaCaixa->caixa[cont] = inicializa();
    }
    
    return novaCaixa;
}

int h(int item, int N){
    return item % N;
}

void insere(Caixa *cx, int item){
    int nCaixa = 0;

    nCaixa = h(item, cx->N);
    No *novoNO = (No*)malloc(sizeof(No));
    novoNO->info = item;
    novoNO->prox = cx->caixa[nCaixa];
    cx->caixa[nCaixa] = novoNO;
}

No* retira(Caixa *cx, int item){
    int nCaixa = 0;
    nCaixa = h(item, cx->N);
    No *anterior = NULL;
    No *atual = cx->caixa[nCaixa];

    while (atual->info != item)
    {
        anterior = atual;   
        atual = atual->prox;    
        if(atual == NULL)
            return NULL;
    }

    if(anterior == NULL)
        cx->caixa[nCaixa] = atual->prox;
    else
        anterior->prox = atual->prox;

    return atual;
}

void desaloca_lista(No *lista){
    No *aux = NULL;

    while (lista->prox != NULL)
    {
        aux = lista->prox;
        free(lista);
        lista = aux;
    }
    free(lista);
}

void desaloca_caixas(Caixa *cx){
    for(int cont=0;cont<=cx->N - 1;cont++){
        if(cx->caixa[cont] != NULL)
        desaloca_lista(cx->caixa[cont]);
    }
    free(cx->caixa);
    free(cx);
}

void imprime(Caixa *cx){
    No *aux = NULL;

    for(int cont=0;cont<=cx->N - 1;cont++){
        aux = cx->caixa[cont];
        if (aux != NULL) {
            while (aux->prox != NULL)
            {
                printf("%d ", aux->info);
                aux = aux->prox;
            }
            printf("%d \n", aux->info);
        }
    }
}

int main(){
    int N = 0, m = 0, remover = 0;
    scanf("%d", &N);
    Caixa *cx = aloca_caixas(N);
    scanf("%d", &m);
    for(int cont=0;cont<m;cont++){
        int item = 0;

        scanf("%d", &item);
        insere(cx, item);
    }
    
    scanf("%d", &remover);
    No *removido = retira(cx, remover);
    if(removido != NULL){
        printf("%d \n", remover);
        free(removido);
    }
    else
        printf("-1 \n");

    imprime(cx);

    desaloca_caixas(cx);
    return 0;    
}
