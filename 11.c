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
    if (!stack->array) {
        free(stack);
        return NULL;
    }
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

// Function to reverse a string
void reverseString(char* str) {
    int left = 0, right = strlen(str) - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

// Function to convert infix expression to prefix expression
char* infixToPrefix(char* exp) {
    struct Stack* stack = createStack(strlen(exp));
    char* prefix = (char*)malloc((strlen(exp) + 1) * sizeof(char));
    int i, j = 0;

    if (!stack || !prefix) {
        free(stack);
        free(prefix);
        return NULL;
    }

    reverseString(exp);

    for (i = 0; exp[i]; ++i) {
        if (exp[i] == '(') {
            exp[i] = ')';
            i++;
        } else if (exp[i] == ')') {
            exp[i] = '(';
            i++;
        }
    }

    for (i = 0; exp[i]; ++i) {
        if (isdigit(exp[i])) {
            prefix[j++] = exp[i];
        } else if (exp[i] == '(') {
            push(stack, exp[i]);
        } else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                prefix[j++] = pop(stack);
            }
            pop(stack); // Remove '('
        } else { // Operator
            while (!isEmpty(stack) && precedence(exp[i]) < precedence(peek(stack))) {
                prefix[j++] = pop(stack);
            }
            push(stack, exp[i]);
        }
    }

    while (!isEmpty(stack)) {
        prefix[j++] = pop(stack);
    }
    prefix[j] = '\0';

    reverseString(prefix);
    free(stack->array);
    free(stack);
    return prefix;
}

// Function to evaluate the prefix expression
int evaluatePrefix(char* exp) {
    struct Stack* stack = createStack(strlen(exp));
    int i, result;

    if (!stack)
        return -1;

    for (i = strlen(exp) - 1; i >= 0; --i) {
        if (isdigit(exp[i])) {
            push(stack, exp[i] - '0');
        } else {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i]) {
            case '+': push(stack, val1 + val2); break;
            case '-': push(stack, val1 - val2); break;
            case '*': push(stack, val1 * val2); break;
            case '/': push(stack, val1 / val2); break;
            }
        }
    }
    result = pop(stack);
    free(stack->array);
    free(stack);
    return result;
}

int main() {
    char infix[100], *prefix;
    int result;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Convert infix expression to prefix\n");
        printf("2. Evaluate prefix expression\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the infix expression: ");
                scanf("%s", infix);
                prefix = infixToPrefix(infix);
                if (prefix) {
                    printf("Prefix expression: %s\n", prefix);
                    free(prefix);
                } else {
                    printf("Failed to convert infix to prefix expression\n");
                }
                break;
            case 2:
                printf("Enter the prefix expression: ");
                scanf("%s", infix);
                result = evaluatePrefix(infix);
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
