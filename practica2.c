#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX; // Manejo de desbordamiento
    }
    
    int signo = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1; // Determinar el signo del resultado
    
    long long dividendoAbs = llabs((long long)dividend);
    long long divisorAbs = llabs((long long)divisor);
    long long cociente = 0;
    
    while (dividendoAbs >= divisorAbs) {
        long long temp = divisorAbs, factor = 1;
        while (dividendoAbs >= (temp << 1)) {
            temp <<= 1;
            factor <<= 1;
        }
        dividendoAbs -= temp;
        cociente += factor;
    }
    
    return signo * cociente;
}

int main() {
    int dividendo, divisor;
    printf("Ingrese el dividendo: ");
    scanf("%d", &dividendo);
    printf("Ingrese el divisor: ");
    scanf("%d", &divisor);
    
    if (divisor == 0) {
        printf("Error: División por cero no permitida.\n");
        return 1;
    }
    
    int resultado = divide(dividendo, divisor);
    printf("Resultado: %d\n", resultado);
    
    return 0;
}

