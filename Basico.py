import numpy as np
from time import perf_counter

def multiplicacion_basica(X, Y):
    dimension = len(X)
    resultado = [[0 for _ in range(dimension)] for _ in range(dimension)]
    for fila in range(dimension):
        for columna in range(dimension):
            for indice in range(dimension):
                resultado[fila][columna] += X[fila][indice] * Y[indice][columna]
    return resultado

# Tamaño (debe ser potencia de 2)
tam = 128
matriz_1 = np.random.randint(0, 10, (tam, tam)).tolist()
matriz_2 = np.random.randint(0, 10, (tam, tam)).tolist()

inicio = perf_counter()
producto = multiplicacion_basica(matriz_1, matriz_2)
fin = perf_counter()

print(f"Tiempo ejecución (Básica): {fin - inicio:.6f} segundos")

