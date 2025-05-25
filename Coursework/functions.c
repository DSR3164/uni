#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"


// Функция для определения, обладает ли дата заданным свойством
int has_interesting_property(data found) { // Функция для проверки даты на искомые характеристики
    int our_years = found.year % 100;
    return (found.day * found.month == our_years);
}

bool is_date_exist(data found) { //Функция для проверки даты на возможность существования
    // Проверка допустимого диапазона для месяца (от 1 до 12)
    if (found.month < 1 || found.month > 12) {
        return false;
    }

    // Определение количества дней в заданном месяце
    int days_in_month;
    switch (found.month) {
        case 1:  // Январь
        case 3:  // Март
        case 5:  // Май
        case 7:  // Июль
        case 8:  // Август
        case 10: // Октябрь
        case 12: // Декабрь
            days_in_month = 31;
            break;
        case 4:  // Апрель
        case 6:  // Июнь
        case 9:  // Сентябрь
        case 11: // Ноябрь
            days_in_month = 30;
            break;
        case 2:  // Февраль
            // Проверяем високосный год для февраля
            if ((found.year % 4 == 0 && found.year % 100 != 0) || found.year % 400 == 0) {
                days_in_month = 29; // Високосный год
            } else {
                days_in_month = 28; // Обычный год
            }
            break;
        default:
            return false; // Некорректный месяц
    }

    // Проверка допустимого диапазона для дня (от 1 до days_in_month)
    if (found.day < 1 || found.day > days_in_month) {
        return false;
    }

    // Дата существует, если все условия выполнены
    return true;
}

int find_and_write_dates(char *filename) { // Функция для поиска и записи дат в файл
    data Age;
    int count = 0, count1 = 0, max = 0, inyear = 0;
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Ошибка при открытии файла %s для записи.\n", filename);
        exit(1);
    }

    // Перебираем года с 1901 по 2000
    for ( Age.year = 1901; Age.year <= 2000; Age.year++) {
        for ( Age.month = 1; Age.month <= 12; Age.month++) {
            // Определяем количество дней в месяце
            int days_in_month;
            if (Age.month == 2) {
                // Февраль
                if ((Age.year % 4 == 0 && Age.year % 100 != 0) || Age.year % 400 == 0)
                    days_in_month = 29;
                else
                    days_in_month = 28;
            } else if (Age.month == 4 || Age.month == 6 || Age.month == 9 || Age.month == 11) {
                // Апрель, Июнь, Сентябрь, Ноябрь
                days_in_month = 30;
            } else {
                // Остальные месяцы
                days_in_month = 31;
            }

            // Проверяем все даты в месяце
            for (Age.day = 1; Age.day <= days_in_month; Age.day++) {
                if (has_interesting_property(Age)) {
                    count1 += 1;
                    count += 1;
                    fprintf(file, "%d/%d/%d\n", Age.day, Age.month, Age.year);
                    fflush(file); // Сбрасываем буфер после каждой записи
                }
            }
        }

        if(count>max){
            max = count;
            inyear = Age.year;
        }
        count = 0;
    }
    fprintf(file, "Количество искомых дат в данном веке: %d\n", count1);
    fprintf(file, "Год с наибольшим количестом искомых дат: %d - %d дат", inyear, max);
    fclose(file);
    return 0;
}
