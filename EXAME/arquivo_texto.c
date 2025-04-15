#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura para manipulação de arquivos de texto */
// não é NECESSÁRIO criar uma struct para arquivos
typedef struct {
    FILE *arquivo;
    char nome[100];
    char modo[3];
} ArquivoTexto;

/* Abre um arquivo em modo texto */
ArquivoTexto* abrirArquivoTexto(const char *nome, const char *modo) {
    ArquivoTexto *arq = (ArquivoTexto*)malloc(sizeof(ArquivoTexto));
    fprintf(stdout, "Abrindo arquivo: %s\n", nome);
    
    arq->arquivo = fopen(nome, modo);
    if (arq->arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", nome);
        free(arq);
        return NULL;
    }
    return arq;
}

/* Fecha um arquivo */
void fecharArquivoTexto(ArquivoTexto *arq) {
    if (arq->arquivo != NULL) {
        fclose(arq->arquivo);
    }
    free(arq);
}

/* Lê uma linha do arquivo */
int lerLinha(ArquivoTexto *arq, char *buffer, int tamanho) {
    if (arq->arquivo != NULL) {
        return fgets(buffer, tamanho, arq->arquivo) != NULL;
    }
    return 0;
}

/* Lê um caractere do arquivo */
int lerCaractere(ArquivoTexto *arq) {
    if (arq->arquivo != NULL) {
        return fgetc(arq->arquivo);
    }
    return EOF;
}

/* Escreve uma linha no arquivo */
void escreverLinha(ArquivoTexto *arq, const char *linha) {
    if (arq->arquivo != NULL) {
        fprintf(arq->arquivo, "%s\n", linha);
    }
}

/* Escreve um caractere no arquivo */
void escreverCaractere(ArquivoTexto *arq, char c) {
    if (arq->arquivo != NULL) {
        fputc(c, arq->arquivo);
    }
}

/* Procura uma palavra-chave dentro de um arquivo */
int procurarPalavraChave(ArquivoTexto *arq, const char *chave) {
    char linha[256];
    while (lerLinha(arq, linha, sizeof(linha))) {
        if (strstr(linha, chave) != NULL) {
            return 1; // Palavra encontrada
        }
    }
    return 0;
}

/* Acesso via fseek e rewind */
void acessarPosicaoArquivo(ArquivoTexto *arq, long posicao) {
    fseek(arq->arquivo, posicao, SEEK_SET);
}

void voltarAoInicio(ArquivoTexto *arq) {
    rewind(arq->arquivo);
}

/* Exemplo de uso */
int main() {
    ArquivoTexto *arq = abrirArquivoTexto("exemplo.txt", "w+");
    if (!arq) return 1;

    escreverLinha(arq, "Linha 1: Olá, Mundo!");
    escreverLinha(arq, "Linha 2: Teste de escrita.");
    escreverLinha(arq, "Linha 3: C é uma linguagem poderosa.");

    voltarAoInicio(arq);
    
    char linha[256];
    printf("Conteúdo do arquivo:\n");
    while (lerLinha(arq, linha, sizeof(linha))) {
        printf("%s", linha);
    }

    fecharArquivoTexto(arq);
    return 0;
}
