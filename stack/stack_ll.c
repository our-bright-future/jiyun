#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_LEGTH 5
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN // 뭐든지 정해놓은 규칙대로 선언하면 된다.

typedef struct node {
    int value;
    struct node *next;
} node;

// 구조체 포인터(스택의 주소를 가리킨다)
typedef node *stack;

// 스택의 주소(구조체 포인터)를 가져오기 위해 이중포인터가 파라미터로 들어간다
bool push(stack *mystack, int value) {
    node *newnode = malloc(sizeof(node));
    
    if (newnode == NULL) return false;

    newnode -> value = value;
    newnode -> next = *mystack; 
    // *mystack은 'node **'(aka 'stack *')의 역참조의 역참조 즉, 스택의 주소값이다.
    *mystack = newnode;
    return true;
}

int pop(stack *mystack) {
    if (*mystack == NULL) return STACK_EMPTY;

    int result = (*mystack) -> value;
    node *tmp = *mystack;
    *mystack = (*mystack) -> next;
    free(tmp);
    return result;
}

int main() {
    stack s1 = NULL, s2 = NULL, s3 = NULL;
    push(&s1, 56);
    push(&s2, 78);
    push(&s2, 13);
    push(&s2, 98);

    int a;
    while ((a = pop(&s2)) != STACK_EMPTY) {
        printf("a = %d\n", a);
    }
    /*
    t = 98
    t = 13
    t = 78
    */
}