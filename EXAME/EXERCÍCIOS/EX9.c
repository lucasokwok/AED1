/*
🔹 9. Verificar se Duas Árvores Genéricas São Iguais
📌 Enunciado:
Implemente a função arvoresIguais(No *raiz1, No *raiz2), que verifica se duas árvores genéricas possuem 
a mesma estrutura e os mesmos valores.

📌 Conceitos envolvidos:

Árvores genéricas (com múltiplos filhos).
Recursão.
Comparação de estruturas de dados dinâmicas.

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int info;
    No* primeiroFilho;
    No* proxIrmao;
} No;

typedef struct Arvore{
    No* raiz;
} Arvore;

int arvoresIguais(No *raiz1, No *raiz2) {
    if (!raiz1 && !raiz2) return 1; // Ambas são nulas → iguais
    if (!raiz1 || !raiz2) return 0; // Apenas uma nula → diferentes
    if (raiz1->info != raiz2->info) return 0; // Valores diferentes

    return arvoresIguais(raiz1->primeiroFilho, raiz2->primeiroFilho) &&
           arvoresIguais(raiz1->proxIrmao, raiz2->proxIrmao);
}



