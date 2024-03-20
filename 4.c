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

// Function to insert a node in sorted order
void insertByOrder(int data) {
    struct Node *newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        head->next = head; // Circular link
        return;
    }

    // Find the correct position to insert
    struct Node *temp = head;
    while (temp->next != head && temp->next->data < data) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Function to delete a node by position
void deleteByPosition(int pos) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;
    int count = 0;

    // Traverse until we reach the position or back to head
    do {
        prev = temp;
        temp = temp->next;
        count++;
    } while (temp != head && count < pos);

    // Check if the position is valid
    if (temp == head || count != pos) {
        printf("Invalid position\n");
        return;
    }

    // Delete the node
    prev->next = temp->next;
    free(temp);

    // Update head if necessary
    if (temp == head) {
        head = prev->next;
    }
}

// Function to search for a node by key
void searchByKey(int key) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    int pos = 1;
    while (temp->next != head && temp->data != key) {
        temp = temp->next;
        pos++;
    }

    if (temp->data == key) {
        printf("Item found at position: %d\n", pos);
    } else {
        printf("Item not found\n");
    }
}

// Function to delete a node by key
void deleteByKey(int key) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;

    // Find the node with the given key
    while (temp->next != head && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key not found
    if (temp->data != key) {
        printf("Item not found\n");
        return;
    }

    // Delete the node
    if (temp == head) {
        prev = head;
        while (prev->next != head) {
            prev = prev->next;
        }
        prev->next = head->next;
        head = head->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
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
        printf("\nCircular Singly Linked List Operations\n");
        printf("1. Insert by order\n");
        printf("2. Delete by position\n");
        printf("3. Search for an item by key\n");
        printf("4. Delete by key\n");
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
                printf("Enter key to search: ");
                scanf("%d", &key);
                searchByKey(key);
                break;
            case 4:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteByKey(key);
                display();
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
