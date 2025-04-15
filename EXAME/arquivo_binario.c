#include <stdio.h>
#include <stdlib.h>

/* Estrutura para representar um registro */
typedef struct {
    int id;
    char nome[50];
    float nota;
} Registro;

/* Estrutura para manipulação de arquivos binários */
typedef struct {
    FILE *arquivo;
    char nome[100];
    char modo[3]; 
} ArquivoBinario;

/* Abre um arquivo binário */
ArquivoBinario* abrirArquivoBinario(const char *nome, const char *modo) {
    ArquivoBinario *arq = (ArquivoBinario*)malloc(sizeof(ArquivoBinario));
    fprintf(stdout, "Abrindo arquivo binário: %s\n", nome);
    
    arq->arquivo = fopen(nome, modo);
    if (arq->arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo binário: %s\n", nome);
        free(arq);
        return NULL;
    }
    return arq;
}

/* Fecha um arquivo binário */
void fecharArquivoBinario(ArquivoBinario *arq) {
    if (arq->arquivo != NULL) {
        fclose(arq->arquivo);
    }
    free(arq);
}

/* Escreve um registro no arquivo binário */
void escreverRegistro(ArquivoBinario *arq, Registro *reg) {
    if (arq->arquivo != NULL) {
        fwrite(reg, sizeof(Registro), 1, arq->arquivo);
    }
}

/* Lê um registro do arquivo binário */
int lerRegistro(ArquivoBinario *arq, Registro *reg) {
    if (arq->arquivo != NULL) {
        return fread(reg, sizeof(Registro), 1, arq->arquivo);
    }
    return 0;
}

/* Usa fseek para acessar posição específica */
void acessarRegistro(ArquivoBinario *arq, int indice) {
    fseek(arq->arquivo, indice * sizeof(Registro), SEEK_SET);
}

/* Exemplo de uso */
int main() {
    ArquivoBinario *arq = abrirArquivoBinario("dados.bin", "wb+");
    if (!arq) return 1;

    Registro r1 = {1, "Alice", 9.5};
    Registro r2 = {2, "Bob", 8.7};

    escreverRegistro(arq, &r1);
    escreverRegistro(arq, &r2);

    rewind(arq->arquivo); // Retorna ao início do arquivo

    Registro lido;
    printf("Registros no arquivo:\n");
    while (lerRegistro(arq, &lido)) {
        printf("ID: %d, Nome: %s, Nota: %.2f\n", lido.id, lido.nome, lido.nota);
    }

    fecharArquivoBinario(arq);
    return 0;
}
