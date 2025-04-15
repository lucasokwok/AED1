#include <stdio.h>

int main() {
    int x = 42;
    int *ptr = &x;
    int **ptr2 = &ptr;

    printf("Valor de x: %d\n", x);      // 42
    printf("Valor de x via *ptr: %d\n", *ptr); // 42
    printf("Valor de x via **ptr2: %d\n", **ptr2); // 42

    return 0;
}
