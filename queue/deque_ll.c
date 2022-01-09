#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int element;
typedef struct node {
    struct node *prev;
    element data;
    struct node *next;
} node;

typedef struct deque {
    node *f;
    node *r;
    int size;
} deque;

deque *init_deque(deque *mydq) {
    mydq -> f = mydq -> r = NULL;
    mydq -> size = 0;

    return mydq;
}

node *get_node(element newData) {
    node *newNode = malloc(sizeof(node));
    newNode -> data = newData;
    newNode -> prev = newNode -> next = NULL;

    return newNode;
}

bool is_empty(deque *mydq) {
    return mydq -> f == NULL;
}

void insert_front(deque *mydq, element newData) {
    node *newNode = get_node(newData);
    if (newNode == NULL) {return ;}

    if (is_empty(mydq)) {
        mydq -> f = mydq -> r = newNode;
    } else {
        newNode -> next = mydq -> f;
        mydq -> f -> prev = newNode;
        mydq -> f = newNode;
    }
    mydq -> size++;
}

void insert_rear(deque *mydq, element newData) {
    node *newNode = get_node(newData);
    if (newNode == NULL) {return ;}

    if (is_empty(mydq)) {
        mydq -> f = mydq -> r = newNode;
    } else {
        newNode -> prev = mydq -> r;
        mydq -> r -> next = newNode;
        mydq -> r = newNode;
    }
    mydq -> size++;
}

element delete_front(deque *mydq) {
    if(is_empty(mydq)) {
        printf("It's empty. Cannot be deleted");
        return -1;
    }
    element target = mydq -> f -> data;
    node *tmp = mydq -> f;
    mydq -> f = mydq -> f -> next;
    // if only one element was present
    if (mydq -> f == NULL) {
        mydq -> r = NULL;
    } else {
        mydq -> f -> prev = NULL;
    }
    free(tmp);
    mydq -> size--;

    return target;
}

element delete_rear(deque *mydq) {
    if (is_empty(mydq)) {
        printf("It's empty. Cannot be deleted");
        return -1;
    }
    element target = mydq -> r -> data;
    node *tmp = mydq -> r;
    mydq -> r = mydq -> r -> prev;
    if (mydq -> r == NULL) {
        mydq -> f = NULL;
    } else {
        mydq -> r -> next = NULL;
    }
    free(tmp);
    mydq -> size--;

    return target;
}

element get_front(deque *mydq) {
    if (is_empty(mydq)) {
        printf("It's empty.");
        return -1;
    }
    return mydq -> f -> data;
}

element get_rear(deque *mydq) {
    if (is_empty(mydq)) {
        printf("It's empty.");
        return -1;
    }
    return mydq -> r -> data;
}

void print(deque *mydq) {
    if (is_empty(mydq)) {
        printf("It's empty!");
        return ;
    }
    node *curr = mydq -> f;
    while (curr != mydq -> r -> next) {
        printf("%d ", curr -> data);
        curr = curr -> next;
    }
    printf("\n");
}

int main() {
    deque dq;
    init_deque(&dq);

    insert_front(&dq, 5);
    insert_rear(&dq, 30);
    insert_front(&dq, 1995);

    print(&dq);
    // 1995 5 30 

    insert_front(&dq, 77);
    insert_rear(&dq, 88);
    delete_front(&dq);
    delete_rear(&dq);

    print(&dq);
    // 1995 5 30 
}