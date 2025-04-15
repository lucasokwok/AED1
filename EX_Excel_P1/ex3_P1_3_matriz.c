#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma célula
typedef struct Celula {
    int valor;
    struct Celula *cima;
    struct Celula *baixo;
    struct Celula *esquerda;
    struct Celula *direita;
} Celula;

// Estrutura da Planilha
// - "linhas" e "colunas": tamanho atual
// - "matriz": armazena de fato as células (cada elemento é um bloco contíguo)
// Não há mais o campo cantoSuperiorEsquerdo.
typedef struct {
    int linhas;
    int colunas;
    Celula **matriz;  // Vetor de ponteiros para linhas; cada linha é um array contíguo de Celula
} Planilha;

/**
 * Função que refaz as ligações (cima, baixo, esquerda, direita)
 * após qualquer mudança estrutural (remoção de linha/coluna).
 */
void reconstruirLigacoes(Planilha *p) {
    if (!p || !p->matriz) return;

    // Zera os ponteiros de cada célula
    for(int i = 0; i < p->linhas; i++) {
        for(int j = 0; j < p->colunas; j++) {
            p->matriz[i][j].cima     = NULL;
            p->matriz[i][j].baixo    = NULL;
            p->matriz[i][j].esquerda = NULL;
            p->matriz[i][j].direita  = NULL;
        }
    }

    // "Costura" com base nas posições
    for(int i = 0; i < p->linhas; i++) {
        for(int j = 0; j < p->colunas; j++) {
            // Se não está na primeira linha, liga cima/baixo
            if(i > 0) {
                p->matriz[i][j].cima        = &p->matriz[i-1][j];
                p->matriz[i-1][j].baixo     = &p->matriz[i][j];
            }
            // Se não está na primeira coluna, liga esquerda/direita
            if(j > 0) {
                p->matriz[i][j].esquerda    = &p->matriz[i][j-1];
                p->matriz[i][j-1].direita   = &p->matriz[i][j];
            }
        }
    }
}

/**
 * Cria uma planilha com "linhas" e "colunas" usando **.
 */
Planilha* criarPlanilha(int linhas, int colunas) {
    if(linhas <= 0 || colunas <= 0) return NULL;

    Planilha *plan = (Planilha*) malloc(sizeof(Planilha));
    plan->linhas = linhas;
    plan->colunas = colunas;

    // Aloca um vetor de "linhas"
    plan->matriz = (Celula**) malloc(linhas * sizeof(Celula*));

    // Para cada linha, aloca um array contíguo de 'colunas' células
    for(int i = 0; i < linhas; i++) {
        plan->matriz[i] = (Celula*) malloc(colunas * sizeof(Celula));
    }

    // Inicializa valores e ponteiros
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            plan->matriz[i][j].valor    = 0;
            plan->matriz[i][j].cima     = NULL;
            plan->matriz[i][j].baixo    = NULL;
            plan->matriz[i][j].esquerda = NULL;
            plan->matriz[i][j].direita  = NULL;
        }
    }

    // Costura as ligações
    reconstruirLigacoes(plan);

    return plan;
}

/**
 * Libera toda a memória de uma planilha.
 */
void liberarPlanilha(Planilha *p) {
    if (!p) return;
    if (p->matriz) {
        // Libera cada linha
        for(int i = 0; i < p->linhas; i++) {
            free(p->matriz[i]);
        }
        // Libera o vetor de ponteiros de linha
        free(p->matriz);
    }
    free(p);
}

/**
 * Retorna ponteiro para a célula na linha e coluna (1-based).
 * Caso seja inválido, retorna NULL.
 */
Celula* obterCelula(Planilha *p, int linha, int coluna) {
    if(!p || !p->matriz) return NULL;
    if(linha < 1 || coluna < 1 || linha > p->linhas || coluna > p->colunas) {
        return NULL;
    }
    // p->matriz[linha-1][coluna-1] é a célula
    return &(p->matriz[linha-1][coluna-1]);
}

/**
 * Define o valor de (linha, coluna) para "valor".
 */
void definirValor(Planilha *p, int linha, int coluna, int valor) {
    Celula *c = obterCelula(p, linha, coluna);
    if(c) {
        c->valor = valor;
    } else {
        printf("Coordenada (%d, %d) invalida!\n", linha, coluna);
    }
}

