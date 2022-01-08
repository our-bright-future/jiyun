#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct queue {
    node *f;
    node *r;
} queue;

queue *init_queue(queue *myQueue) {
    myQueue -> f = NULL;
    myQueue -> r = NULL;
    return myQueue;
}

bool is_empty(queue *myQueue) {
    return myQueue -> f == NULL;
}
// 뒤에 붙는다
void enqueue(queue *myQueue, int newData) {
    node *newNode = malloc(sizeof(node));
    if (newNode == NULL) return false;

    newNode -> data = newData;
    newNode -> next = NULL;
    if (is_empty(myQueue)) {
        myQueue -> f = myQueue -> r = newNode;
    } else {
        myQueue -> r -> next = newNode;
        myQueue -> r = newNode;
    }
}
// 가장 앞 노드가 지워진다
int dequeue(queue *myQueue) {
    if (is_empty(myQueue)) {
        printf("It's empty");
        return INT_MIN;
    }
    int target = myQueue -> f -> data;
    node *tmp = myQueue -> f;
    myQueue -> f = myQueue -> f -> next;
    // 하나 남은걸 지웠을 때
    if (myQueue -> f == NULL)
        myQueue -> r = NULL;
    free(tmp);

    return target;
}

