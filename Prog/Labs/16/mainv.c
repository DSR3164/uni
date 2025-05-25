#include <stdio.h>
#include <stdlib.h>

struct OneNode {
    int data;
    struct OneNode* next;
};

struct TripleNode {
    struct OneNode* first;
    struct OneNode* second;
    struct TripleNode* next;
};

struct LinkedList {
    struct OneNode* FirstHead;
    struct OneNode* FirstTail;
    struct OneNode* SecondHead;
    struct OneNode* SecondTail;
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
    return node;
}

void createTripleNode(struct LinkedList* list, struct OneNode* firstHead, struct OneNode* firstTail, struct OneNode* secondHead, struct OneNode* secondTail) {
    if (firstHead == NULL || secondHead == NULL) {
        printf("Один или оба списка пусты\n");
        return;
    }

    struct TripleNode* node = createEmptyTripleNode();
    node->first = firstHead;
    node->second = secondHead;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->tail->next = list->head;
}

void createOneFirstNode(struct LinkedList* list, int data) {
    struct OneNode* node = createOneNode(data);
    if (list->FirstHead == NULL) list->FirstHead = node;
    if (list->FirstTail != NULL) list->FirstTail->next = node;
    list->FirstTail = node;
}

void createOneSecondNode(struct LinkedList* list, int data) {
    struct OneNode* node = createOneNode(data);
    if (list->SecondHead == NULL) list->SecondHead = node;
    if (list->SecondTail != NULL) list->SecondTail->next = node;
    list->SecondTail = node;
}

void moveAlongLists(struct LinkedList* list) {
    struct TripleNode* tripleNode = list->head;
    do {
        printf("Values in TripleNode: \n");
        printf("First: ");
        if (tripleNode->first != NULL) {
            struct OneNode* firstNode = tripleNode->first;
            while (firstNode != NULL) {
                printf("%d ", firstNode->data);
                firstNode = firstNode->next;
            }
        } 
        printf("\n");
        printf("Second: ");
        if (tripleNode->second != NULL) {
            struct OneNode* secondNode = tripleNode->second;
            while (secondNode != NULL) {
                printf("%d ", secondNode->data);
                secondNode = secondNode->next;
            }
        }
        printf("\n");
        tripleNode = tripleNode->next;
    } while (tripleNode != list->head);
}

int main() {
    struct LinkedList list;
    int input;
    int index = 0;

    list.FirstHead = NULL;
    list.FirstTail = NULL;
    list.SecondHead = NULL;
    list.SecondTail = NULL;
    list.head = NULL;
    list.tail = NULL;

    printf("Введите элементы (введите -1 для завершения):\n");
    scanf("%d", &input);
    while (input != -1) {
        if (index % 2 == 0)
            createOneFirstNode(&list, input);
        else
            createOneSecondNode(&list, input);

        index++;
        scanf("%d", &input);
    }

    createTripleNode(&list, list.FirstHead, list.FirstTail, list.SecondHead, list.SecondTail);

    moveAlongLists(&list);

    return 0;
}