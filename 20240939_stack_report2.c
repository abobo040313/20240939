int main() {
    Stack s;
    char str[MAX];
    initStack(&s);
    int isValid = 1;
    printf("문자열 입력 : ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';

    for(int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            push(&s, ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (isEmpty(&s) || !isMatching(pop(&s), ch)) {
                isValid = 0;
                break;
            }
        }
    }

    if (!isEmpty(&s)) isValid = 0;

    if (isValid) 
        printf("유효한 괄호\n");
    else 
        printf("유효하지 않은 괄호\n");

    return 0;
}
