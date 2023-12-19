#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct treenode {
    int value;
    struct treenode* left;
    struct treenode* right;
} treenode;

// Prototip funkcije za stvaranje novog čvora
treenode* createnode(int value);

// Prototip funkcije za umetanje broja u stablo
bool insertnumber(treenode** rootptr, int value);

// Prototip funkcije za pretragu broja u stablu
bool findnumber(treenode* root, int value);

// Prototip funkcije za ispis stabla
void printtree(treenode* root);

// Prototip funkcije za inorder ispis
void inorder(treenode* root);

// Prototip funkcije za preorder ispis
void preorder(treenode* root);

// Prototip funkcije za postorder ispis
void postorder(treenode* root);

// Funkcija za ispis tabova ovisno o razini čvora
void printtabs(int numtabs);

// Funkcija za rekurzivni ispis stabla
void printtree_rec(treenode* root, int level);

int main() {
    treenode* root = NULL;

    // Umetanje brojeva u binarno stablo
    insertnumber(&root, 14);
    insertnumber(&root, 11);
    insertnumber(&root, 24);
    insertnumber(&root, 5);
    insertnumber(&root, 16);
    insertnumber(&root, 15);
    insertnumber(&root, 19);

    // Ispis binarnog stabla
    printf("Binary Tree:\n");
    printtree(root);

    // Inorder ispis
    printf("\nIN-ORDER:\n");
    inorder(root);
    printf("\n");

    // Preorder ispis
    printf("PRE-ORDER:\n");
    preorder(root);
    printf("\n");

    // Postorder ispis
    printf("POST-ORDER:\n");
    postorder(root);
    printf("\n\n");

    // Pretraga brojeva u stablu
    printf("Search Results:\n");
    printf("%d (%s)\n", 16, findnumber(root, 16) ? "Found" : "Not Found");
    printf("%d (%s)\n", 15, findnumber(root, 15) ? "Found" : "Not Found");
    printf("%d (%s)\n", 5, findnumber(root, 5) ? "Found" : "Not Found");
    printf("%d (%s)\n", 156, findnumber(root, 156) ? "Found" : "Not Found");
    printf("%d (%s)\n", 1, findnumber(root, 1) ? "Found" : "Not Found");

    // Oslobađanje memorije
    // ...

    return 0;
}

// Implementacija funkcije za stvaranje novog čvora
treenode* createnode(int value) {
    treenode* result = malloc(sizeof(treenode));
    if (result != NULL) {
        result->left = NULL;
        result->right = NULL;
        result->value = value;
    }
    return result;
}

// Implementacija funkcije za umetanje broja u stablo
bool insertnumber(treenode** rootptr, int value) {
    treenode* root = *rootptr;
    if (root == NULL) {
        // Stablo/prvi čvor je prazan
        (*rootptr) = createnode(value);
        return true;
    }
    if (value == root->value) {
        // Ne čini ništa ako se broj već nalazi u stablu
        return false;
    }
    if (value < root->value)
        return insertnumber(&(root->left), value);
    else
        return insertnumber(&(root->right), value);
}

// Implementacija funkcije za pretragu broja u stablu
bool findnumber(treenode* root, int value) {
    if (root == NULL)
        return false;
    if (root->value == value)
        return true;

    if (value < root->value)
        return findnumber(root->left, value);
    if (value > root->value)
        return findnumber(root->right, value);

    return false; // Nepotrebno, ali dodano radi jasnosti
}

// Implementacija funkcije za ispis stabla
void printtree(treenode* root) {
    printtree_rec(root, 0);
}

// Implementacija funkcije za rekurzivni ispis stabla
void printtree_rec(treenode* root, int level) {
    if (root == NULL) {
        printtabs(level);
        printf("<NULL>\n");
        return;
    }
    printtabs(level);
    printf("value = %d\n", root->value);
    printtabs(level);

    printf("left\n");
    printtree_rec(root->left, level + 1);
    printtabs(level);

    printf("right\n");
    printtree_rec(root->right, level + 1);
}

// Implementacija funkcije za ispis tabova ovisno o razini čvora
void printtabs(int numtabs) {
    for (int i = 0; i < numtabs; i++)
        printf("\t");
}

// Implementacija funkcije za inorder ispis
void inorder(treenode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

// Implementacija funkcije za preorder ispis
void preorder(treenode* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

// Implementacija funkcije za postorder ispis
void postorder(treenode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
}
