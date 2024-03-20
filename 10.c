#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to create a stack of given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack)
        return NULL;
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    if (!stack->array)
        return NULL;
    return stack;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element to the stack
void push(struct Stack* stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

// Function to get the top element of the stack without removing it
char peek(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top];
}

// Function to get the precedence of an operator
int precedence(char op) {
    if (op == '(')
        return 0;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return -1;
}

// Function to convert infix expression to postfix expression
char* infixToPostfix(char* exp) {
    struct Stack* stack = createStack(strlen(exp));
    char* postfix = (char*)malloc((strlen(exp) + 1) * sizeof(char));
    int i, j = 0;

    if (!stack || !postfix)
        return NULL;

    for (i = 0; exp[i]; ++i) {
        if (isdigit(exp[i])) {
            postfix[j++] = exp[i];
        } else if (exp[i] == '(') {
            push(stack, exp[i]);
        } else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
            }
            pop(stack); // Remove '('
        } else { // Operator
            while (!isEmpty(stack) && precedence(exp[i]) <= precedence(peek(stack))) {
                postfix[j++] = pop(stack);
            }
            push(stack, exp[i]);
        }
    }

    while (!isEmpty(stack)) {
        postfix[j++] = pop(stack);
    }
    postfix[j] = '\0';
    free(stack);
    return postfix;
}

// Function to evaluate the postfix expression
int evaluatePostfix(char* exp) {
    struct Stack* stack = createStack(strlen(exp));
    int i, result;

    if (!stack)
        return -1;

    for (i = 0; exp[i]; ++i) {
        if (isdigit(exp[i])) {
            push(stack, exp[i] - '0');
        } else {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i]) {
            case '+': push(stack, val2 + val1); break;
            case '-': push(stack, val2 - val1); break;
            case '*': push(stack, val2 * val1); break;
            case '/': push(stack, val2 / val1); break;
            }
        }
    }
    result = pop(stack);
    free(stack);
    return result;
}

int main() {
    char infix[100], *postfix;
    int result;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Convert infix expression to postfix\n");
        printf("2. Evaluate postfix expression\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the infix expression: ");
                scanf("%s", infix);
                postfix = infixToPostfix(infix);
                printf("Postfix expression: %s\n", postfix);
                free(postfix);
                break;
            case 2:
                printf("Enter the postfix expression: ");
                scanf("%s", infix);
                result = evaluatePostfix(infix);
                printf("Result of evaluation: %d\n", result);
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
