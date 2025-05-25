#include <stdio.h>
#define N 6
int main()
{
    for (int x = 0; x < N; x++){
        for (int y = 0; y < x; y++) {
            printf(" ");
        }
        for (int y = 0; y < N - x; y++){ 
            printf("*");
        }
        printf("\n");
    }
    return 0;
}