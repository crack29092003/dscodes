#include<stdio.h>
#include<stdlib.h>

int ne = 0; 
int *x;
int size;

void disp() {
    int i;
    if (ne == 0) {
        printf("Array empty\n");
        return;
    }
    printf("The Array elements are:\n");
    for (i = 0; i < ne; i++)
        printf("%d\t", x[i]);
    printf("\n");
}

void insert_by_order() {
    int i, ele;
    if (ne == size) {
        printf("Array is full. Reallocating Array\n");
        size++;
        x = (int*)realloc(x, size * sizeof(int));
    }
    printf("Enter the element to be inserted: ");
    scanf("%d", &ele);
    i = ne - 1;
    while (i >= 0 && x[i] > ele) {
        x[i + 1] = x[i];
        i--;
    }
    x[i + 1] = ele;
    ne++;
}

void delete_by_pos() {
    int i, pos;
    if (ne == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Enter the position from where elements should be deleted: ");
    scanf("%d", &pos);
    if (pos >= 1 && pos <= ne) {
        for (i = pos - 1; i < ne - 1; i++) {
            x[i] = x[i + 1];
        }
        ne--;
    } else {
        printf("Invalid position.\n");
    }
}

void search_by_key() {
    int i, ele, found = 0;
    if (ne == 0) {
        printf("Array is empty\n");
        return;
    }
    printf("Enter the element that should be searched: ");
    scanf("%d", &ele);
    for (i = 0; i < ne; i++) {
        if (x[i] == ele) {
            printf("Element found at position %d\n", i + 1);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Element not found\n");
    }
}

void reverse() {
    int t, i;
    if (ne == 0) {
        printf("Array is empty\n");
        return;
    }
    for (i = 0; i < ne / 2; i++) {
        t = x[i];
        x[i] = x[ne - i - 1];
        x[ne - i - 1] = t;
    }
}

int main() {
    int choice;
    printf("Enter the size: ");
    scanf("%d", &size);
    x = (int*)malloc(size * sizeof(int)); 
    printf("Menu\n1. Display\n2. Insert by order\n3. Delete by position\n4. Search by key\n5. Reverse\n6. Exit\n");
    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: disp();
                    break;
            case 2: insert_by_order();
                    disp();
                    break;
            case 3: delete_by_pos();
                    disp();
                    break;
            case 4: search_by_key();
                    break;
            case 5: reverse();
                    disp();
                    break;
            case 6: 
                    exit(0);
            default: printf("Invalid choice\n");
        }
    }
    free(x); // Free allocated memory before exiting
    return 0;
}
