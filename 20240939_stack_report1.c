int main() {
    char input[MAX_LENGTH + 1];
    Stack s;
    initStack(&s, MAX_LENGTH);

    printf("문자열을 입력하세요 (최대 %d자): ", MAX_LENGTH);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; 

    for (int i = 0; input[i] != '\0'; i++) {
        push(&s, input[i]);
    }

    printf("거꾸로 출력된 문자열: ");
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }
    printf("\n");

    freeStack(&s);
    return 0;
}
