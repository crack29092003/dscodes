#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
};

// Global variable to keep track of the head of the list
struct Node *head = NULL;

// Function to create a new node
struct Node* createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node by position
void insertByPosition(int data, int pos) {
    if (pos < 1) {
        printf("Invalid position\n");
        return;
    }

    struct Node *newNode = createNode(data);

    if (pos == 1) {
        if (head == NULL) {
            head = newNode;
            newNode->next = head;
        } else {
            struct Node *temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
            head = newNode;
        }
    } else {
        struct Node *temp = head;
        int count = 1;
        while (count < pos - 1 && temp->next != head) {
            temp = temp->next;
            count++;
        }
        if (count != pos - 1) {
            printf("Invalid position\n");
            return;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Function to delete the rear node
void deleteRear() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;
    while (temp->next != head) {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL) { // Only one node in the list
        free(head);
        head = NULL;
    } else {
        prev->next = head;
        free(temp);
    }
}

// Function to delete the front node
void deleteFront() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;
    while (temp->next != head) {
        temp = temp->next;
    }

    if (temp == head) { // Only one node in the list
        free(head);
        head = NULL;
    } else {
        temp->next = head->next;
        free(head);
        head = temp->next;
    }
}

// Function to search for an item by value
void searchByValue(int value) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    int pos = 1;
    do {
        if (temp->data == value) {
            printf("Item found at position %d\n", pos);
            return;
        }
        temp = temp->next;
        pos++;
    } while (temp != head);

    printf("Item not found\n");
}

// Function to display the list
void display() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main() {
    int choice, data, pos, value;

    while (1) {
        printf("\nCircular Singly Linked List Operations\n");
        printf("1. Insert by position\n");
        printf("2. Delete rear\n");
        printf("3. Delete front\n");
        printf("4. Search by value\n");
        printf("5. Display list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position to insert: ");
                scanf("%d", &pos);
                insertByPosition(data, pos);
                display();
                break;
            case 2:
                deleteRear();
                display();
                break;
            case 3:
                deleteFront();
                display();
                break;
            case 4:
                printf("Enter value to search: ");
                scanf("%d", &value);
                searchByValue(value);
                break;
            case 5:
                display();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
