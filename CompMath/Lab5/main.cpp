#include<iostream>
#include<iomanip>
#include<cmath>
#include<functional>
#include <chrono>
using namespace std::chrono;

using namespace std;

double f(double x) {
    return exp(-x * x);
}

double integrate_rect(double a, double b, int N, function<double(double)> func) {
    double h = (b - a) / N;
    double sum = 0.0;
    double base = a + h * 0.5;
    for (int i = 0; i < N; ++i) {
        sum += func(base);
        base+=h;
    }
    return sum * h;
}

int main() {
    double a, b, epsylon;
    cout << "Введите пределы интегрирования a и b: ";
    cin >> a >> b;
    cout << "Введите требуемую точность epsylon: ";
    cin >> epsylon;

    if (a == b) {
        cout << "I = 0 (нулевой интервал)\n";
        return 0;
    }

    int N = 1;
    double I_N = integrate_rect(a, b, N, f);
    double I_2N;
    auto start = high_resolution_clock::now();

    do {
        N *= 2;
        I_2N = integrate_rect(a, b, N, f);
        if (fabs(I_2N - I_N) < epsylon) {
            break;
        }
        I_N = I_2N;
    } while (true);
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<microseconds>(end - start).count();

    cout << "Приближённое значение интеграла I = "
              << setprecision(15) << I_2N << "\n";
    cout << "Использовано разбиений N = " << N << "\n";
    cout << "Время выполнения: " << elapsed << endl;

    return 0;
}
