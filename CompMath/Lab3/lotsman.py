import math

def f(x):
    if x <= 0:
        raise ValueError("Х должен быть положительным")
    return 2 - math.sqrt(x**3) - 2 * math.log(x)

def f1(x):
    # f'(x)
    return -1.5*math.sqrt(x) - 2/x

def f2(x):
    # f''(x)
    return -0.75/math.sqrt(x) + 2/x**2

def lotsman_method(x0: float, eps: float = 1e-6, max_iter: int = 100) -> float:
    x = x0
    for _ in range(max_iter):
        fx = f(x)
        f1x = f1(x)
        f2x = f2(x)
        div = 2*f1x*f1x - fx*f2x
        if abs(div) < 1e-14:
            raise ZeroDivisionError("Делитель близок к нулю")
        x_new = x - 2*fx*f1x/div
        if abs(x_new - x) < eps:
            return x_new
        x = x_new
    raise RuntimeError(f"Не сошлось за {max_iter} итераций")

x0 = 1.0
root = lotsman_method(x0)
print(f"Корень: x = {root}")
print(f"f(x) = {f(root)}")
