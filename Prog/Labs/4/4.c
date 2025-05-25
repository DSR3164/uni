#include <stdio.h>
int main() {
    char a;
    int res = 0;
    printf("Введите целое положительное число: "); 
    scanf("%d", &a);

    printf("Обычный порядок: "); 
    for (int i = 7; i >= 0; --i) { 
        printf("%d", (a >> i) & 1);
    } 
    printf(" = %d",a);

    for (int i=0; i < 8; ++i) { 
        int bit = a & 1;
        a = a >> 1; 
        res = (res << 1) | bit;
    }

    printf("\nОбратный порядок: "); 
    for (int i = 7; i >= 0; --i) { 
        printf("%d", (res >> i) & 1);
    }

    printf(" = %d", res);

    return 0;
}