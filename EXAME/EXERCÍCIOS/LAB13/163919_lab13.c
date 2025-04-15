#include <stdio.h>
#include <stdlib.h>

#define TAM_BUFFER 1024

/*
-----------------------------------------------------------------------------------
 PROGRAMA PARA MANIPULAÇÃO DE ARQUIVOS BINÁRIOS E DE TEXTO EM C
-----------------------------------------------------------------------------------
 DESCRIÇÃO:
 Implementar um programa em C que manipule arquivos binários e de texto, realizando 
 conversões entre esses formatos e aplicando operações de leitura e escrita sem 
 reabrir os arquivos.

 O programa deve receber como entrada, via linha de comando, **quatro nomes de arquivos**:
 
 1️⃣ entrada.bin  -> Arquivo binário contendo n linhas, cada uma com 3 inteiros.
 2️⃣ saida.txt    -> Arquivo de texto inicialmente vazio.
 3️⃣ entrada.txt  -> Arquivo de texto contendo n linhas, cada uma com 3 inteiros 
                     separados por um espaço em branco.
 4️⃣ saida.bin    -> Arquivo binário inicialmente vazio.

-----------------------------------------------------------------------------------
 REQUISITOS:
 O programa deve seguir **exatamente** as seguintes etapas:

 1️⃣ Ler os números do arquivo `entrada.bin` e escrever na **mesma ordem** no arquivo 
    `saida.txt`, separando-os por espaço e adicionando uma quebra de linha ao final 
    de cada conjunto de 3 inteiros.

 2️⃣ **Sem reabrir** o arquivo `saida.txt`, adicionar o seu conteúdo ao final de 
    `entrada.txt`, mantendo o formato original (**3 inteiros por linha, separados 
    por espaço**).

 3️⃣ **Sem reabrir** o arquivo `entrada.txt`, copiar todo o seu conteúdo para o 
    arquivo `saida.bin`.

-----------------------------------------------------------------------------------
 CONDIÇÕES IMPORTANTES:

 ✅ O número de parâmetros deve ser verificado e os arquivos devem ser corretamente 
    abertos antes da manipulação.

 ✅ O número de linhas **não é informado previamente**, logo, **não pode ser usado n**.

 ✅ Nenhum arquivo pode ser aberto, fechado e aberto novamente.

 ✅ Um arquivo deve **ser lido de uma vez só**, armazenando o conteúdo em buffer 
    antes de ser fechado.

 ✅ **NÃO utilizar as funções** `fgetc`, `fputc`, `fputs`.

 ✅ As funções `fgets` e `rewind` devem ser obrigatoriamente usadas **uma única vez**.

-----------------------------------------------------------------------------------
 EXEMPLO DE CONTEÚDO DO ARQUIVO `entrada.bin` EM ASCII PARA REFERÊNCIA:

    011
    411
    001
    431
    143

-----------------------------------------------------------------------------------
*/

//fopen(NOME DO ARQUIVO, TIPO)

   /*
   -----------------------------------------------------------------------------------
   MODOS DE ABERTURA DE ARQUIVOS EM C
   -----------------------------------------------------------------------------------

   r  -> read    : Indica modo para leitura;
   w  -> write   : Indica modo para escrita;
   a  -> append  : Indica modo para escrita ao final do existente;
   t  -> text    : Indica modo texto;
   b  -> binary  : Indica modo binário.

   -----------------------------------------------------------------------------------
   */

void copiarBinarioParaTexto(FILE *arquivoBinario, FILE *arquivoTexto) {
   int numeros[3];  // Cada linha contém 3 inteiros

   // fread(void *buffer, size_t tamanho_elemento, size_t quantidade, FILE *arquivo);

   while (fread(numeros, sizeof(int), 3, arquivoBinario) == 3) {
       fprintf(arquivoTexto, "%d %d %d\n", numeros[0], numeros[1], numeros[2]);
   }
}

void copiarTextoParaBinario(FILE *arquivoTexto, FILE *arquivoBinario, char *buffer) {
   int num1, num2, num3;
   //rewind é necessário só se o arquivo ja foi lido antes
   rewind(arquivoTexto); // O rewind não aparece mais de uma vez no código
   //esse buffer ta estranho? deveria ser o arquivo eu aacho
   while (sscanf(arquivoTexto, "%d %d %d", &num1, &num2, &num3) == 3) {
       int numeros[] = {num1, num2, num3};
       fwrite(numeros, sizeof(int), 3, arquivoBinario);
   }
}

void copiarTextoParaTexto(FILE *arquivoTextoOrigem, FILE *arquivoTextoDestino, char *buffer) {
   int num1, num2, num3;

   fseek(arquivoTextoOrigem, 0, SEEK_SET);
   while (fgets(buffer, sizeof(buffer), arquivoTextoOrigem)) {
      fprintf(arquivoTextoDestino, "%s", buffer);
   }
}

int main(int argc, char *argv[]) {

   // Atribuição dos arquivos passados via linha de comando
   char *arquivoEntradaBin = argv[1]; // entrada.bin
   char *arquivoSaidaTxt   = argv[2]; // saida.txt
   char *arquivoEntradaTxt = argv[3]; // entrada.txt
   char *arquivoSaidaBin   = argv[4]; // saida.bin

   // Abertura de todos os arquivos necessários
   FILE *entradaBin = fopen(arquivoEntradaBin, "rb");
   FILE *saidaTxt   = fopen(arquivoSaidaTxt, "w");
   FILE *entradaTxt = fopen(arquivoEntradaTxt, "a+"); // Abre para leitura e escrita sem apagar o conteúdo
   FILE *saidaBin   = fopen(arquivoSaidaBin, "wb");

   // Buffer para armazenar as linhas lidas
   char buffer[TAM_BUFFER];

   // ------------------ Etapa 1: Ler entrada.bin e escrever em saida.txt ------------------
   copiarBinarioParaTexto(entradaBin, saidaTxt);
   fclose(entradaBin);  // Fecha entrada.bin após uso

   copiarTextoParaTexto(saidaTxt, entradaTxt, buffer);
   fclose(saidaTxt); // Fecha saida.txt após leitura

   // ------------------ Etapa 3: Copiar entrada.txt para saida.bin ------------------
   copiarTextoParaBinario(entradaTxt, saidaBin, buffer);

   // Fechar os arquivos finais
   fclose(entradaTxt);
   fclose(saidaBin);

   printf("Processo concluído com sucesso!\n");
   return 0;
}