/**
 * Imprime a planilha inteira.
 */
void imprimirPlanilha(Planilha *p) {
    if(!p || !p->matriz || p->linhas == 0 || p->colunas == 0) {
        printf("Planilha vazia ou inexistente.\n\n");
        return;
    }

    for(int i = 1; i <= p->linhas; i++) {
        for(int j = 1; j <= p->colunas; j++) {
            Celula *c = obterCelula(p, i, j);
            if(c) {
                printf("%4d ", c->valor);
            } else {
                printf(" ERRO ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Remove a linha "linhaParaRemover" e faz as linhas de baixo "subirem".
 *  1) Libera o bloco daquela linha.
 *  2) Desloca as linhas seguintes para cima.
 *  3) Decrementa p->linhas.
 *  4) Reconstrói as ligações.
 */
void removerLinha(Planilha *p, int linhaParaRemover) {
    if(!p || !p->matriz) return;
    if(linhaParaRemover < 1 || linhaParaRemover > p->linhas) {
        printf("Linha invalida (%d).\n", linhaParaRemover);
        return;
    }

    free(p->matriz[linhaParaRemover - 1]);

    // "Puxa" as linhas de baixo para cima
    for(int i = linhaParaRemover - 1; i < p->linhas - 1; i++) {
        p->matriz[i] = p->matriz[i + 1];
    }

    p->linhas--;

    // Se p->linhas == 0, poderíamos zerar p->matriz, etc.  
    // Mas para simplicidade, deixamos como está.  

    // Refaz as ligações
    reconstruirLigacoes(p);
}

/**
 * Remove a coluna "colunaParaRemover" e faz as colunas à direita serem deslocadas.
 *  1) Para cada linha, cria-se um novo array com (colunas-1) células.
 *  2) Copia as células antigas, exceto a coluna removida.
 *  3) Libera o array antigo.
 *  4) Substitui a linha pelo novo array.
 *  5) Decrementa p->colunas.
 *  6) Reconstrói as ligações.
 */
void removerColuna(Planilha *p, int colunaParaRemover) {
    if(!p || !p->matriz) return;
    if(colunaParaRemover < 1 || colunaParaRemover > p->colunas) {
        printf("Coluna invalida (%d).\n", colunaParaRemover);
        return;
    }

    for(int i = 0; i < p->linhas; i++) {
        // Aloca um novo array com (p->colunas - 1) células
        Celula *novaLinha = (Celula*) malloc((p->colunas - 1) * sizeof(Celula));

        // Copia, pulando a coluna removida
        int idxNova = 0;
        for(int j = 0; j < p->colunas; j++) {
            if(j == (colunaParaRemover - 1)) {
                continue; // pula a coluna
            }
            novaLinha[idxNova] = p->matriz[i][j];
            idxNova++;
        }

        // Libera a linha antiga
        free(p->matriz[i]);
        // Substitui
        p->matriz[i] = novaLinha;
    }

    p->colunas--;

    // Reconstrói as ligações
    reconstruirLigacoes(p);
}


// Função principal de exemplo
int main() {
    int opcao, lin, col, valor;

    // Cria uma planilha 5x5
    Planilha *plan = criarPlanilha(5, 5);
    if(!plan) {
        printf("Erro ao criar planilha.\n");
        return 1;
    }

    while(1) {
        printf("Menu:\n");
        printf("1 - Inserir valor em (linha, coluna)\n");
        printf("2 - Remover linha\n");
        printf("3 - Remover coluna\n");
        printf("4 - Imprimir planilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite: linha coluna valor -> ");
                scanf("%d %d %d", &lin, &col, &valor);
                definirValor(plan, lin, col, valor);
                break;

            case 2:
                printf("Digite o numero da linha a remover: ");
                scanf("%d", &lin);
                removerLinha(plan, lin);
                break;

            case 3:
                printf("Digite o numero da coluna a remover: ");
                scanf("%d", &col);
                removerColuna(plan, col);
                break;

            case 4:
                imprimirPlanilha(plan);
                break;

            case 0:
                printf("Saindo...\n");
                liberarPlanilha(plan);
                return 0;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    return 0;
}
