//Atividade 3 AED1 2024 Prof Luis
//Lucas de Oliveira Kwok 163919

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int simbolo; // simbolo armazenado no noh
    struct No *prox; // ponteiro para o proximo noh     
    struct No *ant;// ponteiro para o noh anterior
}No;

typedef struct Tambor {
    No *cabeca; // ponteiro para a cabeca da sequencia de simbolos
}Tambor;

typedef struct Maquina{
    int n_tambores; // numero de tambores na maquina
    Tambor *tambores; // ponteiro para VETOR de Tambor e NAO vetor de PONTEIROS de Tambor
}Maquina;

//recebe um numero de tambores, aloca uma máquina e inicializa o campo “cabeca”
Maquina* cria_maquina(int n){
    Maquina *novaMaquina = (Maquina *)malloc(sizeof(Maquina));
    novaMaquina->n_tambores = n;
    novaMaquina->tambores = (Tambor *) malloc(n * sizeof(Tambor));

    for (int cont = 0; cont < n; cont++) {
        novaMaquina->tambores[cont].cabeca = NULL;
    }
    
    return novaMaquina;
}

//recebe a referencia de um “Tambor” e um sımbolo, insere o simbolo no tambor sem retornar nada
void insere_simbolo(Tambor *tambor, int simbolo){

    No *novoNO = (No*)malloc(sizeof(No));
    novoNO->simbolo = simbolo;

    if (tambor->cabeca == NULL) {
        tambor->cabeca = novoNO;
        novoNO->ant = novoNO;
        novoNO->prox = novoNO;
    } else {
        novoNO->prox = tambor->cabeca;
        novoNO->ant = tambor->cabeca->ant;
        tambor->cabeca->ant->prox = novoNO;
        tambor->cabeca->ant = novoNO;
    }
}

//recebe a referencia de um “Tambor” e um śımbolo, remove o simbolo do tambor (se o simbolo pertencer ao tambor) e nao retorna nada
void remove_simbolo(Tambor *tambor, int simbolo){
    if(tambor->cabeca != NULL){
        No *atual = tambor->cabeca->prox;

        if(tambor->cabeca->simbolo == atual->simbolo && tambor->cabeca->simbolo == simbolo){
            free(atual);
            tambor->cabeca = NULL;
        }else{
            while(tambor->cabeca!=atual && atual->simbolo != simbolo){
                atual = atual->prox;
            }
            
            if(atual->simbolo == simbolo){
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
                if(atual == tambor->cabeca)
                    tambor->cabeca = atual->prox;
                free(atual);
            }
        }

        
    }
}

//recebe a referencia de um “Tambor” e desaloca essa tambor
void desaloca_tambor(Tambor *tambor){
    No *atual = tambor->cabeca->prox;
    while(atual != tambor->cabeca){
        atual = atual->prox;
        free(atual->ant);
    }
    free(atual);
}

//recebe uma referencia de “Maquina”, invoca a funcao desaloca_tambor e desaloca os tambores
void desaloca_caixas(Maquina *maquina){
    for(int cont=0; cont<maquina->n_tambores; cont++){
        desaloca_tambor(&maquina->tambores[cont]);
    }
    
    free(maquina->tambores);
    free(maquina);
}
int main(){
    int n, m, remover;
    //numero de tambores na maquina
    scanf("%d", &n);

    int *nRotacoes = (int*) malloc(n * sizeof(int));
    int *sentido = (int*) malloc(n * sizeof(int));
    Maquina* maquina = cria_maquina(n);

    //numero de simbolos em cada tambor
    scanf("%d", &m);

    for(int cont = 0; cont<n; cont++){
        for(int cont2 = 0; cont2<m; cont2++){
            int temp;
            scanf("%d", &temp);
            insere_simbolo(&maquina->tambores[cont], temp);
        }
    }
    
    for (int cont = 0; cont<n; cont++) {
        scanf("%d", &nRotacoes[cont]);
    }

    for (int cont = 0; cont<n; cont++) {
        scanf("%d", &sentido[cont]);
    }

    //rotação
    for(int cont = 0; cont<n; cont++){
        Tambor *tamborTemp = &maquina->tambores[cont];
        //printf("tambor %d rodou %d vezes no sentido %d \n", cont, nRotacoes[cont], sentido[cont]);
        //printf("Inicio = %d -> ", tamborTemp->cabeca->simbolo);
        if(sentido[cont] == 1){
            //1
            for(int cont2 = 0; cont2<nRotacoes[cont]; cont2++){
                tamborTemp->cabeca = tamborTemp->cabeca->ant;
                //printf("%d -> ", tamborTemp->cabeca->simbolo);
            }
        }else{
            //0
            for(int cont2 = 0; cont2<nRotacoes[cont]; cont2++){
                tamborTemp->cabeca = tamborTemp->cabeca->prox;
                //printf("%d -> ", tamborTemp->cabeca->simbolo);
            }
        }
        
        //printf("\n");
    }
    
    for(int cont = 0; cont<n; cont++){
        Tambor *tamborTemp = &maquina->tambores[cont];
        printf("-%d", tamborTemp->cabeca->simbolo);
    }
    printf("-\n");

    //desfaz rotação
    for(int cont = 0; cont<n; cont++){
        Tambor *tamborTemp = &maquina->tambores[cont];
        if(sentido[cont] == 1){
            //1
            for(int cont2 = 0; cont2<nRotacoes[cont]; cont2++){
                tamborTemp->cabeca = tamborTemp->cabeca->prox;
            }
        }else{
            //0
            for(int cont2 = 0; cont2<nRotacoes[cont]; cont2++){
                tamborTemp->cabeca = tamborTemp->cabeca->ant;
            }
        }
    }

    //remover
    for (int cont = 0; cont<n; cont++) {
        scanf("%d", &remover);
        remove_simbolo(&maquina->tambores[cont], remover);
    }

    //rotação 2
    for(int cont = 0; cont<n; cont++){
        Tambor *tamborTemp = &maquina->tambores[cont];
        if(tamborTemp->cabeca != NULL){
            if(sentido[cont] == 1){
                //1
                for(int cont2 = 0; cont2<nRotacoes[cont]; cont2++){
                    tamborTemp->cabeca = tamborTemp->cabeca->ant;
                }
            }else{
                //0
                for(int cont2 = 0; cont2<nRotacoes[cont]; cont2++){
                    tamborTemp->cabeca = tamborTemp->cabeca->prox;
                }
            }
        }
    }
    
    for(int cont = 0; cont<n; cont++){
        Tambor *tamborTemp = &maquina->tambores[cont];
        if(tamborTemp->cabeca != NULL)
            printf("-%d", tamborTemp->cabeca->simbolo);
        
    }
    printf("-\n");

    free(nRotacoes);
    free(sentido);
    desaloca_caixas(maquina);
    return 0;    
}
