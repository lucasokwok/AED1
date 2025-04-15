/*
-----------------------------------------------------------------------------------
      COMO PASSAR INSTRUÇÕES ATRAVÉS DOS PARÂMETROS DA MAIN EM C
-----------------------------------------------------------------------------------

 EM C, PODEMOS PASSAR ARGUMENTOS PARA UM PROGRAMA ATRAVÉS DA LINHA DE COMANDO. 
 ISSO PERMITE QUE O PROGRAMA RECEBA ENTRADAS SEM A NECESSIDADE DE INTERAÇÃO
 DIRETA DO USUÁRIO DURANTE A EXECUÇÃO.

-----------------------------------------------------------------------------------
   SINTAXE DA MAIN COM PARÂMETROS
-----------------------------------------------------------------------------------

 int main(int argc, char *argv[]) {
      // argc: Número de argumentos passados na execução
      // argv: Vetor de strings contendo os argumentos
 }

-----------------------------------------------------------------------------------
   DETALHAMENTO DOS PARÂMETROS
-----------------------------------------------------------------------------------

 ✅ argc (Argument Count) → Indica quantos argumentos foram passados na linha de comando.
 ✅ argv (Argument Vector) → Vetor de strings contendo os argumentos passados.

   ➤ argv[0] → Nome do programa executado
   ➤ argv[1] → Primeiro argumento passado na linha de comando
   ➤ argv[2] → Segundo argumento (se houver) e assim por diante...

-----------------------------------------------------------------------------------
   EXEMPLO DE USO BÁSICO
-----------------------------------------------------------------------------------

 #include <stdio.h>

 int main(int argc, char *argv[]) {
     printf("Número de argumentos: %d\n", argc);
     
     for (int i = 0; i < argc; i++) {
         printf("Argumento %d: %s\n", i, argv[i]);
     }
     return 0;
 }

   ➤ Se compilarmos este programa como `./programa`
   ➤ E executarmos `./programa teste 123 arquivo.txt`

   SAÍDA NO TERMINAL:
   Número de argumentos: 4
   Argumento 0: ./programa
   Argumento 1: teste
   Argumento 2: 123
   Argumento 3: arquivo.txt

-----------------------------------------------------------------------------------
   TRATAMENTO DE ERROS AO RECEBER ARGUMENTOS
-----------------------------------------------------------------------------------

 #include <stdio.h>
 #include <stdlib.h>

 int main(int argc, char *argv[]) {
     if (argc < 3) {
         printf("Uso correto: %s <parametro1> <parametro2>\n", argv[0]);
         return 1;
     }
     printf("Parâmetro 1: %s\n", argv[1]);
     printf("Parâmetro 2: %s\n", argv[2]);
     return 0;
 }

   ➤ Se executarmos `./programa` sem argumentos, teremos:
     "Uso correto: ./programa <parametro1> <parametro2>"
   ➤ Se executarmos `./programa ABC 123`, teremos:
     "Parâmetro 1: ABC"
     "Parâmetro 2: 123"

-----------------------------------------------------------------------------------
   CONVERTENDO ARGUMENTOS PARA TIPOS NUMÉRICOS
-----------------------------------------------------------------------------------

 #include <stdio.h>
 #include <stdlib.h>

 int main(int argc, char *argv[]) {
     if (argc != 3) {
         printf("Uso correto: %s <numero1> <numero2>\n", argv[0]);
         return 1;
     }
     
     int num1 = atoi(argv[1]);
     int num2 = atoi(argv[2]);
     int soma = num1 + num2;
     
     printf("Soma: %d\n", soma);
     return 0;
 }

   ➤ `./programa 10 20` retorna "Soma: 30"

-----------------------------------------------------------------------------------
   BOAS PRÁTICAS
-----------------------------------------------------------------------------------

 ✅ Sempre verifique `argc` antes de acessar `argv[]` para evitar acessos inválidos.
 ✅ Converta argumentos para números usando `atoi()` ou `strtol()` quando necessário.
 ✅ Exiba mensagens de erro claras quando os argumentos forem insuficientes ou inválidos.
 ✅ Use `sprintf()` ou `snprintf()` para construir strings dinâmicas com base nos argumentos.

-----------------------------------------------------------------------------------
*/
