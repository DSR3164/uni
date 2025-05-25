#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char name[MAX_LENGTH];
    char group[MAX_LENGTH];
    int estimation[3];
} Student;

void writeintofile(FILE *file, Student st){
    fprintf(file, "%s\t%s\t%d %d %d\n", st.name, st.group, st.estimation[0], st.estimation[1], st.estimation[2]);
}

Student readStudentFromFile(FILE *file) {
    Student st;
    fscanf(file, "%s\t%s\t%d %d %d\n", st.name, st.group, &st.estimation[0], &st.estimation[1], &st.estimation[2]);
    return st;
}

int main() {
    FILE *file;
    Student st;
    memset(st.group, '\0', sizeof(st.group));
    memset(st.name, '\0', sizeof(st.name));
    int found = 0;

    file = fopen("Wedomost.txt", "w");
    if (file == NULL) {
        printf("Ошибка при создании файла.\n");
        return 1;
    }

    printf("Введите информацию о студенте (фамилия и инициалы, группу и успеваемость по трём предметам)\n");
    while (1) {
        printf("Введите фамилию и инициалы (или 'end' для завершения ввода):\n");
        scanf("%s", st.name);
        if (strcmp(st.name, "end") == 0) {
            break;
        }
        printf("Введите группу:\n");
        scanf("%s", st.group);
        printf("Введите успеваемость:\n");
        scanf("%d %d %d",  &st.estimation[0], &st.estimation[1], &st.estimation[2]);

        writeintofile(file, st);
    }

    fclose(file);

    file = fopen("Wedomost.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }

    printf("\nРезультаты поиска:\n");
    while (!feof(file)) {
        Student current_st = readStudentFromFile(file);
        for(int i = 0; i < sizeof(current_st.estimation)/sizeof(int); i++){
            if(current_st.estimation[i]==2){
                found = 1;
                printf("Найден студент с 2 в успеваемости\nСтудент - %s \nГруппы - %s\nУспеваемость - %d %d %d\n\n", current_st.name, current_st.group, current_st.estimation[0], current_st.estimation[1], current_st.estimation[2]);
            }
        }
    }   

    if (!found) {
        printf("Студент с 2 в успеваемости не найден.\n");
    }

    fclose(file);

    return 0;
}
// Гусев
// МЛ-315
// 4 9 2
// Кузнецов
// ТР-724
// 6 5 1
// Попов
// ПХ-511
// 2 7 3
// Смирнов
// АН-832
// 9 8 6
// Никитин
// КД-217
// 3 5 9
// Беляев
// ОЛ-604
// 8 4 7
// Казанцев
// СТ-923
// 1 6 2
// Федоров
// УГ-482
// 5 3 8
// Лебедев
// ДВ-375
// 7 2 4
// Андреев
// НП-609
// 4 1 5
// Козлов
// ЕМ-815
// 6 9 3
// Морозов
// ЗФ-247
// 2 8 1
// Волков
// ТС-731
// 9 4 6
// Ткачев
// ШИ-563
// 3 7 2
// Романов
// ГК-846
// 1 5 9