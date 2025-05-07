# Autor: Cruz de la Cruz Carlos Eduardo

def es_primo(n):
    if n <= 1:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, int(n**0.5) + 1, 2):
        if n % i == 0:
            return False
    return True

def fibonacci_filtrado_hasta(K):
    fib = [0, 1]
    i = 2
    while True:
        siguiente = fib[-1] + fib[-2]
        if siguiente > K:
            break
        fib.append(siguiente)
        i += 1
    # Omitir términos en posiciones primas (indexado desde 1)
    return [fib[i] for i in range(len(fib)) if not es_primo(i + 1)]

def min_terminos_fibonacci(K, secuencia):
    resultado = []
    idx = len(secuencia) - 1
    while K > 0:
        while idx >= 0 and secuencia[idx] > K:
            idx -= 1
        if idx < 0:
            break
        resultado.append(secuencia[idx])
        K -= secuencia[idx]
        idx -= 1  # Asegura que los términos no se repitan
    return resultado

# Paso 1: Definir fecha de nacimiento (personaliza con tu fecha real)
dia = 25
mes = 12
anio = 1995

# Paso 2: Calcular K
K = dia * 100 + mes * 10 + (anio % 100)
print("K =", K)

# Paso 3: Generar secuencia de Fibonacci filtrada
fibonacci_modificado = fibonacci_filtrado_hasta(K)
print("Fibonacci filtrado:", fibonacci_modificado)

# Paso 4: Encontrar solución óptima
solucion = min_terminos_fibonacci(K, fibonacci_modificado)
print("Términos seleccionados:", solucion)
print("Número mínimo de términos:", len(solucion))
