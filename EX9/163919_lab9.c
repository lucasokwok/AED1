    //Atividade 9 AED1 2024 Prof Luis
    //Lucas de Oliveira Kwok 163919

    #include <stdio.h>
    #include <stdlib.h>

    typedef struct No {
        int dado;
        struct No* esquerda;
        struct No* direita;
    } No;

    No* criarNo(int valor) {
        No* novo = (No*)malloc(sizeof(No));
        novo->dado = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    No* inserir(No* raiz, int valor) {
        if (raiz == NULL) {
            return criarNo(valor);
        }
        if (valor < raiz->dado) {
            raiz->esquerda = inserir(raiz->esquerda, valor);
        } else if (valor > raiz->dado) {
            raiz->direita = inserir(raiz->direita, valor);
        }
        return raiz;
    }

    No* remover(No* raiz, int chave) {
        No* atual = raiz;
        No* pai = NULL;

        while (atual != NULL && atual->dado != chave) {
            pai = atual;
            if (chave < atual->dado) {
                atual = atual->esquerda;
            } else {
                atual = atual->direita;
            }
        }

        if (atual == NULL) 
            return raiz;
            
        if (atual->esquerda == NULL && atual->direita == NULL) {
            if (pai == NULL) {
                free(atual);
                return NULL;
            }
            if (pai->esquerda == atual) {
                pai->esquerda = NULL;
            } else {
                pai->direita = NULL;
            }

            free(atual);

        } else if (atual->esquerda == NULL || atual->direita == NULL) {
            //um filho
            No* filho = (atual->esquerda != NULL) ? atual->esquerda : atual->direita;
            if (pai == NULL) {
                free(atual);
                return filho;
            }
            if (pai->esquerda == atual) {
                pai->esquerda = filho;
            } else {
                pai->direita = filho;
            }
            free(atual);

        } else {
            //dois filhos
            No* sucessor = atual->direita;
            No* paiSucessor = atual;
            while (sucessor->esquerda != NULL) {
                //encontra menor a direita
                paiSucessor = sucessor;
                sucessor = sucessor->esquerda;
            }
            atual->dado = sucessor->dado;
            if (paiSucessor->esquerda == sucessor) {
                paiSucessor->esquerda = sucessor->direita;
            } else {
                paiSucessor->direita = sucessor->direita;
            }
            free(sucessor);
        }
        return raiz;
    }

    void percorrerEmNivel(No* raiz, int n) {
        if (raiz == NULL) return;
        No** fila = (No**)malloc(sizeof(No*) * n);
        int inicio = 0, fim = 0;
        fila[fim] = raiz;
        fim++;

        while (inicio < fim) {
            No* atual = fila[inicio++];
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

    int contarNos(No* raiz) {
        if (raiz == NULL) return 0;
        return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
    }

    void liberarArvore(No* raiz) {
        if (raiz != NULL) {
            liberarArvore(raiz->esquerda);
            liberarArvore(raiz->direita);
            free(raiz);
        }
    }

    int main() {
        int n, m;
        scanf("%d", &n);
        No* raiz = NULL;
        for(int cont = 0; cont < n; cont++){
            int valor;
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }
        percorrerEmNivel(raiz, n);

        printf("\n");

        scanf("%d", &m);

        for(int cont = 0; cont < m; cont++){
            int valor;
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
        }

        printf("%d", contarNos(raiz));

        liberarArvore(raiz);
        return 0;
    }
