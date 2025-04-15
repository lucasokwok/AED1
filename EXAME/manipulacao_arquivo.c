#include <stdio.h>
#include <stdlib.h>

/* 1️⃣ Copiar um arquivo binário para um arquivo texto */
void copiarBinarioParaTexto(FILE *arquivoBinario, FILE *arquivoTexto) {
    int numeros[3];  // Cada linha contém 3 inteiros
 
    while (fread(numeros, sizeof(int), 3, arquivoBinario) == 3) {
        fprintf(arquivoTexto, "%d %d %d\n", numeros[0], numeros[1], numeros[2]);
    }
}

/* 2️⃣ Copiar um arquivo texto para um arquivo binário */
void copiarTextoParaBinario(FILE *arquivoTexto, FILE *arquivoBinario) {
    int num1, num2, num3;
    char linha[256];

    fseek(arquivoTexto, 0, SEEK_SET); // Volta ao início do arquivo usando fseek

    // Lê cada linha e converte para binário
    while (fgets(linha, sizeof(linha), arquivoTexto)) {
        if (sscanf(linha, "%d %d %d", &num1, &num2, &num3) == 3) {
            int numeros[] = {num1, num2, num3};
            fwrite(numeros, sizeof(int), 3, arquivoBinario);
        }
    }
}

/* 3️⃣ Copiar um arquivo texto para outro arquivo texto */
void copiarTextoParaTexto(FILE *arquivoTextoOrigem, FILE *arquivoTextoDestino) {
    char linha[256];  // Buffer de leitura

    rewind(arquivoTextoOrigem); // Garante que a leitura começa do início

    while (fgets(linha, sizeof(linha), arquivoTextoOrigem)) {
       fprintf(arquivoTextoDestino, "%s", linha);
    }
}

/* 4️⃣ Copiar um arquivo caractere por caractere */
void copiarCaracterPorCaracter(FILE *arquivoOrigem, FILE *arquivoDestino) {
    char c;
    
    rewind(arquivoOrigem); // Garante que a leitura começa do início

    while ((c = fgetc(arquivoOrigem)) != EOF) {
        fputc(c, arquivoDestino);
    }
}

/* 5️⃣ Ler um arquivo caractere por caractere e imprimir na tela */
void lerArquivoCaracterPorCaracter(FILE *arquivo) {
    char c;

    rewind(arquivo); // Garante que a leitura começa do início

    while ((c = fgetc(arquivo)) != EOF) {
        putchar(c); // Imprime na tela
    }
}

/* 6️⃣ Buscar uma palavra-chave em um arquivo e imprimir as linhas que a contêm */
void buscarPalavraChave(FILE *arquivo, const char *palavraChave) {
    char linha[256];

    rewind(arquivo); // Garante que a leitura começa do início

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, palavraChave)) {
            printf("%s", linha); // Imprime a linha que contém a palavra-chave
        }
    }
}

/* 7️⃣ Contar quantas vezes uma palavra-chave aparece em um arquivo */
int contarPalavraChave(FILE *arquivo, const char *palavraChave) {
    char linha[256];
    int contador = 0;

    rewind(arquivo); // Garante que a leitura começa do início

    while (fgets(linha, sizeof(linha), arquivo)) {
        char *ptr = linha;
        while ((ptr = strstr(ptr, palavraChave)) != NULL) {
            contador++;
            ptr += strlen(palavraChave); // Move o ponteiro para evitar contar a mesma ocorrência
        }
    }

    return contador;
}

 char *fgets(char *buffer, int tamanho, FILE *arquivo);

 int fputs(const char *string, FILE *arquivo);

 int fprintf(FILE *arquivo, const char *formato, ...);

 size_t fread(void *buffer, size_t tamanho, size_t quantidade, FILE *arquivo);

 size_t fwrite(const void *buffer, size_t tamanho, size_t quantidade, FILE *arquivo);

 int fseek(FILE *arquivo, long deslocamento, int origem);

 void rewind(FILE *arquivo);

 char *strstr(const char *string, const char *substring);

 int fgetc(FILE *arquivo); // retorna EOF se o arquivo acabar

 int fputc(int caractere, FILE *arquivo);


