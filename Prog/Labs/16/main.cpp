#include <iostream>
#include <ncurses.h>

using namespace std;

class OneNode{
public:    
    int data;
    OneNode* next;

    OneNode(int data){
        this->data = data;
        this->next = NULL;
    }
};
class TripleNode{
public:
    OneNode* first, * second;
    TripleNode* next;

    TripleNode(){
        this->next = NULL;
        this->first = NULL;
        this->second = NULL;
    }
};

class LinkedList{
public:
    OneNode* FirstHead, *FirstTail;
    OneNode* SecondHead, *SecondTail;
    TripleNode* head, * tail;

    LinkedList(){
        head = tail = NULL;
        FirstHead = FirstTail = SecondTail = SecondHead = NULL;
    }
//     ~LinkedList() {
//     while (head != NULL) {
//         TripleNode* temp = head;

//         OneNode* firstTemp = temp->first;
//         while (firstTemp != NULL) {
//             OneNode* nextNode = firstTemp->next;
//             delete firstTemp;
//             firstTemp = nextNode;
//         }

//         OneNode* secondTemp = temp->second;
//         while (secondTemp != NULL) {
//             OneNode* nextNode = secondTemp->next;
//             delete secondTemp;
//             secondTemp = nextNode;
//         }

//         head = head->next;
//         delete temp;
//     }
// }

    void CreateTripleNode(OneNode* firstHead, OneNode* firstTail, OneNode* secondHead, OneNode* secondTail){
        TripleNode* node = new TripleNode();
        node->first = firstHead;
        node->second = secondHead;

        int firstSize = 0, secondSize = 0;
        OneNode* temp = firstHead;
        while (temp != NULL) {
            firstSize++;
            temp = temp->next;
        }
        temp = secondHead;
        while (temp != NULL) {
            secondSize++;
            temp = temp->next;
        }

        while (firstSize > secondSize) {
            if (firstHead == NULL) break;
            if (firstHead == firstTail) {
                delete firstHead;
                firstHead = firstTail = NULL;
                break;
            }
            OneNode* prev = firstHead;
            while (prev->next != firstTail) {
                prev = prev->next;
            }
            delete firstTail;
            firstTail = prev;
            firstTail->next = NULL;
            firstSize--;
        }

        while (secondSize >= firstSize) {
            if (secondHead == NULL) break;
            if (secondHead == secondTail) {
                delete secondHead;
                secondHead = secondTail = NULL;
                break;
            }
            OneNode* prev = secondHead;
            while (prev->next != secondTail) {
                prev = prev->next;
            }
            delete secondTail;
            secondTail = prev;
            secondTail->next = NULL;
            secondSize--;
        }

        if (firstTail != NULL && secondTail == NULL) {
            node->second = NULL;
        } else if (firstTail == NULL && secondTail != NULL) {
            node->first = NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }

        tail->next = head;
    }// Центральная структура

    void CreateOneFirstNode(int data){
        OneNode* node = new OneNode(data);
        if (FirstHead == NULL) FirstHead = node;
        if (FirstTail != NULL) FirstTail->next = node;
        FirstTail = node;
    } // Верхняя структура
    void CreateOneSecondNode(int data){
        OneNode* node = new OneNode(data);
        if (SecondHead == NULL) SecondHead = node;
        if (SecondTail != NULL) SecondTail->next = node;
        SecondTail = node;
    } // Нижняя структура


    void EraseLastTripleElement(){
        if (tail == NULL) return;
        if (head == tail) {
            delete tail;
            head = tail = NULL;
            return;
        }
        TripleNode* node = head;

        for (;node->next != tail; node = node->next);
        node->next = NULL;
        delete tail;
        tail = node;
    }
    void MoveAlongLists() {
        TripleNode* tripleNode = head;
        do {
            cout << "Values in TripleNode: " << endl;
            cout << "First: ";
            if (tripleNode->first != NULL) {
                OneNode* firstNode = tripleNode->first;
                while (firstNode != NULL) {
                    cout << firstNode->data << " ";
                    firstNode = firstNode->next;
                }
            } 
            cout << endl;
            cout << "Second: ";
            if (tripleNode->second != NULL) {
                OneNode* secondNode = tripleNode->second;
                while (secondNode != NULL) {
                    cout << secondNode->data << " ";
                    secondNode = secondNode->next;
                }
            }
            cout << endl;
            tripleNode = tripleNode->next;
        } while (tripleNode != head);
    }
};

int main(){
    LinkedList list;
    
    int n = 0;
    int input;
    int index = 0;

    cout << "Введите элементы (введите -1 для завершения):" << endl;
    cin >> input;
    while (input != -1) {
        if (index % 2 == 0)
            list.CreateOneFirstNode(input);
        else
            list.CreateOneSecondNode(input);
        
        index++;
        cin >> input;
    }

    list.CreateTripleNode(list.FirstHead, list.FirstTail, list.SecondHead, list.SecondTail);

    list.MoveAlongLists();

    return 0;
}
