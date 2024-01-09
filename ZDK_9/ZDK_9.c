#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int data);

Node* insert(Node* root, int data);

int replace(Node* root);

void inorder(Node* root);

void freeTree(Node* root);

int main() {
    Node* root = NULL;
    int arr[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    if (root != NULL) {
        printf("Original Tree (Inorder): ");
        inorder(root);
        printf("\n");

        int sum = replace(root);

        printf("Updated Tree (Inorder): ");
        inorder(root);
        printf("\n");

        printf("Sum of Original Values: %d\n", sum);
    }

    // Oslobađanje memorije
    freeTree(root);

    return 0;
}

Node* newNode(int data) {
    Node* root = (Node*)malloc(sizeof(Node));
    if (root != NULL) {
        root->data = data;
        root->left = NULL;
        root->right = NULL;
    }
    return root;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }
    else {
        if (data <= root->data) root->left = insert(root->left, data);
        else root->right = insert(root->right, data);
        return root;
    }
}

int replace(Node* root) {
    if (root == NULL) return 0;
    int old_val = root->data;
    root->data = replace(root->left) + replace(root->right);
    return root->data + old_val;
}

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}