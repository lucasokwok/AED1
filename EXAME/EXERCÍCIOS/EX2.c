/*🔹 Exercício 2: Lista Encadeada e Arquivos Binários
📌 Enunciado:
Implemente a função carregarListaBinario(FILE *arquivo), que lê um arquivo binário contendo números inteiros e os armazena 
em uma lista encadeada ordenada (crescente). Retorne a cabeça da lista.

📌 Conceitos envolvidos:

Lista encadeada
Manipulação de arquivos binários (fopen(), fread(), fclose())
Alocação dinâmica (malloc())*/

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    No* prox;
} No;

No* criaNo(int n){
    No* novo = (No*) malloc (sizeof(No));
    novo->valor;
    novo->prox = NULL;
}

No* adicionaNo(No* cabeca, int valor){
    No* novo = criaNo(valor);

    if(cabeca->valor > valor){
        novo->prox = cabeca;
        return novo;
    }

    No* atual = cabeca;
    while (atual->prox != NULL && atual->prox->valor < valor)
    {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;

    return cabeca;
}

No* carregarListaBinario(char *nomeArquivo){
    FILE* arquivoBinario = fopen(nomeArquivo, "rb");
    No* cabeca = NULL;
    int valor;

    //fread pq o arquivo é binario
    while (fread(&valor, sizeof(int), 1, arquivoBinario))
    {
        cabeca = criaNo(valor);
    }
    
    fclose(arquivoBinario);
    return cabeca;
}
