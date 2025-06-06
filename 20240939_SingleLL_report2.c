#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define PHONE_LEN 20

typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    struct Contact* next;
} Contact;

Contact* createContact(const char* name, const char* phone) {
    Contact* newNode = (Contact*)malloc(sizeof(Contact));
    if (!newNode) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    strncpy(newNode->name, name, NAME_LEN);
    strncpy(newNode->phone, phone, PHONE_LEN);
    newNode->next = NULL;
    return newNode;
}

void addContact(Contact** head, const char* name, const char* phone) {
    Contact* newNode = createContact(name, phone);
    newNode->next = *head;
    *head = newNode;
    printf("연락처가 추가되었습니다: %s - %s\n", name, phone);
}


void searchContact(Contact* head, const char* name) {
    Contact* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("검색 결과: %s의 전화번호는 %s입니다.\n", name, current->phone);
            return;
        }
        current = current->next;
    }
    printf("'%s' 연락처를 찾을 수 없습니다.\n", name);
}

void deleteContact(Contact** head, const char* name) {
    Contact* current = *head;
    Contact* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            printf("'%s' 연락처가 삭제되었습니다.\n", name);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("'%s' 연락처를 찾을 수 없어 삭제할 수 없습니다.\n", name);
}

void printContacts(Contact* head) {
    if (head == NULL) {
        printf("전화번호부가 비어 있습니다.\n");
        return;
    }

    printf("📒 현재 전화번호부:\n");
    Contact* current = head;
    while (current != NULL) {
        printf("- 이름: %s | 전화번호: %s\n", current->name, current->phone);
        current = current->next;
    }
}

void freeContacts(Contact* head) {
    Contact* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("모든 연락처 메모리가 해제되었습니다.\n");
}

int main() {
    Contact* phoneBook = NULL;
    int choice;
    char name[NAME_LEN];
    char phone[PHONE_LEN];

    while (1) {
        printf("\n--- 전화번호부 메뉴 ---\n");
        printf("1. 연락처 추가\n2. 연락처 검색\n3. 연락처 삭제\n4. 전화번호부 출력\n5. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("이름 입력: ");
                scanf("%s", name);
                printf("전화번호 입력: ");
                scanf("%s", phone);
                addContact(&phoneBook, name, phone);
                break;
            case 2:
                printf("검색할 이름 입력: ");
                scanf("%s", name);
                searchContact(phoneBook, name);
                break;
            case 3:
                printf("삭제할 이름 입력: ");
                scanf("%s", name);
                deleteContact(&phoneBook, name);
                break;
            case 4:
                printContacts(phoneBook);
                break;
            case 5:
                freeContacts(phoneBook);
                return 0;
            default:
                printf("잘못된 입력입니다. 다시 시도해주세요.\n");
        }
    }
}
