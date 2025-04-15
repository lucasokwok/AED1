#include <stdio.h>
#include <stdlib.h>

/* Estrutura do Nó da Árvore Genérica */
typedef struct No {
    int valor;
    struct No *primeiroFilho;
    struct No *proxIrmao;
} No;

/* Cria um novo nó */
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->primeiroFilho = NULL;
    novo->proxIrmao = NULL;
    return novo;
}

/* Adiciona um filho como o primeiro da lista */
void adicionarFilhoPrimeiro(No *pai, int valor) {
    No *novo = criarNo(valor);
    novo->proxIrmao = pai->primeiroFilho;
    pai->primeiroFilho = novo;
}

/* Adiciona um filho como o último da lista */
void adicionarFilhoUltimo(No *pai, int valor) {
    No *novo = criarNo(valor);
    if (pai->primeiroFilho == NULL) {
        pai->primeiroFilho = novo;
    } else {
        No *temp = pai->primeiroFilho;
        while (temp->proxIrmao != NULL) {
            temp = temp->proxIrmao;
        }
        temp->proxIrmao = novo;
    }
}

/* Função auxiliar para encontrar e remover um nó */
No* removerNoAux(No *raiz, int valor, No **pai) {
    if (raiz == NULL) return NULL;

    if (raiz->valor == valor) {
        return raiz; // Nó encontrado
    }

    *pai = raiz;
    No *temp = raiz->primeiroFilho;
    while (temp != NULL) {
        No *encontrado = removerNoAux(temp, valor, pai);
        if (encontrado != NULL) {
            return encontrado;
        }
        temp = temp->proxIrmao;
    }

    return NULL;
}

/* Remove um nó da árvore */
void removerNo(No **raiz, int valor) {
    if (*raiz == NULL) return;

    No *pai = NULL;
    No *remover = removerNoAux(*raiz, valor, &pai);

    if (remover == NULL) {
        printf("Nó %d não encontrado!\n", valor);
        return;
    }

    // Caso o nó removido seja a raiz
    if (pai == NULL) {
        printf("Não é possível remover a raiz da árvore!\n");
        return;
    }

    // Se o nó a ser removido for o primeiro filho do pai
    if (pai->primeiroFilho == remover) {
        pai->primeiroFilho = remover->proxIrmao;
    } else {
        No *temp = pai->primeiroFilho;
        while (temp->proxIrmao != remover) {
            temp = temp->proxIrmao;
        }
        temp->proxIrmao = remover->proxIrmao;
    }

    // Libera a memória do nó removido e seus filhos
    remover->proxIrmao = NULL; // Evita que os filhos sejam considerados irmãos
    liberarArvore(remover);
}

/* Exibe a árvore */
void exibir(No *raiz, int nivel) {
    if (raiz == NULL) return;
    
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }
    
    printf("%d\n", raiz->valor);
    
    exibir(raiz->primeiroFilho, nivel + 1);
    exibir(raiz->proxIrmao, nivel);
}

/* Libera a memória da árvore */
void liberarArvore(No *raiz) {
    if (raiz == NULL) return;

    liberarArvore(raiz->primeiroFilho);
    liberarArvore(raiz->proxIrmao);

    free(raiz);
}

/* Exemplo de uso */
int main() {
    No *raiz = criarNo(1);

    adicionarFilhoPrimeiro(raiz, 2);
    adicionarFilhoUltimo(raiz, 3);
    adicionarFilhoUltimo(raiz, 4);
    
    adicionarFilhoPrimeiro(raiz->primeiroFilho, 5);
    adicionarFilhoUltimo(raiz->primeiroFilho, 6);
    
    printf("Árvore antes da remoção:\n");
    exibir(raiz, 0);

    printf("\nRemovendo o nó 2...\n");
    removerNo(&raiz, 2);
    exibir(raiz, 0);

    liberarArvore(raiz);
    return 0;
}
