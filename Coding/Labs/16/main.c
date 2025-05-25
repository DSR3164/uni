#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NIL "NIL"

struct OneNode {
    int data;
    struct OneNode* next;
    struct OneNode* prev;
};

struct TripleNode {
    struct OneNode* first;
    struct OneNode* second;
    struct TripleNode* next;
    struct TripleNode* prev;
};

struct LinkedList {
    struct TripleNode* head;
    struct TripleNode* tail;
};

struct OneNode* createOneNode(int data) {
    struct OneNode* newNode = (struct OneNode*)malloc(sizeof(struct OneNode));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти для узла\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

struct TripleNode* createEmptyTripleNode() {
    struct TripleNode* node = malloc(sizeof(struct TripleNode));
    if (node == NULL) {
        printf("Ошибка выделения памяти для узла\n");
        exit(1);
    }
    node->first = NULL;
    node->second = NULL;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void appendNode(struct OneNode** head, struct OneNode** tail, int data) {
    struct OneNode* newNode = createOneNode(data);
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
}

void appendTripleNode(struct LinkedList* list, struct OneNode* first, struct OneNode* second) {
    struct TripleNode* newNode = createEmptyTripleNode();
    newNode->first = first;
    newNode->second = second;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }

    list->tail->next = list->head;
    list->head->prev = list->tail;
}

void printLinkedList(struct LinkedList list) {
    struct TripleNode* current = list.head;
    do {
        if (current->first != NULL && current->second != NULL) {
            printf("(%d,%d) ", current->first->data, current->second->data);
        } else {
            printf("(%s,%s) ", NIL, NIL);
        }
        current = current->next;
    } while (current != list.head);
    printf("\n");
}

void move(struct TripleNode** current, char direction) {
    if (direction == 'd') {
        *current = (*current)->next;
    } else if (direction == 'a') {
        *current = (*current)->prev;
    }
}

int main() {
    struct LinkedList list;
    struct OneNode* head = NULL;
    struct OneNode* tail = NULL;
    int input;
    char direction;

    list.head = NULL;
    list.tail = NULL;

    printf("Введите элементы (введите -1 для завершения):\n");
    if (scanf("%d", &input) == 0){
        printf("Нужны цифры\n");
        exit(1);
    }

    while (input != -1) {
        appendNode(&head, &tail, input);
        scanf("%d", &input);
    }

    if ((tail - head + 1) % 2 != 0) {
        appendNode(&head, &tail, 0);
    }

    struct OneNode* current = head;
    
    while (current != NULL && current->next != NULL) {
        appendTripleNode(&list, current, current->next);
        current = current->next->next;
    }

    struct TripleNode* currentTriple = list.head;

    while (1) {
        printf("Введите направление (a - Влево, d - Вправо, q - выход): ");
        scanf(" %c", &direction);

        if (direction == 'q') {
            break;
        }

        move(&currentTriple, direction);
        if (currentTriple->second->data == 0){
             printf("Верхний элемент: %d\nНижний элемент: NIL\n", currentTriple->first->data);
        } else{
            printf("Верхний элемент: %d\nНижний элемент: %d\n", currentTriple->first->data, currentTriple->second->data);
        }
    }

    return 0;
}