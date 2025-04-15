    //Atividade 8 AED1 2024 Prof Luis
    //Lucas de Oliveira Kwok 163919

    #include <stdio.h>
    #include <stdlib.h>

    typedef struct No {
        int dado;
        struct No *esquerda, *direita;
    } No;

    No* criarNo(int dado) {
        No* novoNo = (No*)malloc(sizeof(No));
        novoNo->dado = dado;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    void pre_ordem(No* raiz) {
        if (raiz != NULL) {
            printf("%d", raiz->dado);
            pre_ordem(raiz->esquerda);
            pre_ordem(raiz->direita);
        }
    }

    void em_ordem(No* raiz) {
        if (raiz != NULL) {
            em_ordem(raiz->esquerda);
            printf("%d", raiz->dado);
            em_ordem(raiz->direita);
        }
    }

    void pos_ordem(No* raiz) {
        if (raiz != NULL) {
            pos_ordem(raiz->esquerda);
            pos_ordem(raiz->direita);
            printf("%d", raiz->dado);
        }
    }

    void por_nivel(No* raiz, int n) {
        if (raiz == NULL) {
            return;
        }

        int inicio = 0, fim = 0;
        No** fila = (No**)malloc(n * sizeof(No*));
        
        fila[fim] = raiz;
        fim++;

        while (inicio < fim) {
            No* atual = fila[inicio];
            inicio++;

            printf("%d", atual->dado);

            if (atual->esquerda != NULL) {
                fila[fim] = atual->esquerda;
                fim++;
            }
            if (atual->direita != NULL) {
                fila[fim] = atual->direita;
                fim++;
            }
        }

        free(fila);
    }

    No* inserir(No* raiz, int dado) {
        if (raiz == NULL) {
            return criarNo(dado);
        }
        if (dado < raiz->dado) {
            raiz->esquerda = inserir(raiz->esquerda, dado);
        } else if (dado > raiz->dado) {
            raiz->direita = inserir(raiz->direita, dado);
        }
        return raiz;
    }

    int buscar(No* raiz, int chave) {
        if (raiz == NULL) {
            return 0;
        }
        if (raiz->dado == chave) {
            return 1;
        }
        if (chave < raiz->dado) {
            return buscar(raiz->esquerda, chave);
        }
        return buscar(raiz->direita, chave);
    }

    void liberar_arvore(No* raiz) {
        if (raiz != NULL) {
            liberar_arvore(raiz->esquerda);
            liberar_arvore(raiz->direita);
            free(raiz);
        }
    }

    int main() {
        int n, buscarItem;

        scanf("%d", &n);
        
        if(n == 0){
            printf("0");
            return 0;
        }

        No* raiz = NULL;

        for (int cont = 0; cont < n; cont++) {
            int valor;
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }

        scanf("%d", &buscarItem);

        pre_ordem(raiz);
        printf("\n");

        em_ordem(raiz);
        printf("\n");

        pos_ordem(raiz);
        printf("\n");

        por_nivel(raiz, n);
        printf("\n");

        printf("%d", buscar(raiz, buscarItem));
        printf("\n");

        liberar_arvore(raiz);

        return 0;
    }
