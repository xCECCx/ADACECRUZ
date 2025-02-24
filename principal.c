#include <stdio.h>
#include <stdbool.h>

// Función que determina si un número es palíndromo
bool esPalindromo(int numero) {
    // Si el número es negativo, no se considera palíndromo
    if (numero < 0) {
        return false;
    }
    
    int original = numero;
    int reverso = 0;

    // Se invierte el número
    while (numero > 0) {
        int digito = numero % 10;
        reverso = reverso * 10 + digito;
        numero /= 10;
    }
    
    // Si el número original es igual al reverso, es palíndromo
    return (original == reverso);
}

int main() {
    int num;
    
    printf("Ingresa un número entero: ");
    scanf("%d", &num);
    
    if (esPalindromo(num)) {
        printf("El número %d es palíndromo.\n", num);
    } else {
        printf("El número %d no es palíndromo.\n", num);
    }
    
    return 0;
}
