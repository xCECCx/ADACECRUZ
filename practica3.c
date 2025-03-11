#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void backtrack(char* digits, int index, char* current, char** result, int* returnSize) {
    // Mapeo de dígitos a letras
    char* mapping[] = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    // Caso base: si hemos llegado al final del dígito
    if (index == strlen(digits)) {
        result[*returnSize] = (char*)malloc(strlen(current) + 1);
        strcpy(result[*returnSize], current);
        (*returnSize)++;
        return;
    }

    int digit = digits[index] - '0'; // Obtener el dígito correspondiente
    char* letters = mapping[digit]; // Obtener las letras correspondientes a ese dígito

    // Recursión para generar todas las combinaciones
    for (int i = 0; i < strlen(letters); i++) {
        current[index] = letters[i]; // Asignar la letra actual
        backtrack(digits, index + 1, current, result, returnSize); // Llamada recursiva
    }
}

char** letterCombinations(char* digits, int* returnSize) {
    if (digits == NULL || strlen(digits) == 0) {
        *returnSize = 0;
        return NULL;
    }

    int maxCombinations = 1;
    for (int i = 0; i < strlen(digits); i++) {
        int digit = digits[i] - '0';
        maxCombinations *= strlen("abc def ghi jkl mno pqrs tuv wxyz" + (digit - 2) * 4);
    }

    char** result = (char**)malloc(maxCombinations * sizeof(char*));
    char current[strlen(digits) + 1];
    current[strlen(digits)] = '\0';

    *returnSize = 0;
    backtrack(digits, 0, current, result, returnSize);

    return result;
}

int main() {
    char digits[5];
    printf("Ingrese los dígitos (de 2 a 9): ");
    scanf("%s", digits);

    int returnSize = 0;
    char** result = letterCombinations(digits, &returnSize);

    printf("Combinaciones posibles:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", result[i]);
        free(result[i]); // Liberar memoria
    }
    free(result); // Liberar memoria

    return 0;
}
