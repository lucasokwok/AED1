#include <stdio.h>
#include <stdlib.h>

/* Estrutura do Nó da Árvore Binária de Busca (ABB) */
typedef struct No {
    int valor;
    struct No *esquerda, *direita;
} No;

/* Cria um novo nó */
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

/* Insere um nó na ABB */
No* inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else
        raiz->direita = inserir(raiz->direita, valor);
    return raiz;
}

/* Busca um valor na ABB */
No* buscar(No *raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;
    if (valor < raiz->valor)
        return buscar(raiz->esquerda, valor);
    return buscar(raiz->direita, valor);
}

/* Encontra o menor nó da subárvore direita */
No* encontrarMenor(No *raiz) {
    while (raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

/* Remove um nó da ABB */
No* remover(No *raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        /* Caso 1: Nó sem filhos */
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        /* Caso 2: Nó com um filho */
        else if (raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        /* Caso 3: Nó com dois filhos */
        else {
            No *sucessor = encontrarMenor(raiz->direita);
            raiz->valor = sucessor->valor;
            raiz->direita = remover(raiz->direita, sucessor->valor);
        }
    }
    return raiz;
}

/* Percurso Em-Ordem (Imprime os valores ordenados) */
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

/* Libera toda a memória da árvore */
void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

/* Exemplo de uso */
int main() {
    No *raiz = NULL;
    raiz = inserir(raiz, 50);
    inserir(raiz, 30);
    inserir(raiz, 70);
    inserir(raiz, 20);
    inserir(raiz, 40);
    inserir(raiz, 60);
    inserir(raiz, 80);

    printf("Árvore Em-Ordem antes da remoção:\n");
    emOrdem(raiz);
    printf("\n");

    /* Testando remoção */
    printf("Removendo nó sem filhos (20)...\n");
    raiz = remover(raiz, 20);
    emOrdem(raiz);
    printf("\n");

    printf("Removendo nó com um filho (30)...\n");
    raiz = remover(raiz, 30);
    emOrdem(raiz);
    printf("\n");

    printf("Removendo nó com dois filhos (50)...\n");
    raiz = remover(raiz, 50);
    emOrdem(raiz);
    printf("\n");

    /* Liberando memória */
    liberarArvore(raiz);

    return 0;
}
