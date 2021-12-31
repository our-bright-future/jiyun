#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head;
/* 헤드포인트 말고 헤드노드로 구현해보자 */

bool append(int newData) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) return false;
    newNode -> data = newData;
    newNode -> next = NULL;
    
    if (head == NULL) {
        head = newNode;
        return true;
    }
    Node *current = head;
    while (current -> next != NULL) {
        current = current -> next;
    }
    current -> next = newNode;
    return true;
}

bool prepand(int newData) {
    if (head == NULL) return false;
    Node *newNode = malloc(sizeof(Node));
    newNode -> data = newData;
    newNode -> next = head;
    head = newNode;
    return true;
}

bool delete(int targetData) {
    if (head == NULL) return false;
    if (head -> data == targetData) {
        head = head -> next;
        // 여기서 head였던거 free해야되지 않나
        return true;
    }
    Node *current = head;
    while (current -> next != NULL) {
        if (current -> next -> data == targetData) {
            current -> next = current -> next -> next;
            free(current);
            return true;
        }
        current = current -> next;
    }
    printf("There's no targetData");
    return false;
}

void print_node() {
    if (head == NULL) {
        printf("Nothing to print");
    }
    Node *current = head;
    while (current -> next != NULL) {
        printf("%d - ", current -> data);
        current = current -> next;
    }
    printf("%d - ", current -> data);
    printf("\n");
}

int main() {
    Node *head = NULL;

    append(5);
    append(127);
    append(30);
    print_node(); //1

    prepand(95);
    print_node(); //2
    delete(127);
    print_node(); //3

    delete(95);
    print_node(); //4

    delete(33); //5
}
/* 결과
1) 5 - 127 - 30 - 
2) 95 - 5 - 127 - 30 - 
3) 95 - 5 - 30 - 
4) 5 - 30 - 
5) There's no targetData
*/