/*
🔹 Exercício 1: Pilha, Arquivos e Ponteiros
📌 Enunciado:
Implemente a função processarArquivoPilha(FILE *arquivo), que lê um arquivo de texto contendo números inteiros (um por linha) 
e os armazena em uma pilha dinâmica. Depois, desempilhe os números, some-os e retorne o valor da soma.

📌 Conceitos envolvidos:

Ponteiros (FILE * e pilha dinâmica)
Alocação dinâmica (malloc())
Pilha (LIFO)
Manipulação de arquivos (fopen(), fgets(), fclose())
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int topo;
    int capacidade;
    int *dados;
} Pilha;

Pilha* criaPilha(int n){
    Pilha* novaPilha = (Pilha*)malloc(sizeof(Pilha));
    novaPilha->capacidade = n;
    novaPilha->topo = -1;
    novaPilha->dados = (int*)malloc(sizeof(int) * n);
    return novaPilha;
}

//push
void empilha(Pilha* pilha, int item){
    //verificar se ja ultrapasou capacidade
    if (pilha->topo == pilha->capacidade - 1) {
        printf("Pilha cheia!\n");
        return;
    }

    pilha->topo++;
    pilha->dados[pilha->topo] = item;
}

//pop
int desempilha(Pilha* pilha){
    /*VERIFICAR SE PILHA VAZIA
    if (estaVazia(p)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    */

    int temp = pilha->dados[pilha->topo];
    pilha->dados[pilha->topo] = -1;
    pilha->topo--;
    return temp;
}

int processarArquivoPilha(char * nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "r");

    //se n dizer capacidade fazer uma pilha com nós com ponteiro pro proximo
    Pilha* pilha = criaPilha(10);
    int num;
    char buffer[100];

    while (fscanf(arquivo, "%d", &num) == 1) {
        empilha(pilha, num);
    }

    num = 0;

    while (pilha->topo != -1)
    {
        num += desempilha(pilha);
    }
    

}