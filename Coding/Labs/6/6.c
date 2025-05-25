#include <stdio.h>

int IsPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; ++i)
        if (num % i == 0) return 0;
    return 1;
}

int main() {
    int X[] = { 1, 2, 3, 5, 9, 7, 13, 19, 46, 17};
    int n = sizeof(X) / sizeof(X[0]);
    int Y[5], k = 0;
    for (int i = 1; i < n; i += 2)
        Y[k++] = X[i];

    int countpx = 0, countpy = 0;
    double sumX = 0, sumY = 0;
    for (int i = 0; i < n; ++i) {
        countpx += IsPrime(X[i]);
        sumX += X[i];
    }
    for (int i = 0; i < k; ++i) {
        countpy += IsPrime(Y[i]);
        sumY += Y[i];
    }
    printf("Простые числа в X: %d\n", countpx);
    printf("Простые числа в Y: %d\n", countpy);
    printf("Среднее арифметическое X: %.2f\n", sumX / n);
    printf("Среднее арифметическое Y: %.2f\n", sumY / k);
    return 0;
}
