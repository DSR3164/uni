#include <stdio.h>
#include <stdlib.h>

int IsCI(int **matrix, int column, int n) {
    for (int i = 1; i < n; i++) {
        if (matrix[i][column] < matrix[i - 1][column]) {
            return 0;
        }
    }
    return 1;
}
int main() {
    int n, m;
    printf("Введите количество строк n: ");
    scanf("%d", &n);
    printf("Введите количество столбцов m: ");
    scanf("%d", &m);
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(m * sizeof(int));
    }
    printf("Введите элементы матрицы B(%d,%d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int InCC = 0;
    for (int j = 0; j < m; j++) {
        if (IsCI(matrix, j, n)) {
            InCC++;
        }
    }
    int zec = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                zec++;
            }
        }
    }
    printf("Количество упорядоченных по возрастанию столбцов: %d\n", InCC);
    printf("Количество нулевых элементов матрицы: %d\n", zec);
    return 0;
    
}
//IsCI = Столбец упорядочен(bool)
//InCC = Количество упорядоченных столбцов
//zec = количесво нулевых элементов