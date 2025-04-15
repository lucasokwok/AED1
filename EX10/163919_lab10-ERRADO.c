#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct No {
    char nome[MAX];
    struct No* irmao;
    struct No* filho;
} No;

No* criarNo(char arquivo[MAX]) {
    No* novo = (No*)malloc(sizeof(No));
    strcpy(novo->nome, arquivo);
    novo->irmao = NULL;
    novo->filho = NULL;
    return novo;
}

void adicionaArquivo(No* raiz, char arquivo[MAX], char dir[MAX]) {
    
    if (raiz == NULL) {
        return;
    }

    No* atual = raiz;

    while (atual != NULL) {
        if (strcmp(atual->nome, dir) == 0) {
            break;
        }
        atual = atual->filho;
    }

    if (atual != NULL && strcmp(atual->nome, dir) == 0) {
        No* novo = criarNo(arquivo);

        if (arquivo[0] == 'f') {
            if (atual->irmao == NULL) {
                atual->irmao = novo;
            } else {
                No* temp = atual->irmao;
                while (temp->irmao != NULL) {
                    temp = temp->irmao;
                }
                temp->irmao = novo;
            }
        } else {
            if (atual->filho == NULL) {
                atual->filho = novo;
            } else {
                No* temp = atual->filho;
                while (temp->filho != NULL) {
                    temp = temp->filho;
                }
                temp->filho = novo;
            }
        }
    }
}

int verificaArquivoExiste(No* raiz, char arquivo[MAX]){
    No* no;
    while (raiz != NULL)
    {
        no = raiz;
        while (no != NULL)
        {
            if(strcmp(no->nome, arquivo) == 0){
                return 1;
            }
            no = no->irmao;
        }
        raiz = raiz->filho;
    }

    return 0;
}

void removeArquivo(No* raiz, char arquivo[MAX]) {
    No* no;
    No* anterior;

    /*
    if (arquivo[0] == 'd') {
        return;
    }
    */

    while (raiz != NULL)
    {
        no = raiz;
        while (no != NULL)
        {
            if(strcmp(no->nome, arquivo) == 0){
                if(no->irmao != NULL)
                    anterior->irmao = no->irmao;
                else
                    anterior->irmao = NULL;

                free(no);
                return;
            }
            anterior = no;
            no = no->irmao;
        }
        anterior = NULL;
        raiz = raiz->filho;
    }
}

void moverArquivo(No* raiz, char arquivo[MAX], char dir[MAX]) {

    /*
    if (arquivo[0] == 'd' || raiz == NULL) {
        return;
    }
    */

    if(!verificaArquivoExiste(raiz, arquivo))
        return;

    removeArquivo(raiz, arquivo);
    adicionaArquivo(raiz, arquivo, dir);
}



/*
int printCaminho(No* raiz, char arquivo[MAX]) {
    if (raiz == NULL) return 0;

    No* root = raiz;

    while (raiz->irmao != NULL)
    {
        if(strcmp(raiz->nome, arquivo) == 0){
            printf("<-%s", raiz->nome);
            return 1;
        }
        raiz = raiz->irmao;
    }

    while (root != NULL){
        root = root->filho;
        No* irmaoRoot = root->irmao;
        while (irmaoRoot != NULL)
        {
            if(strcmp(irmaoRoot->nome, arquivo) == 0){
                printf("<-%s", irmaoRoot->nome);
                return 1;
            }
            irmaoRoot = irmaoRoot->irmao;
        }
    }

    return 0;
}
*/
int printCaminho(No* raiz, char arquivo[MAX]) {
    if (raiz == NULL) {
        return 0;  
    }

    if (strcmp(raiz->nome, arquivo) == 0) {

        printf("%s", raiz->nome);
        return 1;  
    }
    
    if (printCaminho(raiz->filho, arquivo)) {
        printf("<-%s", raiz->nome);
        return 1;
    }
    
    if (printCaminho(raiz->irmao, arquivo)) {
        return 1;
    }
    
    return 0;
}



void desalocarArvore(No* raiz) {
    if (raiz == NULL) {
        return;
    }
    desalocarArvore(raiz->filho);
    desalocarArvore(raiz->irmao);
    free(raiz);
}


int main() {
    int n;
    char linha[100], linhaOP[100], operacao[MAX], arquivo[MAX], dir[MAX];

    No* raiz = criarNo("root");

    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &n);

    for (int i = 0; i < n; i++) {
        fgets(linhaOP, sizeof(linhaOP), stdin);

        sscanf(linhaOP, "%s %s %s", operacao, arquivo, dir);

        if (operacao[1] == 'i') {
            adicionaArquivo(raiz, arquivo, dir);
        } else if(operacao[1] == 'm'){
            moverArquivo(raiz, arquivo, dir);
        } else if(operacao[1] == 'r'){
            removeArquivo(raiz, arquivo);
        }
    }

    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", arquivo);

    if (!printCaminho(raiz, arquivo)) {
        printf("Arquivo nao encontrado");
    }

    //printf("\n");

    desalocarArvore(raiz);
    return 0;
}
