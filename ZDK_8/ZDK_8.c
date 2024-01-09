#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct BinaryTreenode {
    int value;
    struct BinaryTreenode* left;
    struct BinaryTreenode* right;
} BinaryTreenode;

// Stvaranje novog cvora
BinaryTreenode* createnode(int value);

// Umetanje broja u stablo
bool insertnumber(BinaryTreenode** rootptr, int value);

// Pretraga broja u stablu kao bool
bool findnumber(BinaryTreenode* root, int value);

// Pretraga broja u stablu kao pokazivač na strukturu
BinaryTreenode* findNode(BinaryTreenode* root, int value);

// Ispis stabla
void printtree(BinaryTreenode* root);

// Inorder ispis
void inorder(BinaryTreenode* root);

// Preorder ispis
void preorder(BinaryTreenode* root);

// Postorder ispis
void postorder(BinaryTreenode* root);

// Ispis tabova ovisno o razini cvora
void printtabs(int numtabs);

// Rekurzivni ispis stabla
void printtree_rec(BinaryTreenode* root, int level);

// Rekurzivna funckija za oslobađanje memorije za cvorove stabla
void freetree(BinaryTreenode* root);

// Brisanje elementa
void deletenode(BinaryTreenode*, int);

int main() {
    BinaryTreenode* root = NULL;

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

    // Brisanje elementa iz stabla
    deletenode(root, 24);
    printf("--");
    deletenode(root, 19);
    printf("Izbrisani broj 24 i 19\n");

    // Ispis binarnog stabla
    printf("\nNew Binary Tree:\n");
    printtree(root);

    // Oslobadjanje memorije
    freetree(root);

    return 0;
}

BinaryTreenode* createnode(int value) {
    BinaryTreenode* result = malloc(sizeof(BinaryTreenode));
    if (result != NULL) {
        result->left = NULL;
        result->right = NULL;
        result->value = value;
    }
    return result;
}

bool insertnumber(BinaryTreenode** rootptr, int value) {
    BinaryTreenode* root = *rootptr;
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

bool findnumber(BinaryTreenode* root, int value) {
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

void printtree(BinaryTreenode* root) {
    printtree_rec(root, 0);
}

void printtree_rec(BinaryTreenode* root, int level) {
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

void inorder(BinaryTreenode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

void preorder(BinaryTreenode* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(BinaryTreenode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
}

void freetree(BinaryTreenode* root) {
    if (root != NULL) {
        freetree(root->left);
        freetree(root->right);
        free(root);
    }
}

BinaryTreenode* findNode(BinaryTreenode* root, int value) {
    if (root == NULL)
        return NULL;

    if (root->value == value)
        return root;

    if (value < root->value)
        return findNode(root->left, value);
    if (value > root->value)
        return findNode(root->right, value);

    return NULL;
}


void deletenode(BinaryTreenode** rootptr, int value) {
    BinaryTreenode* root = *rootptr;

    if (root == NULL) {
        // Stablo je prazno
        printf("Tree is empty.\n");
        return;
    }

    BinaryTreenode* parent = NULL;
    BinaryTreenode* current = root;

    // Traži element koji se treba izbrisati
    while (current != NULL && current->value != value) {
        parent = current;
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) {
        // Element nije pronađen u stablu
        printf("Element not found in the tree.\n");
        return;
    }

    // Slučaj 1: Element nema djece ili ima samo jedno dijete
    if (current->left == NULL || current->right == NULL) {
        BinaryTreenode* newChild = (current->left != NULL) ? current->left : current->right;

        if (parent == NULL) {
            // Element je korijen stabla
            *rootptr = newChild;
        }
        else {
            // Element je dijete roditelja
            if (parent->left == current)
                parent->left = newChild;
            else
                parent->right = newChild;
        }

        free(current);
    }
    // Slučaj 2: Element ima oba djeteta
    else {
        // Pronađi nasljednika (najmanji element u desnom podstablu)
        BinaryTreenode* successorParent = current->right;
        BinaryTreenode* successor = current->right;

        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        // Zamijeni vrijednost trenutnog čvora s vrijednosti nasljednika
        current->value = successor->value;

        // Ponovno poziva funkciju brisanja za nasljednika
        deletenode(&successorParent->left, successor->value);
    }
}
