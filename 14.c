#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the BST
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the BST
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// Function to perform inorder traversal of the BST
void inorder(struct Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

// Function to perform preorder traversal of the BST
void preorder(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

// Function to perform postorder traversal of the BST
void postorder(struct Node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

// Function to search for a key in the BST
struct Node* search(struct Node* root, int key, struct Node** parent) {
    struct Node* current = root;
    *parent = NULL;
    while (current != NULL) {
        if (key == current->key)
            return current;
        *parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}

// Function to count all nodes in the BST
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to find the height of the BST
int height(struct Node* root) {
    if (root == NULL)
        return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to find the node with the maximum key value in the BST
struct Node* findMax(struct Node* root, struct Node** parent) {
    struct Node* current = root;
    *parent = NULL;
    while (current->right != NULL) {
        *parent = current;
        current = current->right;
    }
    return current;
}

// Function to print node details
void printNodeDetails(struct Node* node, struct Node* parent) {
    printf("Key: %d", node->key);
    if (parent)
        printf(", Parent: %d\n", parent->key);
    else
        printf(", No parent\n");
}

int main() {
    struct Node* root = NULL;
    int choice, key;
    struct Node* parent;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert a key\n");
        printf("2. Inorder traversal\n");
        printf("3. Preorder traversal\n");
        printf("4. Postorder traversal\n");
        printf("5. Search for a node\n");
        printf("6. Count all nodes\n");
        printf("7. Find height of the tree\n");
        printf("8. Find node with maximum key\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                printf("Enter key to search: ");
                scanf("%d", &key);
                struct Node* foundNode = search(root, key, &parent);
                if (foundNode)
                    printf("Node found: ");
                else
                    printf("Node not found: ");
                printNodeDetails(foundNode, parent);
                break;
            case 6:
                printf("Total number of nodes: %d\n", countNodes(root));
                break;
            case 7:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 8:
                struct Node* maxNode = findMax(root, &parent);
                printf("Node with maximum key: ");
                printNodeDetails(maxNode, parent);
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
