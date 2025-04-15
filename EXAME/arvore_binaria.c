#include <stdio.h>
#include <stdlib.h>

/* Estrutura do Nó da Árvore */
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

/* Insere um nó na árvore */
No* inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else
        raiz->direita = inserir(raiz->direita, valor);
    return raiz;
}

/* 1️⃣ Percurso Pré-Ordem (Raiz → Esquerda → Direita) */
void preOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

/* 2️⃣ Percurso Em-Ordem (Esquerda → Raiz → Direita) */
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

/* 3️⃣ Percurso Pós-Ordem (Esquerda → Direita → Raiz) */
void posOrdem(No *raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

/* 4️⃣ Percurso Por Nível (Largura - BFS) */
typedef struct Fila {
    No *no;
    struct Fila *prox;
} Fila;

/* Funções auxiliares para a Fila */
Fila* criarFila(No *raiz) {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->no = raiz;
    f->prox = NULL;
    return f;
}

void enfileirar(Fila **frente, Fila **tras, No *no) {
    Fila *novo = criarFila(no);
    if (*tras) (*tras)->prox = novo;
    *tras = novo;
    if (*frente == NULL) *frente = novo;
}

No* desenfileirar(Fila **frente) {
    if (*frente == NULL) return NULL;
    No *no = (*frente)->no;
    Fila *temp = *frente;
    *frente = (*frente)->prox;
    free(temp);
    return no;
}

int filaVazia(Fila *frente) {
    return frente == NULL;
}

/* Percorre a árvore em largura */
void porNivel(No *raiz) {
    if (raiz == NULL) return;

    Fila *frente = NULL, *tras = NULL;
    enfileirar(&frente, &tras, raiz);

    while (!filaVazia(frente)) {
        No *atual = desenfileirar(&frente);
        printf("%d ", atual->valor);

        if (atual->esquerda) enfileirar(&frente, &tras, atual->esquerda);
        if (atual->direita) enfileirar(&frente, &tras, atual->direita);
    }
}

/* Libera a memória da árvore */
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
    raiz = inserir(raiz, 10);
    inserir(raiz, 5);
    inserir(raiz, 15);
    inserir(raiz, 2);
    inserir(raiz, 7);
    inserir(raiz, 20);

    printf("Pré-Ordem: "); preOrdem(raiz); printf("\n");
    printf("Em-Ordem: "); emOrdem(raiz); printf("\n");
    printf("Pós-Ordem: "); posOrdem(raiz); printf("\n");
    printf("Por Nível: "); porNivel(raiz); printf("\n");

    liberarArvore(raiz);
    return 0;
}
