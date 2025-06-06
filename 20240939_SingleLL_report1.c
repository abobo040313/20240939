// 실습 1-4
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void printList(Node* head) {
    Node* current = head;
    printf("연결 리스트 내용: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {

    Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);

    printList(head);

    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

// 실습 1-5
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    Node* current = head;
    printf("연결 리스트 내용: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int searchValue1(Node* head, int val) {
    int pos = 1;
    Node* current = head;
    while (current != NULL) {
        if (current->data == val) {
            return pos;
        }
        current = current->next;
        pos++;
    }
    return -1;
}

void searchValue2(Node* head, int val) {
    Node* prev = NULL;
    Node* current = head;

    while (current != NULL) {
        if (current->data == val) {
            printf("값 %d 발견!\n", val);
            if (prev != NULL) {
                printf("이전 노드 값: %d\n", prev->data);
            } else {
                printf("이전 노드 없음 (처음 노드)\n");
            }
            if (current->next != NULL) {
                printf("다음 노드 값: %d\n", current->next->data);
            } else {
                printf("다음 노드 없음 (마지막 노드)\n");
            }
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("값 %d를 찾을 수 없습니다.\n", val);
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("리스트 메모리 해제 완료.\n");
}

int main() {
    // 연결 리스트 구성
    Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);

    printList(head);

    // searchValue1 테스트
    int val = 30;
    int pos = searchValue1(head, val);
    if (pos != -1)
        printf("%d의 위치는 %d번째입니다.\n", val, pos);
    else
        printf("%d는 리스트에 없습니다.\n", val);

    // searchValue2 테스트
    searchValue2(head, val);

    // 메모리 해제
    freeList(head);

    return 0;
}
