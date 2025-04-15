/*
🔹 10. Contar o Número de Amigos em Comum
📌 Objetivo: Contar o número de amigos em comum de um usuário e seus amigos em um grafo representando uma rede social.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_USUARIOS 100

// Estrutura do Grafo (Matriz de Adjacência)
typedef struct Grafo {
    int matriz[MAX_USUARIOS][MAX_USUARIOS];
    int n;
} Grafo;

// Função para contar amigos em comum
int contarAmigosEmComum(Grafo *g, int usuario) {
    int comum = 0;

    for (int amigo1 = 0; amigo1 < g->n; amigo1++) {
        if (g->matriz[usuario][amigo1]) { // Se amigo1 é amigo do usuário
            for (int amigo2 = amigo1 + 1; amigo2 < g->n; amigo2++) {
                if (g->matriz[usuario][amigo2] && g->matriz[amigo1][amigo2]) {
                    comum++; // amigo1 e amigo2 são amigos em comum
                }
            }
        }
    }

    return comum;
}
