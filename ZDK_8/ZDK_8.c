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

// Stvaranje novog cvora
treenode* createnode(int value);

// Umetanje broja u stablo
bool insertnumber(treenode** rootptr, int value);

// Pretraga broja u stablu
bool findnumber(treenode* root, int value);

// Ispis stabla
void printtree(treenode* root);

// Inorder ispis
void inorder(treenode* root);

// Preorder ispis
void preorder(treenode* root);

// Postorder ispis
void postorder(treenode* root);

// Ispis tabova ovisno o razini cvora
void printtabs(int numtabs);

// Rekurzivni ispis stabla
void printtree_rec(treenode* root, int level);

// Rekurzivna funckija za oslobađanje memorije za cvorove stabla
void freetree(treenode* root);

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
    printf("%d\t(%s)\n", 16, findnumber(root, 16) ? "Found" : "Not Found");
    printf("%d\t(%s)\n", 15, findnumber(root, 15) ? "Found" : "Not Found");
    printf("%d\t(%s)\n", 5, findnumber(root, 5) ? "Found" : "Not Found");
    printf("%d\t(%s)\n", 156, findnumber(root, 156) ? "Found" : "Not Found");
    printf("%d\t(%s)\n", 1, findnumber(root, 1) ? "Found" : "Not Found");

    // Oslobadjanje memorije
    freetree(root);

    return 0;
}

treenode* createnode(int value) {
    treenode* result = malloc(sizeof(treenode));
    if (result != NULL) {
        result->left = NULL;
        result->right = NULL;
        result->value = value;
    }
    return result;
}

bool insertnumber(treenode** rootptr, int value) {
    treenode* root = *rootptr;
    if (root == NULL) {
        // Stablo/prvi cvor je prazan
        (*rootptr) = createnode(value);
        return true;
    }
    if (value == root->value) {
        // Ako je broj vec u stablu, preskoci
        return false;
    }
    if (value < root->value)
        return insertnumber(&(root->left), value);
    else
        return insertnumber(&(root->right), value);
}

bool findnumber(treenode* root, int value) {
    if (root == NULL)
        return false;
    if (root->value == value)
        return true;

    if (value < root->value)
        return findnumber(root->left, value);
    if (value > root->value)
        return findnumber(root->right, value);

    return false; //mozda nepotrebno, dodano cisto radi jasnoce
}

void printtree(treenode* root) {
    printtree_rec(root, 0);
}

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

void printtabs(int numtabs) {
    for (int i = 0; i < numtabs; i++)
        printf("\t");
}

void inorder(treenode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

void preorder(treenode* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(treenode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
}

void freetree(treenode* root) {
    if (root != NULL) {
        freetree(root->left);
        freetree(root->right);
        free(root);
    }
}