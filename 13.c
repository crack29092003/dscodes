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

// Structure to represent a node in the priority queue
struct Node {
    int data;
    int priority;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the priority queue is empty
int isEmpty(struct Node* front) {
    return front == NULL;
}

// Function to insert an element into the priority queue based on priority
void enqueue(struct Node** front, int data, int priority) {
    struct Node* newNode = createNode(data, priority);
    if (!newNode)
        return;

    // If the queue is empty or the new node has higher priority than the front node
    if (*front == NULL || priority < (*front)->priority) {
        newNode->next = *front;
        *front = newNode;
    } else {
        struct Node* temp = *front;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    printf("Enqueued %d with priority %d\n", data, priority);
}

// Function to remove an element with the highest priority from the priority queue
int dequeue(struct Node** front) {
    if (isEmpty(*front)) {
        printf("Priority queue is empty. Dequeue failed.\n");
        return -1;
    }
    struct Node* temp = *front;
    int data = temp->data;
    *front = (*front)->next;
    free(temp);
    printf("Dequeued element: %d\n", data);
    return data;
}

// Function to display the priority queue
void display(struct Node* front) {
    if (isEmpty(front)) {
        printf("Priority queue is empty.\n");
        return;
    }
    printf("Priority queue elements:\n");
    while (front != NULL) {
        printf("Data: %d, Priority: %d\n", front->data, front->priority);
        front = front->next;
    }
}

// Function to free memory allocated to the priority queue
void freeQueue(struct Node** front) {
    while (*front != NULL) {
        struct Node* temp = *front;
        *front = (*front)->next;
        free(temp);
    }
}

int main() {
    struct Node* front = NULL;
    int choice, data, priority;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to enqueue: ");
                scanf("%d", &data);
                printf("Enter priority: ");
                scanf("%d", &priority);
                enqueue(&front, data, priority);
                break;
            case 2:
                dequeue(&front);
                break;
            case 3:
                display(front);
                break;
            case 4:
                freeQueue(&front);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
