#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para uma célula da planilha
typedef struct Celula {
    char conteudo[50];  // Conteúdo da célula
    int linha, coluna;  // Coordenadas da célula
    struct Celula *cima, *baixo, *esquerda, *direita;  // Ponteiros para células vizinhas
} Celula;

// Função para criar uma nova célula
Celula* criarCelula(char* conteudo, int linha, int coluna) {
    Celula* novaCelula = (Celula*)malloc(sizeof(Celula));
    if (!novaCelula) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    strcpy(novaCelula->conteudo, conteudo);
    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    novaCelula->cima = novaCelula->baixo = novaCelula->esquerda = novaCelula->direita = NULL;
    return novaCelula;
}

// Função para inserir uma célula na matriz
void inserirCelula(Celula*** planilha, int linhas, int colunas, char* conteudo, int linha, int coluna) {
    if (linha >= linhas || coluna >= colunas) {
        printf("Posição (%d, %d) fora dos limites.\n", linha, coluna);
        return;
    }

    planilha[linha][coluna] = criarCelula(conteudo, linha, coluna);

    // Ajustando os ponteiros das células vizinhas
    if (linha > 0 && planilha[linha - 1][coluna]) {
        planilha[linha][coluna]->cima = planilha[linha - 1][coluna];
        planilha[linha - 1][coluna]->baixo = planilha[linha][coluna];
    }
    if (coluna > 0 && planilha[linha][coluna - 1]) {
        planilha[linha][coluna]->esquerda = planilha[linha][coluna - 1];
        planilha[linha][coluna - 1]->direita = planilha[linha][coluna];
    }
}

// Função para exibir a planilha
void exibirPlanilha(Celula*** planilha, int linhas, int colunas) {
    printf("\nPlanilha:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (planilha[i][j]) {
                printf("[%s (%d,%d)] ", planilha[i][j]->conteudo, planilha[i][j]->linha, planilha[i][j]->coluna);
            } else {
                printf("[vazio] ");
            }
        }
        printf("\n");
    }
}

// Função para remover uma linha e deslocar as células para cima
void removerLinha(Celula*** planilha, int* linhas, int colunas, int linhaRemovida) {
    if (linhaRemovida >= *linhas) {
        printf("Linha inválida.\n");
        return;
    }

    // Liberar memória da linha removida
    for (int j = 0; j < colunas; j++) {
        free(planilha[linhaRemovida][j]);
    }
    free(planilha[linhaRemovida]);

    // Deslocar as linhas para cima
    for (int i = linhaRemovida; i < (*linhas) - 1; i++) {
        planilha[i] = planilha[i + 1];
        for (int j = 0; j < colunas; j++) {
            if (planilha[i][j]) {
                planilha[i][j]->linha = i;
                if (i > 0) {
                    planilha[i][j]->cima = planilha[i - 1][j];
                }
            }
        }
    }

    (*linhas)--;
    planilha[*linhas] = NULL;
}

// Função para remover uma coluna e deslocar as células para a esquerda
void removerColuna(Celula*** planilha, int linhas, int* colunas, int colunaRemovida) {
    if (colunaRemovida >= *colunas) {
        printf("Coluna inválida.\n");
        return;
    }

    // Liberar memória da coluna removida
    for (int i = 0; i < linhas; i++) {
        free(planilha[i][colunaRemovida]);
    }

    // Deslocar as colunas para a esquerda
    for (int i = 0; i < linhas; i++) {
        for (int j = colunaRemovida; j < (*colunas) - 1; j++) {
            planilha[i][j] = planilha[i][j + 1];
            if (planilha[i][j]) {
                planilha[i][j]->coluna = j;
                if (j > 0) {
                    planilha[i][j]->esquerda = planilha[i][j - 1];
                }
            }
        }
    }

    (*colunas)--;
    for (int i = 0; i < linhas; i++) {
        planilha[i][*colunas] = NULL;
    }
}

// Função para liberar a memória alocada
void liberarPlanilha(Celula*** planilha, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (planilha[i][j]) {
                free(planilha[i][j]);
            }
        }
        free(planilha[i]);
    }
    free(planilha);
}

int main() {
    int linhas, colunas;

    printf("Digite o número de linhas e colunas: ");
    scanf("%d %d", &linhas, &colunas);

    // Alocar memória para a matriz de células
    Celula*** planilha = (Celula***)malloc(linhas * sizeof(Celula**));
    for (int i = 0; i < linhas; i++) {
        planilha[i] = (Celula**)calloc(colunas, sizeof(Celula*));
    }

    int n;
    printf("Digite o número de células a serem adicionadas: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char conteudo[50];
        int linha, coluna;

        printf("Digite o conteúdo e a posição (linha coluna): ");
        scanf("%s %d %d", conteudo, &linha, &coluna);

        inserirCelula(planilha, linhas, colunas, conteudo, linha, coluna);
    }

    exibirPlanilha(planilha, linhas, colunas);

    // Remover linha
    int linhaRem;
    printf("Digite a linha a ser removida: ");
    scanf("%d", &linhaRem);
    removerLinha(planilha, &linhas, colunas, linhaRem);
    exibirPlanilha(planilha, linhas, colunas);

    // Remover coluna
    int colunaRem;
    printf("Digite a coluna a ser removida: ");
    scanf("%d", &colunaRem);
    removerColuna(planilha, linhas, &colunas, colunaRem);
    exibirPlanilha(planilha, linhas, colunas);

    liberarPlanilha(planilha, linhas, colunas);

    return 0;
}
/*
ENTRADA
Digite o número de linhas e colunas: 3 3
Digite o número de células a serem adicionadas: 3
Digite o conteúdo e a posição (linha coluna): A1 0 0
Digite o conteúdo e a posição (linha coluna): B2 1 1
Digite o conteúdo e a posição (linha coluna): C3 2 2
Digite a linha a ser removida: 1
Digite a coluna a ser removida: 1

Saida
Planilha:
[A1 (0,0)] [vazio] 
[vazio] [C3 (1,1)] 

*/