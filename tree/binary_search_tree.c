#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int num;
    struct node *left;
    struct node *right;
} node;

/*
typedef node *rootNode;
// NULL을 대입하는 것으로 tree 생성
*/

node *get_node(int newNum) {
    node *newNode = malloc(sizeof(node));
    if (newNode == NULL) {return NULL;}

    newNode -> num = newNum;
    newNode -> left = newNode -> right = NULL;

    return newNode;
}
node *insert(node *rootNode, int newNum) {
    
    if (rootNode == NULL) {
        rootNode = get_node(newNum);
        return rootNode;
    }
    if (newNum == rootNode -> num) { // 중복값일 때
        printf("Please enter anothe input.\n");
        return NULL;
    } else if (newNum < rootNode -> num) { // 오른쪽으로 가야할 때(부모노드보다 클 때)
        rootNode -> left = insert(rootNode -> left, newNum);
    } else { // 왼쪽으로 가야할 때(부모노드보다 작을 때)
        rootNode -> right = insert(rootNode -> right, newNum);
    }
    return rootNode;
}

node *search_data(node *rootNode, int targetNum) {
    if (rootNode == NULL) {
        printf("There's no target data.\n");
        return NULL;
    }
    if (targetNum == rootNode -> num) {
        printf("Here it is: %d\n", targetNum);
        return rootNode;
    } else if (targetNum < rootNode -> num) {
        search_data(rootNode -> left, targetNum);
    } else {
        search_data(rootNode -> right, targetNum);
    }
}

node *succesor(node *rootNode) {
    node *curr = rootNode -> right;

    while (curr && curr -> left != NULL) {
        curr = curr -> left;
    }
    return curr;
}

node *predecessor(node *rootNode) {
    node *curr = rootNode -> left;

    while (curr && curr -> right != NULL) {
        curr = curr -> right;
    }
    return curr;
}

node *delete(node *rootNode, int targetNum) {
    if (rootNode == NULL) {return rootNode;}

    if (targetNum < rootNode -> num) { // 왼쪽으로 가야할 때
        rootNode -> left = delete(rootNode -> left, targetNum);
    } else if (targetNum > rootNode -> num) { // 오른쪽으로 가야할 때
        rootNode -> right = delete(rootNode -> right, targetNum);
    }
    // targetNum이 나타났는데
    if (targetNum == rootNode -> num) {
        // 자식노드가 아예 없는 경우는 생략하기도 하는듯
        if (rootNode -> left && rootNode -> right == NULL) {
            return NULL;
        } else if (rootNode -> left == NULL) { // 오른쪽 자식만 있을 때
            node *tmp = rootNode -> right;
            free(rootNode);
            return tmp;
        } else if (rootNode -> right == NULL){ // 왼쪽 자식만 있을 때
            node *tmp = rootNode -> left;
            free(rootNode);
            return tmp;

        /* 근데 왜 대체된 노드를 반환하는걸까????????  왜 copy 부분이 없을까?????????
           -> 아 재귀 끝나면 반환된 값이 지워진 자리에 대입되기 때문!!!!!!!*/
        
        } else { // 왼/오 두 자식 다 있을 때
            node *tmp = succesor(rootNode); // or predecessor()
            rootNode -> num = tmp -> num;
        /* 여기는 copy 부분이 있다구!!!!!! */
            rootNode -> right = delete(rootNode -> right, tmp -> num);
            
            /* or predecessor()
            node *tmp = predecessor(rootNode); 
            rootNode -> num = tmp -> num;
            rootNode -> left = delete(rootNode -> left, tmp -> num);
            */
        }
    }
    return rootNode;  
}

// inorder traversal
void print(node *rootNode) { 
    if(rootNode == NULL) {return ;}

    print(rootNode -> left); 
    printf("%d ",rootNode -> num); 
    print(rootNode -> right); 
}

// 잘 돌아가는지 확인 안해봄
int main() {
    node *rootNode = NULL;

    rootNode = insert(rootNode, 5);
    rootNode = insert(rootNode, 2);
    rootNode = insert(rootNode, 3);
    rootNode = insert(rootNode, 1);
    rootNode = insert(rootNode, 4);
    rootNode = insert(rootNode, 6);

    print(rootNode);
}
