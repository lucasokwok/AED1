#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para uma célula da planilha
typedef struct Cell {
    char content[50];  // Conteúdo da célula
    int row, col;      // Coordenadas da célula
    struct Cell *up, *down, *left, *right;  // Ponteiros para células vizinhas
} Cell;

// Função para criar uma nova célula
Cell* createCell(char* content, int row, int col) {
    Cell* newCell = (Cell*)malloc(sizeof(Cell));
    if (!newCell) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    strcpy(newCell->content, content);
    newCell->row = row;
    newCell->col = col;
    newCell->up = newCell->down = newCell->left = newCell->right = NULL;
    return newCell;
}

// Função para inserir uma célula na matriz
void insertCell(Cell*** grid, int rows, int cols, char* content, int row, int col) {
    if (row >= rows || col >= cols) {
        printf("Posição (%d, %d) fora dos limites.\n", row, col);
        return;
    }

    grid[row][col] = createCell(content, row, col);

    // Ajustando os ponteiros das células vizinhas
    if (row > 0 && grid[row - 1][col]) {
        grid[row][col]->up = grid[row - 1][col];
        grid[row - 1][col]->down = grid[row][col];
    }
    if (col > 0 && grid[row][col - 1]) {
        grid[row][col]->left = grid[row][col - 1];
        grid[row][col - 1]->right = grid[row][col];
    }
}

// Função para exibir a planilha
void displaySheet(Cell*** grid, int rows, int cols) {
    printf("\nPlanilha:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j]) {
                printf("[%s (%d,%d)] ", grid[i][j]->content, grid[i][j]->row, grid[i][j]->col);
            } else {
                printf("[empty] ");
            }
        }
        printf("\n");
    }
}

// Função para liberar a memória alocada
void freeSheet(Cell*** grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j]) {
                free(grid[i][j]);
            }
        }
        free(grid[i]);
    }
    free(grid);
}

int main() {
    int rows, cols;

    printf("Digite o número de linhas e colunas: ");
    scanf("%d %d", &rows, &cols);

    // Alocar memória para a matriz de células
    Cell*** grid = (Cell***)malloc(rows * sizeof(Cell**));
    for (int i = 0; i < rows; i++) {
        grid[i] = (Cell**)calloc(cols, sizeof(Cell*));
    }

    int n;
    printf("Digite o número de células a serem adicionadas: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char content[50];
        int row, col;

        printf("Digite o conteúdo e a posição (linha coluna): ");
        scanf("%s %d %d", content, &row, &col);

        insertCell(grid, rows, cols, content, row, col);
    }

    displaySheet(grid, rows, cols);

    freeSheet(grid, rows, cols);

    return 0;
}
