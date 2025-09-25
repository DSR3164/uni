def seidel(A, b, eps=1e-4, max_iter=1000):
    """
    Решение СЛАУ методом Зейделя: Ax = b
    A — квадратная матрица
    b — вектор свободных членов
    eps — допустимая погрешность
    max_iter — максимальное количество итераций
    """
    n = len(A)
    x = [0.0 for _ in range(n)]

    for it in range(max_iter):
        x_new = x.copy()
        for i in range(n):
            sum1 = sum(A[i][j] * x_new[j] for j in range(i))
            sum2 = sum(A[i][j] * x[j] for j in range(i + 1, n))
            x_new[i] = (b[i] - sum1 - sum2) / A[i][i]

        if max(abs(x_new[i] - x[i]) for i in range(n)) < eps:
            return x_new
        x = x_new

    raise ValueError("Метод Зейделя не сошелся за заданное число итераций")

A = [
    [10, -1, 2, 0],
    [-1, 11, -1, 3],
    [2, -1, 10, -1],
    [0, 3, -1, 8]
]
b = [6, 25, -11, 15]
solution = seidel(A, b)
print("Решение:", solution)
