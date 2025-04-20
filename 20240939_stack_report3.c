#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
#define TRUE 1
#define FALSE 0

typedef struct {
    int top;
    char items[MAX];
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char item) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->items[++(s->top)] = item;
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

char peek(Stack *s) {
    if (isEmpty(s)) return '\0';
    return s->items[s->top];
}

int precedence(char op) {
    switch (op) {
        case '(': return 0;
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
    }
    return -1;
}

typedef struct {
    int top;
    int items[MAX];
} IntStack;

void initIntStack(IntStack *s) {
    s->top = -1;
}

void pushInt(IntStack *s, int item) {
    s->items[++(s->top)] = item;
}

int popInt(IntStack *s) {
    return s->items[(s->top)--];
}

int evalPostfix(char *postfix) {
    IntStack s;
    initIntStack(&s);
    int i, op1, op2;

    for (i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            pushInt(&s, postfix[i] - '0');
        } else {
            op2 = popInt(&s);
            op1 = popInt(&s);
            switch (postfix[i]) {
                case '+': pushInt(&s, op1 + op2); break;
                case '-': pushInt(&s, op1 - op2); break;
                case '*': pushInt(&s, op1 * op2); break;
                case '/': pushInt(&s, op1 / op2); break;
            }
        }
    }
    return popInt(&s);
}

int infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int i, j = 0;
    char token;

    for (i = 0; infix[i] != '\0'; i++) {
        token = infix[i];

        if (isdigit(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(&s, token);
        } else if (token == ')') {
            while (peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s);  
        } else { 
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(token)) {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';

    return evalPostfix(postfix);
}

int main(void) {
    char infix[MAX];
    char postfix[MAX];
    int result;

    printf("중위표기식 입력 : ");
    scanf("%s", infix);

    result = infixToPostfix(infix, postfix);

    printf("후위표기식 : %s\n", postfix);
    printf("후위표기식 계산 결과 : %d\n", result);

    return 0;
}
