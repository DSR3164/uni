#include <stdio.h>

#define MAX_SIZE 10 

void swapTriangles(int matrix[MAX_SIZE][MAX_SIZE], int size) {
    int i, j, temp;

    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

int main() {
    int size;

    do {
        printf("Введите размерность квадратной матрицы (не более %d): ", MAX_SIZE);
        scanf("%d", &size);

        if (size <= 0 || size > MAX_SIZE) {
            printf("Некорректный размер. Пожалуйста, повторите ввод.\n");
        }
    } while (size <= 0 || size > MAX_SIZE);

    int matrix[MAX_SIZE][MAX_SIZE];

    printf("Введите элементы матрицы (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int count = 0, mped = -1;

    printf("\nИсходная матрица:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    swapTriangles(matrix, size);

    printf("\nПолученная матрица:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
            if (matrix[i][j] == matrix[j][i]) {
                count++;
            }
            if (i == j && (matrix[i][j] > 0 && (mped == -1 || matrix[i][j] < mped))) {
                mped = matrix[i][j];
            }
        }
        printf("\n");
    }

    printf("\nКоличество совпадающих значений: %d\n", count);
    printf("Минимальный положительный элемент в главной диагонали: %d\n", mped);

    return 0;
}
