#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/* rear에서 데이터 삽입, front에서 데이터 삭제 */
typedef struct queue {
    int *queue_arr;
    int max;
    int r;
    int f;
} queue;

queue *init_queue(queue *myQueue, int size) {
    myQueue -> queue_arr = malloc(size*sizeof(queue));
    myQueue -> max = size;
    myQueue -> f = 0;
    myQueue -> r = (myQueue -> max)-1;
    return myQueue;
}

bool is_empty(queue *myQueue) {
    return ((myQueue -> r)+1) % (myQueue -> max)== (myQueue -> f);
}

bool is_full(queue *myQueue) {
    return ((myQueue -> r)+2) % (myQueue -> max) == myQueue -> f;
}

void enqueue(queue *myQueue, int data) {
    if (is_full(myQueue)) {
        printf("Already full");
        return ;
    }
    myQueue -> r = ((myQueue -> r)+1) % (myQueue -> max);
    myQueue -> queue_arr[myQueue -> r] = data;
} 

int dequeue(queue *myQueue) {
    if (is_empty(myQueue)) {
        printf("It's empty");
        return INT_MIN;
    }
    int target = myQueue -> queue_arr[myQueue -> f];
    myQueue -> f = ((myQueue -> f)+1) % (myQueue -> max);
    return target;
}

int front(queue *myQueue) {
    if (is_empty(myQueue)) {
        printf("It's empty");
        return INT_MIN;
    }
    return myQueue -> queue_arr[myQueue -> f];
}

void print(queue *myQueue) {
    for (int i = myQueue -> f; i < myQueue -> r; i++) {
        printf("%d ", myQueue -> queue_arr[i]);
    }
    printf("\n");
}

int main() {
    queue q1;
    init_queue(&q1, 8);
    // 실질적으로는 max = 7, 한칸을 비워놔야하기 때문에 
    int arr[] = {1,9,9,5,0,5,3,0};
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        enqueue(&q1, arr[i]);
    }
    print(&q1);
    // Already full1 9 9 5 0 5

    dequeue(&q1);
    dequeue(&q1);
    print(&q1);
    // 9 5 0 5

    int f = front(&q1);
    printf("%d\n", f);
    // 9
}