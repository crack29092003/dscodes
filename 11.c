#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_EXPR_SIZE 100

struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

void push(struct Stack* stack, char op) {
    stack->array[++stack->top] = op;
}

int isOperand(char ch) {
    return isalnum(ch);
}

int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

void reverseString(char* str) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void infixToPrefix(char* infix, char* prefix) {
    struct Stack* stack = createStack(strlen(infix));
    int i, k;
    for (i = strlen(infix) - 1, k = 0; i >= 0; --i) {
        if (isOperand(infix[i]))
            prefix[k++] = infix[i];
        else if (infix[i] == ')')
            push(stack, infix[i]);
        else if (infix[i] == '(') {
            while (!isEmpty(stack) && peek(stack) != ')')
                prefix[k++] = pop(stack);
            pop(stack);
        } else {
            while (!isEmpty(stack) && precedence(infix[i]) < precedence(peek(stack)))
                prefix[k++] = pop(stack);
            push(stack, infix[i]);
        }
    }
    while (!isEmpty(stack))
        prefix[k++] = pop(stack);
    prefix[k] = '\0';
    reverseString(prefix);
}

int evaluatePrefix(char* prefix) {
    struct Stack* stack = createStack(strlen(prefix));
    int i, op1, op2;
    for (i = 0; prefix[i]; ++i) {
        if (isdigit(prefix[i]))
            push(stack, prefix[i] - '0');
        else {
            op1 = pop(stack);
            op2 = pop(stack);
            switch (prefix[i]) {
                case '+':
                    push(stack, op1 + op2);
                    break;
                case '-':
                    push(stack, op1 - op2);
                    break;
                case '*':
                    push(stack, op1 * op2);
                    break;
                case '/':
                    push(stack, op1 / op2);
                    break;
            }
        }
    }
    return pop(stack);
}

int main() {
    char infix[MAX_EXPR_SIZE];
    char prefix[MAX_EXPR_SIZE];
    int result;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Convert Infix to Prefix\n");
        printf("2. Evaluate Prefix Expression\n");
        printf("3. Exit\n");
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the infix expression: ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);
                printf("Prefix expression: %s\n", prefix);
                break;
            case 2:
                printf("Enter the prefix expression: ");
                scanf("%s", prefix);
                result = evaluatePrefix(prefix);
                printf("Result of evaluation: %d\n", result);
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

