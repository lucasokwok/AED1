//Atividade 5 AED1 2024 Prof Luis
//Lucas de Oliveira Kwok 163919
 
#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    int id;
    int paginas;
    char prioridade;
} Tarefa;
 
typedef struct {
  Tarefa* tarefas;
  int n;
  int tamanho;
} Fila;
 
Fila* cria_Fila(int n){
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->n = n;
    fila->tamanho = 0;
    fila->tarefas = (Tarefa*)malloc(n*sizeof(Tarefa));
    for(int cont=0;cont<fila->n;cont++){
        fila->tarefas[cont].id = -1;
        fila->tarefas[cont].paginas = 0;
        fila->tarefas[cont].prioridade = '\0';
    }
    return fila;
}
 
void organiza_Fila(Fila *fila){
    if(fila->tamanho>1){
        for(int cont=fila->tamanho-1;cont>0;cont--){
            Tarefa tarefaTemp = fila->tarefas[cont];
            //if((fila->tarefas[cont-1].prioridade == 'N' || fila->tarefas[cont-1].prioridade == '\0')&& tarefaTemp.prioridade == 'U'){
            if(tarefaTemp.prioridade == 'U' && fila->tarefas[cont-1].prioridade != 'U'){
                fila->tarefas[cont] = fila->tarefas[cont-1];
                fila->tarefas[cont-1] = tarefaTemp;
                //printf("troquei %d", fila->tarefas[cont].id);
                //printf("por %d\n", fila->tarefas[cont  -1].id);
            }
        }
    }
}
 
void insere_Fila(Fila* fila, int id, int paginas, char prioridade){
    int fim = fila->tamanho++;
    Tarefa tarefaTemp;
    tarefaTemp.id = id;
    tarefaTemp.paginas = paginas;
    tarefaTemp.prioridade = prioridade;
    if (prioridade == 'N')
    {
        fila->tarefas[fim] = tarefaTemp;
        organiza_Fila(fila);
    }else{
        for (int cont = fila->tamanho; cont > 0; cont--) {
            fila->tarefas[cont] = fila->tarefas[cont - 1];
        }
        fila->tarefas[0] = tarefaTemp;
    } 
}
 
void remove_Fila(Fila *fila, int id){
    for(int cont=0;cont<fila->tamanho;cont++){
        if(fila->tarefas[cont].id == id){
            //fila->tarefas[cont].id = -1;
            //fila->tarefas[cont].paginas = 0;
            //fila->tarefas[cont].prioridade = '\0';
            /*
            printf("fila antes\n");
            for (int cont = 0; cont < fila->n; cont++) {
                printf("%d %d %c\n", fila->tarefas[cont].id, fila->tarefas[cont].paginas, fila->tarefas[cont].prioridade);
            }
            */
 
            for (int cont2 = cont; cont2 < fila->tamanho - 1; cont2++) {
                fila->tarefas[cont2] = fila->tarefas[cont2 + 1];
            }
            fila->tarefas[fila->tamanho - 1].id = -1;
            fila->tarefas[fila->tamanho - 1].paginas = 0;
            fila->tarefas[fila->tamanho - 1].prioridade = '\0';
            /*a
            printf("fila dps\n");
            for (int cont = 0; cont < fila->n; cont++) {
                printf("%d %d %c\n", fila->tarefas[cont].id, fila->tarefas[cont].paginas, fila->tarefas[cont].prioridade);
            }
            */
 
            fila->tamanho--;
            break;
        }
    }
}
 
void processa_Fila(Fila *fila){
    if(fila->tamanho>0)
        remove_Fila(fila, fila->tarefas[0].id);
}
 
int main(){
    int n;
    scanf("%d", &n);
 
    Fila* fila = cria_Fila(n);
 
    for(int cont=0;cont<n;cont++){
        char op;
        scanf(" %c", &op);
 
        if(op =='P'){
            if(fila->tamanho > 0){
                printf("%d %d %c\n", fila->tarefas[0].id, fila->tarefas[0].paginas, fila->tarefas[0].prioridade);
                processa_Fila(fila);
            }else{
                printf("\n");
            }
            
        } else if(op =='C'){
            int id, encontrou=0;
            scanf("%d", &id);
            if(fila->tamanho > 0){
                for(int cont=0;cont<fila->tamanho;cont++){
                    if(fila->tarefas[cont].id == id) {
                        printf("%d %d %c\n", fila->tarefas[cont].id, fila->tarefas[cont].paginas, fila->tarefas[cont].prioridade);
                        encontrou = 1;
                        break;
                    }
                }
                if(encontrou==0){
                    printf("\n");
                }
            }else
                printf("\n");
            
            remove_Fila(fila, id);
            
        } else if(op =='E'){
            int ordem;
            scanf("%d", &ordem);
            if(ordem == 0 && fila->tamanho > 0){
                for (int cont = 0; cont < fila->tamanho; cont++) {
                    printf("%d %d %c\n", fila->tarefas[cont].id, fila->tarefas[cont].paginas, fila->tarefas[cont].prioridade);
                }
            } else if(ordem == 1 && fila->tamanho > 0){
                for (int cont = fila->tamanho - 1; cont >= 0; cont--) {
                    printf("%d %d %c\n", fila->tarefas[cont].id, fila->tarefas[cont].paginas, fila->tarefas[cont].prioridade);
                }
            } else {
                printf("\n");
            }
 
        } else if(op == 'A'){
            int id, paginas, encontrou=0;
            char prioridade;
            scanf("%d %d %c", &id, &paginas, &prioridade);
            for(int cont=0;cont<fila->tamanho;cont++){
                if(fila->tarefas[cont].id == id) {
                    encontrou = 1;
                    break;
                }
            }
            if (encontrou==0)
                insere_Fila(fila,id,paginas,prioridade);
        } else{
            printf("\n");
            //scanf("%*[^\n]");
            //getchar();
        }
        //fflush(stdin);
    }
 
    free(fila->tarefas);
    free(fila);
    return 0;
}