//Atividade 6 AED1 2024 Prof Luis
//Lucas de Oliveira Kwok 163919
 
#include <stdio.h>
#include <stdlib.h>


/*
char* corrigeNomeArquivo(char *str, int tamanho){
    int cont, cont2 = 0;

    for (cont = tamanho - 1; cont >= 0; cont--) {
        if (str[cont] == '\\' || str[cont] == '/')
            break;
    }

    char *nomeArquivo = (char *)malloc((tamanho - cont) * sizeof(char));

    for (int cont3 = cont + 1; cont3 < tamanho; cont3++) {
        cont2++;
        nomeArquivo[cont2] = str[cont3];
    }
    nomeArquivo[cont2 + 1] = '\0';

    return nomeArquivo;
}
*/
int tamanhoString(char *str) {
    int tamanho = 0;
    while (str[tamanho] != '\0') {
        tamanho++;
    }
    return tamanho;
}

void trataString(char *str) {
    int tamanho = tamanhoString(str);
    char *strNOVO = (char *)malloc((tamanho + 1) * sizeof(char)); 
    int cont2 = 0;

    for (int cont = 0; cont < tamanho; cont++) {
        char c = str[cont];

        if (c != '.' && c != ',' && c != ';' && c != '\n' && c != ' ') {

            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }
            
            strNOVO[cont2] = c;
            cont2++;
        }
    }

    strNOVO[cont2] = '\0';

    for (int cont = 0; cont <= cont2; cont++) {
        str[cont] = strNOVO[cont];
    }

    free(strNOVO); 
}

//01234  012345  012345
//anna\0 radar\0 arara\0
int verificaPalindromo(char *str, int inicio, int fim){
    //nao é palindromo
    if(str[inicio] != str[fim]) return 0;
    
    //é palindromo
    if(inicio >= fim) return 1;

    return verificaPalindromo(str, inicio + 1, fim - 1);
}

int main(){
//int main(){
    int n, tamMAX;

    scanf("%d %d", &n, &tamMAX);

    //scanf("%d", &n);
    //scanf("%d", &tamMAX);
    
    char *palavra = (char *)malloc((tamMAX + 1) * sizeof(char));
    int *resposta = (int *)malloc(n * sizeof(int));

    //char *resposta = (char *)malloc((n + 1) * sizeof(char));
    //tamNomeARQUIVO = tamanhoString(argv[0]);

    //char *nomeArquivo = corrigeNomeArquivo(argv[0], tamNomeARQUIVO);

    //printf("%s", nomeArquivo);
    
    //printf("%s", argv[0]);
    getchar();
    for(int cont = 0; cont<n; cont++){
        fgets(palavra, tamMAX + 1, stdin);
        trataString(palavra);
        resposta[cont] = verificaPalindromo(palavra, 0, tamanhoString(palavra) - 1);
    }

    /*
    if (argc != 3) 
        return 1;

    FILE *arquivoENTRADA = fopen(argv[1], "r");
    FILE *arquivoSAIDA = fopen(argv[2], "w");

    fscanf(arquivoENTRADA, "%d %d", &n, &tamMAX);

    char *palavra = (char *)malloc((tamMAX + 1) * sizeof(char));

    while (fscanf(arquivoENTRADA, "%s", palavra) != EOF) {
        fprintf(arquivoSAIDA, "%d\n", verificaPalindromo(palavra, 0, tamanhoString(palavra) - 1));
    }

    fclose(arquivoENTRADA);
    fclose(arquivoSAIDA);
    
    */

    //free(nomeArquivo);
    for(int cont = 0; cont<n; cont++){
        printf("%d", resposta[cont]);
    }
    
    free(palavra);
    free(resposta);
    return 0;
}