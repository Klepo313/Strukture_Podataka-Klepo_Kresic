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
void postorder(Node* root);
void levelorder(Node* root);

int main() {
    Node* root = NULL;
    int arr[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    // a) Dodavanje elemenata u stablo
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    // Ispisi stabla
    printf("INORDER: ");
    inorder(root);
    printf("\n");

    printf("POSTORDER: ");
    postorder(root);
    printf("\n");

    printf("LEVELORDER: ");
    levelorder(root);
    printf("\n");

    // b) Zamjena vrijednosti sumom potomaka
    replace(root);

    // Ispisi modificiranog stabla
    printf("\nUpdated Tree (INORDER): ");
    inorder(root);
    printf("\nUpdated Tree (POSTORDER): ");
    postorder(root);
    printf("\nUpdated Tree (LEVELORDER): ");
    levelorder(root);
    printf("\n");

    // Oslobađanje memorije
    free(root);

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

    int leftSum = replace(root->left);
    int rightSum = replace(root->right);

    int oldVal = root->data;
    root->data = leftSum + rightSum;

    return root->data + oldVal;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void levelorder(Node* root) {
    if (root == NULL) return;

    Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}
