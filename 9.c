#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
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
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node by order
void insertByOrder(int data) {
    struct Node *newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
        newNode->prev = head;
    } else if (data < head->data) {
        struct Node *last = head->prev;
        newNode->next = head;
        newNode->prev = last;
        head->prev = newNode;
        last->next = newNode;
        head = newNode;
    } else {
        struct Node *current = head->next;
        while (current != head && current->data < data) {
            current = current->next;
        }
        struct Node *prev = current->prev;
        newNode->next = current;
        newNode->prev = prev;
        prev->next = newNode;
        current->prev = newNode;
    }
}

// Function to delete the rear node
void deleteRear() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    if (head->next == head) {
        free(head);
        head = NULL;
    } else {
        struct Node *last = head->prev;
        struct Node *secondLast = last->prev;
        secondLast->next = head;
        head->prev = secondLast;
        free(last);
    }
}

// Function to delete the front node
void deleteFront() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    if (head->next == head) {
        free(head);
        head = NULL;
    } else {
        struct Node *temp = head;
        struct Node *last = head->prev;
        head = head->next;
        head->prev = last;
        last->next = head;
        free(temp);
    }
}

// Function to search for an item by position
void searchByPosition(int pos) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    int count = 1;
    do {
        if (count == pos) {
            printf("Item found at position %d: %d\n", pos, temp->data);
            return;
        }
        temp = temp->next;
        count++;
    } while (temp != head);

    printf("Position not found\n");
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
    int choice, data, pos;

    while (1) {
        printf("\nCircular Doubly Linked List Operations\n");
        printf("1. Insert by order\n");
        printf("2. Delete rear\n");
        printf("3. Delete front\n");
        printf("4. Search by position\n");
        printf("5. Display list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertByOrder(data);
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
                printf("Enter position to search: ");
                scanf("%d", &pos);
                searchByPosition(pos);
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
