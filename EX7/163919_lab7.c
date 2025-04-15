//Atividade 7 AED1 2024 Prof Luis
//Lucas de Oliveira Kwok 163919
 
#include <stdio.h>
#include <stdlib.h>

int buscaBinaria(int *lista, int inicio, int fim, int x) {
    if (inicio >= fim) { 
        return -1;
    }

    int meio = (inicio + fim) / 2;

    if (lista[meio] < x && x < lista[meio + 1]) {
        return meio;
    }

    if (x < lista[meio]) {
        return buscaBinaria(lista, inicio, meio, x);
    }

    return buscaBinaria(lista, meio + 1, fim, x);
}


int main() {
    int x, n;

    scanf("%d %d", &x, &n);

    int *lista = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &lista[i]);
    }

    int resultado = buscaBinaria(lista, 0, n - 1, x);

    if (resultado != -1 && resultado + 1 < n) 
        printf("%d %d\n", lista[resultado], lista[resultado + 1]);
    else 
        printf("nao ha intervalo valido\n");

    free(lista);
    return 0;
}
