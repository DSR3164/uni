#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <header.h>
#include <math.h>
#include <string.h>
#define MAX_LENGTH 300

void generatearray(FILE *file, int size) {
    char charset[] = "abcdefghijklmnopqrstuvwxyz"; 
    for (int i = 0; i< size; i++){
        int length = ((double)rand() / RAND_MAX) * 10 + 10;
        for (int x = 0; x < length; x++) {
            int random = ((double)rand() / RAND_MAX) * 12 + 3;
            for (int y = 0; y < random; y++){
                int letter = ((double)rand() / RAND_MAX) * 26;
                fprintf(file, "%c", charset[letter]);
            }
            if(x<length-1)fprintf(file, " ");
        }
        if(i<size-1)fprintf(file, "\n");
    }
}

void replaceword(FILE *file, int size) {
    FILE *out;
    out = fopen("output.txt", "w");
    char line[MAX_LENGTH] = "";                                 // Строка
    char temp[MAX_LENGTH] = "";                                 // Временная переменная 
    char longest_word[MAX_LENGTH] = "";                         // Самое длинное слово

    for (int i = 0; i < size; i++) {
        fgets(line, MAX_LENGTH, file);                          // Считываем строку из файла
        line[strcspn(line, "\n")] = '\0';
        int length = strlen(line);
        strcpy(temp, line);                                     // Копируем строку для обработки

        char *token = strtok(temp, " ");
        while (token != NULL) {
            if (strlen(token) > strlen(longest_word))strcpy(longest_word, token);
            token = strtok(NULL, " ");
        }

        char *replace_position = strstr(line, longest_word);
        if (replace_position != NULL) {           
            size_t longest_len = strlen(longest_word);          // Определяем длину самого длинного слова            
            size_t start_pos = replace_position - line;         // Позиция, где начинается слово            
            strncpy(temp, line, start_pos);                     // Копируем часть строки до найденного слова
            temp[start_pos] = '\0';                             // Устанавливаем нулевой символ в конец строки           
            strcat(temp, "DENIS");                              // Добавляем "DENIS" к temp           
            strcat(temp, replace_position + longest_len);       // Добавляем остаток строки после найденного слова к temp     
            memset(temp + strlen(temp), '\0', 30);              // Убираем мусор
            if(i<size-1)temp[strlen(temp)]='\n';                // Добавляем конец строки
            memset(line, '\0', sizeof(line));                   // Очищаем строку
            strcpy(line, temp);                                 // Копируем результат обратно в line
        }
        fputs(line, out);                                       // Записываем измененную строку в файл
        memset(longest_word, '\0', sizeof(longest_word));       // Очистка
        memset(line, '\0', sizeof(line));                       // Очистка
        memset(temp, '\0', sizeof(temp));                       // Очистка
    }
    printf("Done!\n");
}

// gcc -c header.h -o header.o
// gcc -c functions.c -o functions.o
// ar rcs libheader.a header.o functions.o
// gcc main.c -o static -L. -lheader -lm
// ./static
