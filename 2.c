#include<stdio.h>
#include<stdlib.h>

int ne = 0; 
int *x;
int size;

void disp() {
    if(ne == 0) {
        printf("Array empty\n");
        return;
    }
    printf("The Array elements are: \n");
    for(int i = 0; i < ne; i++)
        printf("%d\t", x[i]);
    printf("\n");
}

void insert_by_pos() {
    int pos, ele;
    if(ne == size) {
        printf("Array is full. Reallocating Array\n");
        size++;
        x = (int*)realloc(x, size * sizeof(int));
    }
    printf("Enter the element to be inserted: ");
    scanf("%d", &ele);
    printf("Enter the position where the element should be inserted: ");
    scanf("%d", &pos);
    if(pos >= 1 && pos <= ne + 1) {
        for(int i = ne - 1; i >= pos - 1; i--) {
            x[i + 1] = x[i];
        }
        x[pos - 1] = ele;
        ne++;
    }
    else
        printf("Invalid position\n");
}

void delete_by_ele() {
    int ele, found = 0;
    if(ne == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Enter the element that should be deleted: ");
    scanf("%d", &ele);
    for(int i = 0; i < ne; i++) {
        if(x[i] == ele) {
            for(int j = i; j < ne - 1; j++) {
                x[j] = x[j + 1];
            }
            ne--;
            found = 1;
            break;
        }
    }
    if(!found)
        printf("Element not found in the array\n");
}

void search_by_pos() {
    int pos;
    if(ne == 0) {
        printf("Array is empty\n");
        return;
    }
    printf("Enter the position from where element should be searched: ");
    scanf("%d", &pos);
    if(pos >= 1 && pos <= ne)
        printf("Element at position %d is %d\n", pos, x[pos - 1]);
    else
        printf("Invalid position\n");
}

void reverse() {
    int t;
    if(ne == 0) {
        printf("Array is empty\n");
        return;
    }
    for(int i = 0; i < ne / 2; i++) {
        t = x[i];
        x[i] = x[ne - i - 1];
        x[ne - i - 1] = t;
    }
}

int main() {
    int choice;
    printf("Enter the size: ");
    scanf("%d", &size);
    x = (int *)malloc(size * sizeof(int)); 
    printf("Menu\n1. Display\n2. Insert by position\n3. Delete by element\n4. Search by position\n5. Reverse\n6. Exit\n");
    while(1) {
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: disp();
                    break;
            case 2: insert_by_pos();
                    disp();
                    break;
            case 3: delete_by_ele();
                    disp();
                    break;
            case 4: search_by_pos();
                    break;
            case 5: reverse();
                    disp();
                    break;
            case 6: exit(0);
            default: printf("Invalid Choice\n");
        }
    }
    free(x); // Free allocated memory before exiting
    return 0;
}
