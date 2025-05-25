#include <stdio.h>
void one(){
    printf("Первое задание\n");
    int n, j, i;
    printf("Введите размер массива ");
    scanf("%d", &n);
    int A[n];
    printf("Введите массив ");
    for (int a = 0; a<n; a++) scanf("%d", &A[a]);
    for (i=0; i<n; i++){
        if (A[i]<0){
            for (j=i; j<n-1; j++) A[j]=A[j+1];
            n--;
            i--;
        }
    }
    printf("A=");
    for (int x=0; x<n; x++) printf("%d ", A[x]);
    printf("\n\n");
}

void two() {
    printf("Второе задание\n");
    int A[] = {12, 24, 36, 42}; // Пример массива A
    int n = sizeof(A) / sizeof(A[0]); // Размер массива
    int v = 12; // Начальное значение v
    
    for (int i = 0; i < n; i++) {
        if (A[i] % v != 0){v--;i = -1;} // Сбрасываем индекс на -1
    }

    printf("Наибольший общий делитель: %d\n", v);
    printf("\n\n");
}

void tree() {
    printf("Третье задание\n");
    int A[] = {1, 3, 5, 2, 4, -6}; // Пример массива
    int n = sizeof(A) / sizeof(A[0]); // Размер массива
    int s = 0; // Инициализация переменной для суммы

    for (int i = 0; i < n && A[i] > 0; i++) {
        s += A[i]; // Добавление положительного элемента к сумме
    }

    printf("Сумма положительных элементов: %d\n", s); // Вывод результата
    printf("\n\n");
}

void four() {
    printf("Четвертое задание\n");
    int A[10] = {1, -2, 3, -4, 5, 6, -7, 8, -9, 10}; // Пример массива A
    int i, s, k;
    
    for (i = 0, s = 0, k = 0; i < 10; i++) {
        if (A[i] < 0)
            k = 1;
        else {
            if (k == 1)
                s++;
            k = 0;
        }
    }

    printf("Количество последовательностей: %d\n", s);
    printf("\n\n");
}

int main(){
    one();
    two();
    tree();
    four();
    return 0;
}