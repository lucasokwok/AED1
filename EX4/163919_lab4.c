//Atividade 4 AED1 2024 Prof Luis
//Lucas de Oliveira Kwok 163919

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operacao {
    char tipo; // ’I’ para inserir, ’R’ para remover
    char caractere; // caractere inserido ou removido
    int posicao; // posicao no texto onde a operacao ocorreu
    struct Operacao *prox; // ponteiro para a proxima operacao na pilha
} Operacao;

typedef struct Pilha {
    Operacao* PrimeiraOp;
} Pilha;

Pilha* alocaPilha(){
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->PrimeiraOp = NULL;
    return pilha;
}

void pushPilha(Pilha* pilha, char caractere, int posicao, char tipo){
    Operacao* op = (Operacao*) malloc(sizeof(Operacao));
    op->caractere = caractere;
    op->posicao = posicao;
    op->tipo = tipo;
    op->prox = pilha->PrimeiraOp;
    pilha->PrimeiraOp = op;
}

void popPilha(Pilha* pilha){
    if(pilha->PrimeiraOp != NULL){
        Operacao* op = pilha->PrimeiraOp;
        pilha->PrimeiraOp = op->prox;
        free(op);
    }
}

void insere(char *texto, char caractere, int posicao, int nChar){
    for (int cont = nChar; cont > posicao; cont--) {
        texto[cont] = texto[cont - 1];
    }
    texto[posicao] = caractere;
    texto[nChar + 1] = '\0';
}

void remover(char *texto, int posicao, int nChar){
    for(int cont = posicao; cont < nChar + 1; cont++){
        texto[cont] = texto[cont + 1];
    }
    texto[nChar - 1] = '\0';
}

void desalocaPilha(Pilha* pilha) {
    while (pilha->PrimeiraOp != NULL) {
        popPilha(pilha);
    }
    free(pilha);
}

void limpaPilha(Pilha* pilha) {
    while (pilha->PrimeiraOp != NULL) {
        popPilha(pilha);
    }
}

int main(){
    int nChar, nOperacoes;
    scanf("%d", &nChar);
    
    char *texto = malloc((nChar + 1) * sizeof(char));

    if (nChar == 0) {
        texto[0] = '\0';
    } else {
        scanf("%s", texto);
    }

    scanf("%d", &nOperacoes);

    texto = realloc(texto, (nChar + 1 + nOperacoes) * sizeof(char));

    Pilha* pilha = alocaPilha();
    Pilha* pilhaRedo = alocaPilha();

    for(int cont=0;cont<nOperacoes;cont++){
        char operacao, caractere;
        int posicao;
        
        scanf(" %c", &operacao);
        if(operacao == 'I'){
            scanf(" %c %d", &caractere, &posicao);
            if ((posicao >= 0 && posicao <= nChar)){
                insere(texto, caractere, posicao, nChar);
                nChar++;
                pushPilha(pilha, caractere, posicao, 'I');
                limpaPilha(pilhaRedo);
            }
        } else if(operacao == 'R'){
            scanf("%d", &posicao);
            if (posicao >= 0 && posicao < nChar){
                caractere = texto[posicao];
                remover(texto, posicao, nChar);
                nChar--;
                pushPilha(pilha, caractere, posicao, 'R');
                limpaPilha(pilhaRedo);
            }
        } else if (operacao == 'U')
        {
            if(pilha->PrimeiraOp != NULL){
                char caractere = pilha->PrimeiraOp->caractere;
                char tipo = pilha->PrimeiraOp->tipo;
                int posicao = pilha->PrimeiraOp->posicao;
                popPilha(pilha);

                if (tipo == 'I') {
                    remover(texto, posicao, nChar);
                    nChar--;
                } else if (tipo == 'R') {
                    insere(texto, caractere, posicao, nChar);
                    nChar++;
                }
                pushPilha(pilhaRedo, caractere, posicao, tipo);
            } 
        } else if (operacao == 'E')
        {
            if(pilhaRedo->PrimeiraOp != NULL){
                char caractere = pilhaRedo->PrimeiraOp->caractere;
                char tipo = pilhaRedo->PrimeiraOp->tipo;
                int posicao = pilhaRedo->PrimeiraOp->posicao;
                popPilha(pilhaRedo);

                if (tipo == 'R') {
                    remover(texto, posicao, nChar);
                    nChar--;
                } else if (tipo == 'I') {
                    insere(texto, caractere, posicao, nChar);
                    nChar++;
                }
                pushPilha(pilha, caractere, posicao, tipo);
            }
        }
        printf("%s\n", texto); 
    }

    free(texto);
    desalocaPilha(pilha);
    desalocaPilha(pilhaRedo);
    return 0;
}