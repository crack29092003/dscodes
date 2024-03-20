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

// Function to insert a node at the front of the list
void insertFront(int data) {
    struct Node *newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        newNode->next = head->next;
        head->next = newNode;
    }
}

// Function to insert a node at the rear of the list
void insertRear(int data) {
    struct Node *newNode = createNode(data);
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
    }
}

// Function to delete a node with the given key
void deleteByKey(int key) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key) {
        prev = head;
        while (prev->next != head) {
            prev = prev->next;
        }
        if (head->next == head) {
            free(head);
            head = NULL;
            return;
        }
        prev->next = temp->next;
        free(temp);
        head = prev->next;
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    do {
        prev = temp;
        temp = temp->next;
    } while (temp != head && temp->data != key);

    // If key was not present in the list
    if (temp == head) {
        printf("Key not found\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// Function to search for an item by position
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
        printf("\nCircular Singly Linked List Operations\n");
        printf("1. Insert front\n");
        printf("2. Insert rear\n");
        printf("3. Delete a node by key\n");
        printf("4. Search for an item by position\n");
        printf("5. Display list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at the front: ");
                scanf("%d", &data);
                insertFront(data);
                display();
                break;
            case 2:
                printf("Enter data to insert at the rear: ");
                scanf("%d", &data);
                insertRear(data);
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
