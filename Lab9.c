#include <stdio.h>

// Función que calcula el agua atrapada
int trap(int* height, int heightSize) {
    if (heightSize <= 2) return 0;

    int left = 0;
    int right = heightSize - 1;
    int left_max = 0, right_max = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= left_max) {
                left_max = height[left];
            } else {
                water += left_max - height[left];
            }
            left++;
        } else {
            if (height[right] >= right_max) {
                right_max = height[right];
            } else {
                water += right_max - height[right];
            }
            right--;
        }
    }

    return water;
}

int main() {
    int n;
    printf("Ingrese el número de columnas de altura: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("El número debe ser positivo.\n");
        return 1;
    }

    int height[n];
    printf("Ingrese las alturas:\n");
    for (int i = 0; i < n; i++) {
        printf("Altura[%d]: ", i);
        scanf("%d", &height[i]);
    }

    int resultado = trap(height, n);
    printf("Cantidad de agua atrapada: %d\n", resultado);

    return 0;
}
