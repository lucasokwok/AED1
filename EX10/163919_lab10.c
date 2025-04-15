//Atividade 10 AED1 2024 Prof Luis
//Lucas de Oliveira Kwok 163919

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

No* buscaDiretorioArquivo(No* raiz, char dir[MAX]){
    if (raiz == NULL) return NULL;

    if (strcmp(raiz->nome, dir) == 0) {
        return raiz;
    }

    No* encontrado = buscaDiretorioArquivo(raiz->filho, dir);

    if (encontrado != NULL) {
        return encontrado;
    }
    return buscaDiretorioArquivo(raiz->irmao, dir);
}

void adicionaArquivo(No* raiz, char arquivo[MAX], char dir[MAX]) {
    if (raiz == NULL) return;

    No* pai = buscaDiretorioArquivo(raiz, dir);

    if (pai == NULL) {
        return;
    }

    No* novo = criarNo(arquivo);
    novo->irmao = pai->filho;
    pai->filho  = novo;
}

No* buscaPai(No* raiz, char* nomeFilho) {
    if (raiz == NULL) 
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
/*
void removeArquivo(No* raiz, char arquivo[MAX]) {
    if (raiz == NULL) return;

    No* noArquivo = buscaDiretorioArquivo(raiz, arquivo);

    if(noArquivo == NULL) return;

    No* pai = buscaPai(raiz, arquivo);

    if(noArquivo->irmao != NULL){
        
        No* filho = pai->filho;

        while(filho->irmao != noArquivo){
            filho = filho->irmao;
        }
        filho->irmao = noArquivo->irmao;
    }else{
        pai->filho = NULL;
    }
    
    free(noArquivo);
}*/

void removeArquivo(No* raiz, char arquivo[MAX]) {
    if (raiz == NULL) return;

    No* noArquivo = buscaDiretorioArquivo(raiz, arquivo);
    if (noArquivo == NULL || noArquivo->filho != NULL) return;

    No* pai = buscaPai(raiz, arquivo);
    if (pai == NULL) return;

    No* filho = pai->filho;

    if (filho == noArquivo) {
        pai->filho = noArquivo->irmao;
    } else {
        No* atual = filho;
        while (atual && atual->irmao && atual->irmao != noArquivo) {
            atual = atual->irmao;
        }
        if (atual && atual->irmao == noArquivo) {
            atual->irmao = noArquivo->irmao;
        } else {
            return; 
        }
    }
    free(noArquivo);
}

void moverArquivo(No* raiz, char arquivo[MAX], char dir[MAX]) {
    No* destino = buscaDiretorioArquivo(raiz, dir);
    No* noArquivo = buscaDiretorioArquivo(raiz, arquivo);

    if (destino == NULL) return;             
    if (noArquivo == NULL || noArquivo->filho != NULL) return;     

    removeArquivo(raiz, arquivo);
    adicionaArquivo(raiz, arquivo, dir);
}


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
