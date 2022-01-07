#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *next;
} node;

typedef node *top;

node *initStack(top *stackTop) {
    *stackTop = NULL;
    return *stackTop;
}
/* -> 생략하고, main에서 선언과 동시에 NULL로 초기화해도 될 것 같은데
필요한 경우는 뭐가 있을까? */ 


void push(top *stackTop, char c) {
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL) {return ;}

    newnode -> data = c;
    newnode -> next = *stackTop;
    *stackTop = newnode;
}

char pop(top *stackTop) {
    if (*stackTop == NULL) {
        printf("It's empty");
        return 0;
    }

    char target = (*stackTop) -> data;
    node *tmp = *stackTop;
    *stackTop = (*stackTop) -> next;
    free(tmp);
    return target;
}

char peek(top *stackTop) {
    if (*stackTop == NULL) {
        printf("It's empty");
        return 0;
    }
    return (*stackTop) -> data;
}

void print(top *stackTop) {
    if (*stackTop == NULL) {
        printf("It's empty");
        return ;
    }
    node *tmp = *stackTop;
    while(tmp != NULL) {
        printf("%c-", tmp -> data);
        tmp = tmp -> next;
    }
    printf("\n");
}

int main() {
    top *stackTop;
    char *str = "olleH";

    initStack(stackTop);

    while (*str != '\0') {
        push(stackTop, *str);
        str++;
    }
    print(stackTop);
    // H-e-l-l-o-

    pop(stackTop);
    print(stackTop);
    // e-l-l-o-

    peek(stackTop);
    // e
}