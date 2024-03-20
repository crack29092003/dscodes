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

// Function to insert a node in sorted order
void insertByOrder(int data) {
    struct Node *newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        head->next = head;
        head->prev = head;
        return;
    }

    struct Node *temp = head;
    while (temp->next != head && temp->next->data < data) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
}

// Function to delete a node by position
void deleteByPosition(int pos) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    int count = 1;
    while (count < pos && temp->next != head) {
        temp = temp->next;
        count++;
    }

    if (count != pos) {
        printf("Invalid position\n");
        return;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    if (temp == head) {
        head = temp->next;
    }
    free(temp);
}

// Function to delete a node by key
void deleteByKey(int key) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    while (temp->next != head && temp->data != key) {
        temp = temp->next;
    }

    if (temp->data != key) {
        printf("Key not found\n");
        return;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    if (temp == head) {
        head = temp->next;
    }
    free(temp);
}

// Function to search for a node by position
void searchByPosition(int pos) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    int count = 1;
    while (count < pos && temp->next != head) {
        temp = temp->next;
        count++;
    }

    if (count != pos) {
        printf("Invalid position\n");
        return;
    }

    printf("Element at position %d is %d\n", pos, temp->data);
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
    int choice, data, pos, key;

    while (1) {
        printf("\nCircular Doubly Linked List Operations\n");
        printf("1. Insert by order\n");
        printf("2. Delete by position\n");
        printf("3. Delete by key\n");
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
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                deleteByPosition(pos);
                display();
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteByKey(key);
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
