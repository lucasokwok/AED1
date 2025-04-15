#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct No {
    char nome[MAX];
    struct No* filho;
    struct No* irmao;
} No;

/* -------------------------------------------------------------
   Cria um novo nó, representando um arquivo/pasta no sistema
   ------------------------------------------------------------- */
No* criarNo(const char* nome) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        fprintf(stderr, "Erro de alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novo->nome, nome);
    novo->filho  = NULL;
    novo->irmao  = NULL;
    return novo;
}

/* -------------------------------------------------------------
   Desaloca a árvore inteira recursivamente
   ------------------------------------------------------------- */
void desalocarArvore(No* raiz) {
    if (!raiz) return;
    desalocarArvore(raiz->filho);
    desalocarArvore(raiz->irmao);
    free(raiz);
}

/* -------------------------------------------------------------
   Busca (DFS) um nó de nome "nomeBuscado" na (sub)árvore "raiz".
   Retorna o ponteiro para o nó se encontrar, ou NULL caso não exista.
   ------------------------------------------------------------- */
No* buscaNo(No* raiz, const char* nomeBuscado) {
    if (!raiz) return NULL;
    
    // Se o nó atual tiver o nome procurado, retorna imediatamente
    if (strcmp(raiz->nome, nomeBuscado) == 0) {
        return raiz;
    }
    // Tenta achar nos filhos
    No* encontrado = buscaNo(raiz->filho, nomeBuscado);
    if (encontrado) {
        return encontrado;
    }
    // Se não achou nos filhos, tenta nos irmãos
    return buscaNo(raiz->irmao, nomeBuscado);
}

/* -------------------------------------------------------------
   Busca o PAI de um nó que tenha o nome "nomeFilho".
   Se achar, retorna o ponteiro para o nó pai; senão, retorna NULL.
   ------------------------------------------------------------- */
No* buscaPai(No* raiz, const char* nomeFilho) {
    if (!raiz || !raiz->filho) 
        return NULL;

    // Verifica se algum dos filhos diretos de "raiz" é o que queremos
    No* filho = raiz->filho;
    while (filho) {
        if (strcmp(filho->nome, nomeFilho) == 0) {
            return raiz; // o "raiz" atual é o pai
        }
        filho = filho->irmao;
    }

    // Se não achamos como filho direto, procuramos recursivamente
    // no primeiro filho e em seguida nos irmãos
    No* encontrado = buscaPai(raiz->filho, nomeFilho);
    if (encontrado) 
        return encontrado;

    return buscaPai(raiz->irmao, nomeFilho);
}

/* -------------------------------------------------------------
   Insere um novo nó "nomeNovo" como FILHO do nó de nome "nomePai".
   Se não achar o pai, não faz nada.
   ------------------------------------------------------------- */
void insereNo(No* raiz, const char* nomeNovo, const char* nomePai) {
    if (!raiz) return;

    // Busca o nó que será o pai do novo
    No* pai = buscaNo(raiz, nomePai);
    if (!pai) {
        // pai não encontrado, não insere
        return;
    }
    
    // Cria o novo nó
    No* novo = criarNo(nomeNovo);

    // Insere no início da lista de filhos do "pai"
    novo->irmao = pai->filho;
    pai->filho  = novo;
}

/* -------------------------------------------------------------
   Remove o nó de nome "arquivo" (se for encontrado) da árvore.
   Observação: o enunciado foca em "remover arquivos", mas aqui
   remove qualquer nó que tenha esse nome.
   - Desaloca também todo o "subdiretório" daquele nó.
   ------------------------------------------------------------- */
void removeNo(No* raiz, const char* nomeRemover) {
    if (!raiz) return;

    // Encontra o PAI do nó que será removido
    No* pai = buscaPai(raiz, nomeRemover);
    if (!pai) {
        // Não encontrado ou nó é a raiz
        return;
    }

    // Percorre a lista de filhos do "pai" para achar "nomeRemover"
    No* anterior = NULL;
    No* atual = pai->filho;
    while (atual) {
        if (strcmp(atual->nome, nomeRemover) == 0) {
            // Achou o nó a remover
            if (!anterior) {
                // Era o primeiro filho do pai
                pai->filho = atual->irmao;
            } else {
                anterior->irmao = atual->irmao;
            }
            // Libera a subárvore do nó removido
            desalocarArvore(atual);
            return;
        }
        anterior = atual;
        atual = atual->irmao;
    }
}

/* -------------------------------------------------------------
   Move o nó de nome "nomeArquivo" para dentro de "nomeDestino".
   1) Busca o nó a mover e seu pai.
   2) Remove-o da lista de filhos do pai.
   3) Insere-o como filho do "nomeDestino".
   ------------------------------------------------------------- */
