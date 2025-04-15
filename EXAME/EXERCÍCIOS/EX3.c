/*
🔹 Exercício 3: Árvore Binária e Arquivo Texto
📌 Enunciado:
Implemente a função construirArvore(FILE *arquivo), que lê um arquivo de texto contendo números inteiros e 
insere-os em uma árvore binária de busca (ABB). Retorne a raiz da árvore.

📌 Conceitos envolvidos:

Ponteiros e recursão
Árvore binária de busca (ABB)
Manipulação de arquivos (fopen(), fscanf(), fclose())
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    No* direita;
    No* esquerda;
} No;

typedef struct Arvore
{
    No* raiz;
} Arvore;

No* inserirNo(No* raiz, int valor){
    if (raiz == NULL) return criaNo(valor); //CASO BASE

    if (valor < raiz->valor) // se valor MENOR que raiz vai pra ESQUERDA
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else
    // se valor MAIOR que raiz vai pra DIREITA
        raiz->direita = inserir(raiz->direita, valor);
    return raiz;
}

No* criaNo(int valor){
    No* novo = (No*) malloc (sizeof(No));
    novo->direita = NULL;
    novo->esquerda = NULL;
    novo->valor = valor;
}

No* construirArvore(char* nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "rt");
    Arvore* arvore = (Arvore*)malloc(sizeof(Arvore));
    arvore->raiz = NULL;

    No* raiz = arvore->raiz;
    int num;

    while (fscanf(arquivo, "%d", &num) == 1)
    {
        raiz = inserirNo(arvore->raiz, num);
    }
    
    return raiz;
}
