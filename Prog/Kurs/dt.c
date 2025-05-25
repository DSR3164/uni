#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s\n", argv[1]);
        return 1;
    }

    do{
        int choice;
        printf("Выберите режим работы:\n1 - Исползовать вложенные данные и сохранить в файле\n2 - Ввести свою дату и проверить на \"уникальность\"\nДля прекращения ввода отправте -3\n");
        if (scanf("%d", &choice) == 0){printf("Вы ввели не цифры . . .\n"); break;}

        switch (choice) {
            case 1:
                char *filename = argv[1];
                find_and_write_dates(filename);
                printf("Даты записаны в файл: %s\n", filename);
                exit(1);
            case 2:
                data age2;
                do{
                    
                    printf("Введите свою дату в форме Д М ГГГГ:\n");
                    if (scanf("%d %d %d", &age2.day, &age2.month, &age2.year) == 0){printf("Вы ввели не цифры . . .\n"); exit(12);}
                }while(!is_date_exist(age2));
                if(has_interesting_property(age2)){
                    printf("Дата %d.%d.%d имеет искомые характеристики (%d * %d = %d)\n", age2.day, age2.month, age2.year, age2.day, age2.month, age2.year % 100);}
                else{
                    printf("Дата %d.%d.%d не имеет искомые характеристики (%d * %d ≠ %d)\n", age2.day, age2.month, age2.year, age2.day, age2.month, age2.year % 100);}
                exit(2);
            case -3:
                printf("Прекращение ввода. Выход из программы.\n");
                exit(3);
            default:
                printf("\nНекорректный выбор. Пожалуйста, выберите 1, 2 или -3.\n");
                break;
        }
    }while(1);
    return 0;
}