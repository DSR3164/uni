#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 200

typedef struct Record {
    char name[MAX_SIZE] = "";
    char number[MAX_SIZE] = "";
    struct Record* next;
} Record;

void addRecord(Record** head, const char* name, const char* number) {
    Record* newRecord = new Record;
    if (newRecord == nullptr) {
        printf("Ошибка выделения памяти для записи\n");
        exit(1);
    }
    strcpy(newRecord->name, name);
    strcpy(newRecord->number, number);
    newRecord->next = nullptr;

    if (*head == nullptr || strcmp((*head)->name, name) > 0) {
        newRecord->next = *head;
        *head = newRecord;
    } else {
        Record* current = *head;
        while (current->next != nullptr && strcmp(current->next->name, name) < 0) {
            current = current->next;
        }
        newRecord->next = current->next;
        current->next = newRecord;
    }
}


void printRecords(Record* head) {
    printf("Картотека:\n");
    while (head != NULL) {
        printf("Имя: %s\tНомер: %s\n", head->name, head->number);
        head = head->next;
    }
}

char* findNameByNumber(Record* head, const char* number) {
    while (head != NULL) {
        if (strcmp(head->number, number) == 0) {
            return head->name;
        }
        head = head->next;
    }
    return NULL;
}


int main() {
    Record* head = NULL;
    printf("Выберите метод: \n");
    while(1){
        int choise;
        printf("1 - Добавить запись.\t2 - Вывести картотеку.\n3 - Найти имя по номеру.\t4 - Выход.\n");
        
        if (scanf("%d", &choise) == 0){
            printf("Вроде букв там нет...\n");
            break;
        }
        switch (choise)
        {
        case 1:
            {
                char name[MAX_SIZE] = "";
                char number[MAX_SIZE] = "";
                printf("Введите имя: ");
                scanf("%s", name);
                printf("Введите номер телефона: ");
                scanf("%s", number);
                addRecord(&head, name, number);
            }
            break;
        case 2:
            printRecords(head);
            break;
        case 3:
            {
                char number[MAX_SIZE] = "";
                printf("Введите номер телефона: ");
                scanf("%s", number);
                char* name = findNameByNumber(head, number);
                if (name != NULL) {
                    printf("Имя владельца: %s\n", name);
                } else {
                    printf("Номер телефона не найден в картотеке.\n");
                }
            }
            break;
        case 4:
            return 0;
        default:
            printf("Неверный выбор.");
            break;
        }
    }
    return 0;
}


// Daniel
// +79234871221
// 1
// Andrew
// +79051234567
// 1
// Ekaterina
// +79162345678
// 1
// Ivan
// +79873456789
// 1
// Maria
// +79984567890
// 1
// Alexey
// +79895678901
// 1
// Olga
// +79706789012