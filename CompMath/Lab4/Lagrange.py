def read_data(filename):
    with open(filename, 'r') as file:
        x_values = list(map(float, file.readline().split()))
        y_values = list(map(float, file.readline().split()))
    return x_values, y_values

def lagrange_interpolate(x_values, y_values, x):
    n = len(x_values)
    L_n = 0.0
    for k in range(n):
        c_k = y_values[k]
        for i in range(n):
            if i != k:
                c_k *= (x - x_values[i]) / (x_values[k] - x_values[i])
        L_n += c_k
    return L_n

filename = r"in.txt"
x_eval = 1.0
x_vals, y_vals = read_data(filename)
print(x_vals)
print(y_vals)
print(x_eval)
Lx = lagrange_interpolate(x_vals, y_vals, x_eval)
print(f"L({x_eval}) = {Lx:.6f}")
