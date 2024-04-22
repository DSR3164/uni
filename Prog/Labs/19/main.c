#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_BOOKS 100

typedef struct Node {
    char number[MAX_SIZE];
    char author[MAX_SIZE];
    char name[MAX_SIZE];
    char date[MAX_SIZE];
    int count;
} Node;

Node library[MAX_BOOKS];
int bookCount = 0;

int compareBooksByYear(const void *a, const void *b) {
    const Node *book1 = (const Node *)a;
    const Node *book2 = (const Node *)b;

    return strcmp(book1->date, book2->date);
}


void addBookFromInput() {
    char number[MAX_SIZE];
    char author[MAX_SIZE];
    char name[MAX_SIZE];
    char date[MAX_SIZE];
    int count;

    printf("Введите номер книги: ");
    scanf("%s", number);

    printf("Введите автора книги: ");
    scanf("%s", author);

    printf("Введите название книги: ");
    scanf("%s", name);

    printf("Введите год издания книги: ");
    scanf("%s", date);

    printf("Введите количество экземпляров книги: ");
    scanf("%d", &count);

    if (bookCount < MAX_BOOKS) {
        strcpy(library[bookCount].number, number);
        strcpy(library[bookCount].author, author);
        strcpy(library[bookCount].name, name);
        strcpy(library[bookCount].date, date);
        library[bookCount].count = count;
        bookCount++;
        printf("Книга успешно добавлена в библиотеку.\n");

        // Сортировка библиотеки по году издания после добавления книги
        qsort(library, bookCount, sizeof(Node), compareBooksByYear);
    } else {
        printf("Ошибка: превышено максимальное количество книг в библиотеке.\n");
    }
}


void removeBook() {
    int i;
    char number[MAX_SIZE];
    printf("Введите номер книги: ");
    scanf("%s", number);
    for (i = 0; i < bookCount; i++) {
        if (strcmp(library[i].number, number) == 0) {
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            printf("Книга успешно удалена из библиотеки.\n");
            return;
        }
    }
    printf("Ошибка: книга с таким номером не найдена в библиотеке.\n");
}

void searchBookByName() {
    char name[MAX_SIZE];
    int i;
    printf("Введите название книги: ");
    scanf("%s", name);
    for (i = 0; i < bookCount; i++) {
        if (strcmp(library[i].name, name) == 0) {
            printf("Найдена книга:\n");
            printf("Номер: %s\n", library[i].number);
            printf("Автор: %s\n", library[i].author);
            printf("Дата: %s\n", library[i].date);
            printf("Количество: %d\n", library[i].count);
            return;
        }
    }
    printf("Книга с таким названием не найдена в библиотеке.\n");
}
void printLibraryToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return;
    }

    fprintf(file, "Список книг в библиотеке:\n\n");
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "Номер: %s\n", library[i].number);
        fprintf(file, "Автор: %s\n", library[i].author);
        fprintf(file, "Название: %s\n", library[i].name);
        fprintf(file, "Дата: %s\n", library[i].date);
        fprintf(file, "Количество: %d\n", library[i].count);
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Список книг успешно записан в файл '%s'.\n", filename);
}


int main() {
    printf("Выберите метод: \n");
    while(1){
        int choise;
        printf("1 - Добавить книгу.\t2 - Удалить книгу.\n3 - Найти книгу.\t4 - Вывести список книг в файл.\n");
        
        if (scanf("%d", &choise) == 0){
            printf("Вроде букв там нет...\n");
            break;
        }
        switch (choise)
        {
        case 1:
            addBookFromInput();
            break;
        case 2:
            removeBook();
            break;
        case 3:
            searchBookByName();
            break;
        case 4:
            printLibraryToFile("library.txt");
            break;
        default:
            printf("Неверный выбор.");
            break;
        }
    }
    return 0;
}