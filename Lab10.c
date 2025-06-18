#include <stdio.h>

#define NUM_OBJETOS 4
#define PESO_MAXIMO 4

int main() {
    int pesos[NUM_OBJETOS] = {1, 1, 3, 4};     // iPhone, guitarra, laptop, estéreo
    int valores[NUM_OBJETOS] = {2000, 1500, 2000, 3000};
    char* nombres[NUM_OBJETOS] = {"iPhone", "Guitarra", "Laptop", "Estéreo"};

    int dp[NUM_OBJETOS + 1][PESO_MAXIMO + 1];

    // Llenamos la tabla DP
    for (int i = 0; i <= NUM_OBJETOS; i++) {
        for (int w = 0; w <= PESO_MAXIMO; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (pesos[i - 1] <= w) {
                int incluir = valores[i - 1] + dp[i - 1][w - pesos[i - 1]];
                int excluir = dp[i - 1][w];
                dp[i][w] = (incluir > excluir) ? incluir : excluir;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Resultado óptimo
    printf("Valor máximo en la mochila: $%d\n", dp[NUM_OBJETOS][PESO_MAXIMO]);

    // Determinar qué objetos se incluyeron
    int w = PESO_MAXIMO;
    printf("Objetos seleccionados:\n");
    for (int i = NUM_OBJETOS; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            printf("- %s\n", nombres[i - 1]);
            w -= pesos[i - 1];
        }
    }

    return 0;
}

