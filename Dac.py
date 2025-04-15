import numpy as np
from time import perf_counter

def sumar(A, B):
    return [[A[i][j] + B[i][j] for j in range(len(A))] for i in range(len(A))]

def dividir_matriz(M):
    n = len(M)
    mitad = n // 2
    return (
        [fila[:mitad] for fila in M[:mitad]],
        [fila[mitad:] for fila in M[:mitad]],
        [fila[:mitad] for fila in M[mitad:]],
        [fila[mitad:] for fila in M[mitad:]],
    )

def multiplicacion_dyv(A, B):
    n = len(A)
    if n == 1:
        return [[A[0][0] * B[0][0]]]

    A1, A2, A3, A4 = dividir_matriz(A)
    B1, B2, B3, B4 = dividir_matriz(B)

    P1 = multiplicacion_dyv(A1, B1)
    P2 = multiplicacion_dyv(A2, B3)
    P3 = multiplicacion_dyv(A1, B2)
    P4 = multiplicacion_dyv(A2, B4)
    P5 = multiplicacion_dyv(A3, B1)
    P6 = multiplicacion_dyv(A4, B3)
    P7 = multiplicacion_dyv(A3, B2)
    P8 = multiplicacion_dyv(A4, B4)

    sup_izq = sumar(P1, P2)
    sup_der = sumar(P3, P4)
    inf_izq = sumar(P5, P6)
    inf_der = sumar(P7, P8)

    resultado = []
    for i in range(n // 2):
        resultado.append(sup_izq[i] + sup_der[i])
    for i in range(n // 2):
        resultado.append(inf_izq[i] + inf_der[i])
    return resultado

# Tamaño
tam = 128
mat1 = np.random.randint(0, 10, (tam, tam)).tolist()
mat2 = np.random.randint(0, 10, (tam, tam)).tolist()

inicio = perf_counter()
res = multiplicacion_dyv(mat1, mat2)
fin = perf_counter()

print(f"Tiempo ejecución (Divide y Vencerás): {fin - inicio:.6f} segundos")

