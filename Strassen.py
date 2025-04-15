import numpy as np
from time import perf_counter

def suma(X, Y):
    return [[X[i][j] + Y[i][j] for j in range(len(X))] for i in range(len(X))]

def resta(X, Y):
    return [[X[i][j] - Y[i][j] for j in range(len(X))] for i in range(len(X))]

def partir(M):
    n = len(M)
    m = n // 2
    return (
        [fila[:m] for fila in M[:m]],
        [fila[m:] for fila in M[:m]],
        [fila[:m] for fila in M[m:]],
        [fila[m:] for fila in M[m:]],
    )

def strassen(A, B):
    n = len(A)
    if n == 1:
        return [[A[0][0] * B[0][0]]]

    A11, A12, A21, A22 = partir(A)
    B11, B12, B21, B22 = partir(B)

    S1 = strassen(suma(A11, A22), suma(B11, B22))
    S2 = strassen(suma(A21, A22), B11)
    S3 = strassen(A11, resta(B12, B22))
    S4 = strassen(A22, resta(B21, B11))
    S5 = strassen(suma(A11, A12), B22)
    S6 = strassen(resta(A21, A11), suma(B11, B12))
    S7 = strassen(resta(A12, A22), suma(B21, B22))

    C11 = suma(resta(suma(S1, S4), S5), S7)
    C12 = suma(S3, S5)
    C21 = suma(S2, S4)
    C22 = suma(resta(suma(S1, S3), S2), S6)

    resultado = []
    for i in range(n // 2):
        resultado.append(C11[i] + C12[i])
    for i in range(n // 2):
        resultado.append(C21[i] + C22[i])
    return resultado

# Tamaño
tam = 128
m1 = np.random.randint(0, 10, (tam, tam)).tolist()
m2 = np.random.randint(0, 10, (tam, tam)).tolist()

inicio = perf_counter()
matriz_resultado = strassen(m1, m2)
fin = perf_counter()

print(f"Tiempo ejecución (Strassen): {fin - inicio:.6f} segundos")

