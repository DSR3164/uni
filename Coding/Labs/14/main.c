#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    FILE *file;
    int size;
    char sf;
    printf("Input count of strings: ");
    scanf("%d", &size);
    file = fopen("array.txt", "w");
    generatearray(file, size);
    fclose(file);
    file = fopen("array.txt", "r");
    replaceword(file, size);
    fclose(file);
    return 0;
}