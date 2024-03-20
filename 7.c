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

// Function to insert a node at the front of the list
void insertFront(int data) {
    struct Node *newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
        newNode->prev = head;
    } else {
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
        head = newNode;
    }
}

// Function to insert a node at the rear of the list
void insertRear(int data) {
    struct Node *newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
        newNode->prev = head;
    } else {
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
    }
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

    if (temp == head) {
        if (head->next == head) {
            free(head);
            head = NULL;
        } else {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            struct Node *temp2 = head;
            head = head->next;
            free(temp2);
        }
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
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
    do {
        if (temp->data == key) {
            printf("Key found at position %d\n", pos);
            return;
        }
        temp = temp->next;
        pos++;
    } while (temp != head);

    printf("Key not found\n");
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
        printf("1. Insert front\n");
        printf("2. Insert rear\n");
        printf("3. Delete by position\n");
        printf("4. Search by key\n");
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
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                deleteByPosition(pos);
                display();
                break;
            case 4:
                printf("Enter key to search: ");
                scanf("%d", &key);
                searchByKey(key);
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
