#include <stdio.h>
#include <stdlib.h>

// Structure to represent a circular queue
struct CircularQueue {
    int front, rear;
    unsigned capacity;
    int* array;
};

// Function to create a circular queue of given capacity
struct CircularQueue* createQueue(unsigned capacity) {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    if (!queue)
        return NULL;
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    if (!queue->array) {
        free(queue);
        return NULL;
    }
    return queue;
}

// Function to check if the circular queue is full
int isFull(struct CircularQueue* queue) {
    return ((queue->rear + 1) % queue->capacity == queue->front);
}

// Function to check if the circular queue is empty
int isEmpty(struct CircularQueue* queue) {
    return (queue->front == -1);
}

// Function to enqueue an element into the circular queue
void enqueue(struct CircularQueue* queue, int item) {
    if (isFull(queue))
        printf("Queue is full. Enqueue operation failed.\n");
    else {
        if (isEmpty(queue))
            queue->front = 0;
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->array[queue->rear] = item;
        printf("Enqueued element: %d\n", item);
    }
}

// Function to dequeue an element from the circular queue
int dequeue(struct CircularQueue* queue) {
    int item = -1;
    if (isEmpty(queue)) {
        printf("Queue is empty. Dequeue operation failed.\n");
    } else {
        item = queue->array[queue->front];
        if (queue->front == queue->rear)
            queue->front = queue->rear = -1;
        else
            queue->front = (queue->front + 1) % queue->capacity;
        printf("Dequeued element: %d\n", item);
    }
    return item;
}

// Function to display the elements of the circular queue
void display(struct CircularQueue* queue) {
    if (isEmpty(queue))
        printf("Queue is empty.\n");
    else {
        printf("Queue elements: ");
        int i = queue->front;
        do {
            printf("%d ", queue->array[i]);
            i = (i + 1) % queue->capacity;
        } while (i != (queue->rear + 1) % queue->capacity);
        printf("\n");
    }
}

int main() {
    struct CircularQueue* queue = NULL;
    unsigned capacity;
    int choice, item;

    printf("Enter the capacity of the circular queue: ");
    scanf("%u", &capacity);

    queue = createQueue(capacity);

    if (!queue) {
        printf("Memory allocation failed. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &item);
                enqueue(queue, item);
                break;
            case 2:
                item = dequeue(queue);
                if (item != -1)
                    printf("Dequeued element: %d\n", item);
                break;
            case 3:
                display(queue);
                break;
            case 4:
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}









#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in a double-ended queue
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Structure to represent a double-ended queue
struct Deque {
    struct Node* front;
    struct Node* rear;
};

// Function to create a node in a double-ended queue
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode)
        return NULL;
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to create a double-ended queue
struct Deque* createDeque() {
    struct Deque* deque = (struct Deque*)malloc(sizeof(struct Deque));
    if (!deque)
        return NULL;
    deque->front = deque->rear = NULL;
    return deque;
}

// Function to check if the double-ended queue is empty
int isDequeEmpty(struct Deque* deque) {
    return (deque->front == NULL && deque->rear == NULL);
}

// Function to insert an element at the front of the double-ended queue
void insertFront(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    if (!newNode) {
        printf("Memory allocation failed. Insertion at front failed.\n");
        return;
    }
    if (isDequeEmpty(deque))
        deque->front = deque->rear = newNode;
    else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }
    printf("Inserted element at the front: %d\n", data);
}

// Function to insert an element at the rear of the double-ended queue
void insertRear(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    if (!newNode) {
        printf("Memory allocation failed. Insertion at rear failed.\n");
        return;
    }
    if (isDequeEmpty(deque))
        deque->front = deque->rear = newNode;
    else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }
    printf("Inserted element at the rear: %d\n", data);
}

// Function to delete an element from the front of the double-ended queue
int deleteFront(struct Deque* deque) {
    int data = -1;
    if (isDequeEmpty(deque))
        printf("Queue is empty. Deletion from front failed.\n");
    else {
        struct Node* temp = deque->front;
        data = temp->data;
        if (deque->front == deque->rear)
            deque->front = deque->rear = NULL;
        else {
            deque->front = deque->front->next;
            deque->front->prev = NULL;
        }
        free(temp);
        printf("Deleted element from the front: %d\n", data);
    }
    return data;
}

// Function to delete an element from the rear of the double-ended queue
int deleteRear(struct Deque* deque) {
    int data = -1;
    if (isDequeEmpty(deque))
        printf("Queue is empty. Deletion from rear failed.\n");
    else {
        struct Node* temp = deque->rear;
        data = temp->data;
        if (deque->front == deque->rear)
            deque->front = deque->rear = NULL;
        else {
            deque->rear = deque->rear->prev;
            deque->rear->next = NULL;
        }
        free(temp);
        printf("Deleted element from the rear: %d\n", data);
    }
    return data;
}

// Function to display the elements of the double-ended queue
void displayDeque(struct Deque* deque) {
    if (isDequeEmpty(deque))
        printf("Queue is empty.\n");
    else {
        struct Node* current = deque->front;
        printf("Queue elements: ");
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

// Function to free the memory allocated for the double-ended queue
void freeDeque(struct Deque* deque) {
    while (deque->front) {
        struct Node* temp = deque->front;
        deque->front = deque->front->next;
        free(temp);
    }
    free(deque);
}

int main() {
    struct Deque* deque = createDeque();
    if (!deque) {
        printf("Memory allocation failed. Exiting program.\n");
        return 1;
    }

    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert element at front\n");
        printf("2. Insert element at rear\n");
        printf("3. Delete element from front\n");
        printf("4. Delete element from rear\n");
        printf("5. Display queue elements\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at front: ");
                scanf("%d", &data);
                insertFront(deque, data);
                break;
            case 2:
                printf("Enter data to insert at rear: ");
                scanf("%d", &data);
                insertRear(deque, data);
                break;
            case 3:
                data = deleteFront(deque);
                if (data != -1)
                    printf("Deleted element from front: %d\n", data);
                break;
            case 4:
                data = deleteRear(deque);
                if (data != -1)
                    printf("Deleted element from rear: %d\n", data);
                break;
            case 5:
                displayDeque(deque);
                break;
            case 6:
                freeDeque(deque);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
