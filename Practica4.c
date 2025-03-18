#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int calcularQuimica(int* habilidades, int total) {
    qsort(habilidades, total, sizeof(int), comparar);

    int sumaObjetivo = habilidades[0] + habilidades[total - 1];
    int quimicaTotal = 0;

    for (int i = 0, j = total - 1; i < j; i++, j--) {
        int sumaEquipo = habilidades[i] + habilidades[j];

        if (sumaEquipo != sumaObjetivo) {
            return -1;
        }

        quimicaTotal += habilidades[i] * habilidades[j];
    }

    return quimicaTotal;
}

int main() {
    int habilidades[100];
    int totalJugadores = 0;
    char entrada[256];

    printf("Ingrese las habilidades de los jugadores:\n");

    fgets(entrada, sizeof(entrada), stdin);

    char *token = strtok(entrada, " \n");
    while (token != NULL) {
        habilidades[totalJugadores++] = atoi(token);
        token = strtok(NULL, " \n");
    }

    if (totalJugadores % 2 != 0) {
        printf("-1\n");
        return 0;
    }

    printf("%d\n", calcularQuimica(habilidades, totalJugadores));

    return 0;
}

   