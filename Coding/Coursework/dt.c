#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    // Проверка на правильность количества аргументов командной строки
    if (argc != 2) {
        fprintf(stderr, "Использование: %s \n", argv[1]);
    }

    // Главный цикл программы
    do {
        int choice;
        // Запрос режима работы у пользователя
        printf("Выберите режим работы:\n1 - Использовать вложенные данные и сохранить в файле\n2 - Ввести свою дату и проверить на \"уникальность\"\nДля прекращения ввода отправьте -3\n");
        // Проверка на корректный ввод числа 
        if (scanf("%d", &choice) == 0) {
            printf("Вы ввели не цифры . . .\n");
            break;
        }

        // Обработка выбора пользователя
        switch (choice) {
            case 1: {
                // Обработка первого режима работы
                char *filename = argv[1];
                find_and_write_dates(filename);
                printf("Даты записаны в файл: %s\n", filename);
                exit(1);
            }
            case 2: {
                // Обработка второго режима работы
                data age2;
                do {
                    // Запрос даты у пользователя
                    printf("Введите свою дату в форме Д М ГГГГ:\n");
                    if (scanf("%d %d %d", &age2.day, &age2.month, &age2.year) == 0) {
                        printf("Вы ввели не цифры . . .\n");
                        exit(12);
                    }
                    if (!is_date_exist(age2)){
                        printf("Вы ввели некорректные данные!\nПовторите ввод\n");
                    }
                // Проверка существования введенной даты
                } while (!is_date_exist(age2));
                // Проверка уникальных характеристик даты
                if (has_interesting_property(age2)) {
                    printf("Дата %d.%d.%d имеет искомые характеристики (%d * %d = %d)\n", age2.day, age2.month, age2.year, age2.day, age2.month, age2.year % 100);
                } else {
                    printf("Дата %d.%d.%d не имеет искомые характеристики (%d * %d ≠ %d)\n", age2.day, age2.month, age2.year, age2.day, age2.month, age2.year % 100);
                }
                exit(2);
            }
            case -3:
                // Обработка выхода из программы
                printf("Прекращение ввода. Выход из программы.\n");
                exit(3);
            default:
                // Обработка некорректного выбора
                printf("\nНекорректный выбор. Пожалуйста, выберите 1, 2 или -3.\n");
                break;
        }
    } while (1); // Бесконечный цикл до выхода из программы
    return 0;
}