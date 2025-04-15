#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct No {
    char nome[MAX];
    struct No* filho;
    struct No* irmao;
} No;

No* criarNo(const char* nome) {
    No* novo = (No*) malloc(sizeof(No));
    strcpy(novo->nome, nome);
    novo->filho  = NULL;
    novo->irmao  = NULL;
    return novo;
}

void desalocarArvore(No* raiz) {
    if (raiz == NULL) return;
    desalocarArvore(raiz->filho);
    desalocarArvore(raiz->irmao);
    free(raiz);
}

No* buscaArquivoDir(No* raiz, const char* nomeBuscado) {
    if (raiz == NULL) return NULL;

    if (strcmp(raiz->nome, nomeBuscado) == 0) {
        return raiz;
    }

    No* encontrado = buscaArquivoDir(raiz->filho, nomeBuscado);
    if (encontrado != NULL) {
        return encontrado;
    }
    return buscaArquivoDir(raiz->irmao, nomeBuscado);
}

No* buscaPai(No* raiz, const char* nomeFilho) {
    if (raiz == NULL || raiz->filho == NULL) 
        return NULL;

    No* filho = raiz->filho;
    while (filho != NULL) {
        if (strcmp(filho->nome, nomeFilho) == 0) {
            return raiz;
        }
        filho = filho->irmao;
    }

    No* encontrado = buscaPai(raiz->filho, nomeFilho);
    if (encontrado != NULL) 
        return encontrado;
    return buscaPai(raiz->irmao, nomeFilho);
}

void insereArquivoDir(No* raiz, const char* nomeNovo, const char* nomePai) {
    if (raiz == NULL) return;

    No* pai = buscaArquivoDir(raiz, nomePai);
    if (pai == NULL) {
        return;
    }

    No* novo = criarNo(nomeNovo);
    novo->irmao = pai->filho;
    pai->filho  = novo;
}

void removeArquivo(No* raiz, const char* nomeRemover) {
    if (raiz == NULL) return;

    No* pai = buscaPai(raiz, nomeRemover);
    if (pai == NULL) {
        return;
    }

    No* anterior = NULL;
    No* atual = pai->filho;

    while (atual) {
        if (strcmp(atual->nome, nomeRemover) == 0) {
            if (!anterior) {
                pai->filho = atual->irmao;
            } else {
                anterior->irmao = atual->irmao;
            }
            desalocarArvore(atual);
            return;
        }
        anterior = atual;
        atual = atual->irmao;
    }
}

void moverArquivo(No* raiz, const char* nomeArquivo, const char* nomeDestino) {
    if (raiz == NULL) return;

    No* node = buscaArquivoDir(raiz, nomeArquivo);
    if (node == NULL) {
        return;
    }

    No* paiAntigo = buscaPai(raiz, nomeArquivo);
    if (paiAntigo == NULL) {
        return;
    }

    No* anterior = NULL;
    No* atual = paiAntigo->filho;

    while (atual != NULL) {
        if (atual == node) {
            if (!anterior) {
                paiAntigo->filho = atual->irmao;
            } else {
                anterior->irmao = atual->irmao;
            }
            node->irmao = NULL; 
            break;
        }
        anterior = atual;
        atual = atual->irmao;
    }
    No* novoPai = buscaArquivoDir(raiz, nomeDestino);
    if (novoPai == NULL) {
        node->irmao = paiAntigo->filho;
        paiAntigo->filho = node;
        return;
    }
    node->irmao = novoPai->filho;
    novoPai->filho = node;
}

int printCaminho(No* raiz, const char* nomeBuscado) {
    if (raiz == NULL) return 0;
    if (strcmp(raiz->nome, nomeBuscado) == 0) {
        printf("%s", raiz->nome);
        return 1;
    }
    if (printCaminho(raiz->filho, nomeBuscado)) {
        printf("<-%s", raiz->nome);
        return 1;
    }
    if (printCaminho(raiz->irmao, nomeBuscado)) {
        return 1;
    }
    return 0;
}

int main() {
    int n;
    char linha[100];
    char operacao[3], nome1[MAX], nome2[MAX];

    No* raiz = criarNo("root");

    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &n);

    for (int i = 0; i < n; i++) {
        fgets(linha, sizeof(linha), stdin);
        sscanf(linha, "%s %s %s", operacao, nome1, nome2);
        if (strcmp(operacao, "-i") == 0) {
            insereArquivoDir(raiz, nome1, nome2);
        }
        else if (strcmp(operacao, "-m") == 0) {
            moverArquivo(raiz, nome1, nome2);
        }
        else if (strcmp(operacao, "-r") == 0) {
            removeArquivo(raiz, nome1);
        }
    }

    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", nome1);

    if (!printCaminho(raiz, nome1)) {
        printf("Arquivo nao encontrado");
    }

    //printf("\n");
    desalocarArvore(raiz);
    return 0;
}
