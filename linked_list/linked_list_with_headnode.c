#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int newData) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode -> data = newData;
    newNode -> next = NULL;

    return newNode;
}
// 뒤에 붙이기
void append(Node *head, Node *newNode) {
    if (head -> next == NULL) {
        head -> next = newNode;
        return ;
    } 
    
    Node *curr = head;
    while (curr -> next != NULL) {
        curr = curr -> next;
    }
    curr -> next = newNode;
}

// 중간에 붙이기
void insert(Node *head, Node *pre_newNode, Node *newNode) {
    // 비어있을 때
    if (head -> next == NULL && pre_newNode == NULL) {
        head -> next = newNode;
        return ;
    }
    
    if (pre_newNode == NULL) {
        Node *curr = head;
        while (curr -> next != NULL) {
            curr = curr -> next;
        }
        newNode -> next = curr -> next;
        curr -> next = newNode;
        return ;
    }
    newNode -> next = pre_newNode -> next;
    pre_newNode -> next = newNode;
}

void delete(Node *head, Node *target) {
    if(head -> next == NULL) return ;

    Node *curr = head;
    while (curr -> next != NULL) {
        if (curr -> next == target) {
            curr -> next = target -> next;
            free(target);
            return ;
        }
        curr = curr -> next;
    }
}

void print_ll(Node *head) {
    if (head -> next == NULL) {
        printf("Nothing to print");
    }
    Node *curr = head -> next;
    while (curr -> next != NULL) {
        printf("%d - ", curr -> data);
        curr = curr -> next;
    }
    printf("%d", curr -> data);
    printf("\n");
}

int main() {
    // 헤드 노드를 이용해보자
    Node head = {.data = 0, .next = NULL};

    Node *node_1 = create_node(19);
    Node *node_2 = create_node(95);
    Node *node_3 = create_node(30);
    append(&head, node_1);
    append(&head, node_2);
    append(&head, node_3);
    print_ll(&head);
    insert(&head, node_2, create_node(5));
    print_ll(&head);
    /* 
    19 - 95 - 30
    19 - 95 - 5 - 30
    */

    delete(&head, node_2);
    print_ll(&head);
    // 19 - 5 - 30

    delete(&head, node_1);
    print_ll(&head);
    // 5 - 30

    delete(&head, node_3);
    print_ll(&head);
    // 5
}