void moverNo(No* raiz, const char* nomeArquivo, const char* nomeDestino) {
    if (!raiz) return;

    // Acha o nó que será movido
    No* node = buscaNo(raiz, nomeArquivo);
    if (!node) {
        // Não existe
        return;
    }

    // Acha o pai do nó que será movido
    No* paiAntigo = buscaPai(raiz, nomeArquivo);
    if (!paiAntigo) {
        // Nó é a raiz ou não existe pai
        return;
    }

    // "Desencaixa" o node da lista de filhos do pai
    No* anterior = NULL;
    No* atual = paiAntigo->filho;
    while (atual) {
        if (atual == node) {
            // Remove da corrente
            if (!anterior) {
                paiAntigo->filho = atual->irmao;
            } else {
                anterior->irmao = atual->irmao;
            }
            node->irmao = NULL; 
            break;
        }
        anterior = atual;
        atual = atual->irmao;
    }

    // Agora busca o novo pai (pasta destino)
    No* novoPai = buscaNo(raiz, nomeDestino);
    if (!novoPai) {
        // Se não encontrou o destino, não perde o node (reinsere no pai antigo, por exemplo)
        // Mas, conforme o enunciado, se não achou a pasta de destino, não move.
        // Vamos simplesmente recolocá-lo no pai antigo:
        node->irmao = paiAntigo->filho;
        paiAntigo->filho = node;
        return;
    }

    // Insere node como primeiro filho do novo pai
    node->irmao = novoPai->filho;
    novoPai->filho = node;
}

/* -------------------------------------------------------------
   Imprime o caminho do arquivo em ordem inversa (arquivo <- ... <- root).
   Retorna 1 se encontrar, 0 se não encontrar.
   ------------------------------------------------------------- */
int printCaminho(No* raiz, const char* nomeBuscado) {
    if (!raiz) return 0;

    // Se o nó atual for o buscado, imprime e retorna sucesso
    if (strcmp(raiz->nome, nomeBuscado) == 0) {
        printf("%s", raiz->nome);
        return 1;
    }
    // Tenta achar nos filhos
    if (printCaminho(raiz->filho, nomeBuscado)) {
        // Se um filho encontrou, imprime o "raiz->nome" ao voltar
        printf("<-%s", raiz->nome);
        return 1;
    }
    // Se não achou nos filhos, procura nos irmãos
    if (printCaminho(raiz->irmao, nomeBuscado)) {
        return 1;
    }

    return 0;
}

/* -------------------------------------------------------------
   Função principal
   ------------------------------------------------------------- */
int main() {
    int n;
    char linha[100];
    char operacao[3], nome1[MAX], nome2[MAX];

    // Cria a raiz (pasta root)
    No* raiz = criarNo("root");

    // Lê a quantidade de operações
    if (!fgets(linha, sizeof(linha), stdin)) return 0;
    sscanf(linha, "%d", &n);

    for (int i = 0; i < n; i++) {
        if (!fgets(linha, sizeof(linha), stdin)) break;

        // Cada linha pode ser:
        //  -i arquivoOuPasta pastaDeInsercao
        //  -m arquivo pastaDestino
        //  -r arquivo
        // Formato: "<operacao> <nome1> <nome2?>"
        // Usando %s %s %s, nome2 só será válido se a operação for -i ou -m
        // Caso seja -r, nome2 não é usado (mas é lido).
        // Então parseamos com atenção ao tipo da operação.
        int qtd = sscanf(linha, "%s %s %s", operacao, nome1, nome2);

        if (strcmp(operacao, "-i") == 0 && qtd == 3) {
            // Inserir
            insereNo(raiz, nome1, nome2);
        }
        else if (strcmp(operacao, "-m") == 0 && qtd == 3) {
            // Mover
            moverNo(raiz, nome1, nome2);
        }
        else if (strcmp(operacao, "-r") == 0 && qtd >= 2) {
            // Remover
            removeNo(raiz, nome1);
        }
        // Se a linha for inválida, simplesmente ignora
    }

    // A última linha contém o nome de um arquivo a ser buscado
    if (!fgets(linha, sizeof(linha), stdin)) {
        // Encerrar sem busca
        desalocarArvore(raiz);
        return 0;
    }
    sscanf(linha, "%s", nome1);

    // Imprime o caminho se existir
    if (!printCaminho(raiz, nome1)) {
        printf("Arquivo nao encontrado");
    }
    printf("\n");

    // Libera toda a memória
    desalocarArvore(raiz);
    return 0;
}
