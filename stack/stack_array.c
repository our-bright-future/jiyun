#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
    char *stack_arr;
    int max;
    int top;
} stack;

stack *init_stack(stack *mystack, int size) {
    mystack -> stack_arr = malloc(size*sizeof(char));
    mystack -> max = size;
    mystack -> top = -1;
    return mystack;
}

void push(stack *mystack, char newData) {
    if (mystack -> top == (mystack -> max) - 1) {
        printf("Already full");
        return ;
    }
   mystack -> top++;
    mystack -> stack_arr[mystack -> top] = newData;
}

char pop(stack *mystack) {
    if (mystack -> top == -1) {
        printf("It's empty");
        return 0;
    }
    mystack -> top--;
    return mystack -> stack_arr[mystack -> top];
}

char peek(stack *mystack) {
    if (mystack -> top == -1) {
        printf("It's empty");
        return 0;
    }
    return mystack -> stack_arr[mystack -> top];
}

void duplicate(stack *mystack) {
    char c = pop(mystack);
    push(mystack, c);
    if (mystack -> top == (mystack -> max) - 1) {
        printf("Already full");
        return ;
    }
    push(mystack, c);
}

void up_rotate(stack *mystack, int n) {
    if (n > mystack -> max) {return ;}

    char tmp = mystack -> stack_arr[mystack -> top];
    for(int 
    i = mystack -> top; i > (mystack -> top) - (n-1); i--) 
        mystack -> stack_arr[i] = mystack -> stack_arr[i - 1];
    mystack -> stack_arr[(mystack -> top) - (n-1)] = tmp;
}

void down_rotate(stack *mystack, int n) {
    if (n > mystack -> max) {return ;}

    char tmp = mystack -> stack_arr[(mystack -> top) - (n-1)];
    for(int 
    i = (mystack -> top) - (n-1); i < mystack -> top; i++) 
        mystack -> stack_arr[i] = mystack -> stack_arr[i + 1];
    mystack -> stack_arr[mystack -> top] = tmp;
}

void print(stack *mystack) {
    for(int i = mystack -> top; i > -1; i--) 
        printf("%c", mystack -> stack_arr[i]);
    printf("\n");
}

int main() {
    char *str = "dlrow olleH";
    stack s1;
    init_stack(&s1, strlen(str));

    
    while (*str != '\0') {
        push(&s1, *str);
        str++;
    }
    print(&s1);
    // Hello world

    pop(&s1);
    print(&s1);
    // ello world

    up_rotate(&s1, 3);
    print(&s1);
    // lleo world

    down_rotate(&s1, 3);
    print(&s1);
    // ello world
}