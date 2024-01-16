#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktura za čvor gradova
typedef struct Grad {
    char ime[50];
    int broj_stanovnika;
    struct Grad* next;
} Grad;

// Struktura za čvor država
typedef struct Drzava {
    char ime[50];
    Grad* gradovi;  // Vezana lista gradova
    struct Drzava* next;
} Drzava;

// Funkcija za dodavanje grada u vezanu listu gradova
void dodajGrad(Grad** head, char ime[50], int broj_stanovnika) {
    Grad* noviGrad = (Grad*)malloc(sizeof(Grad));
    strcpy(noviGrad->ime, ime);
    noviGrad->broj_stanovnika = broj_stanovnika;
    noviGrad->next = NULL;

    if (*head == NULL || broj_stanovnika < (*head)->broj_stanovnika) {
        noviGrad->next = *head;
        *head = noviGrad;
    }
    else {
        Grad* trenutni = *head;
        while (trenutni->next != NULL && broj_stanovnika > trenutni->next->broj_stanovnika) {
            trenutni = trenutni->next;
        }
        noviGrad->next = trenutni->next;
        trenutni->next = noviGrad;
    }
}

// Funkcija za dodavanje države u vezanu listu država
void dodajDrzavu(Drzava** head, char ime[50], Grad* gradovi) {
    Drzava* novaDrzava = (Drzava*)malloc(sizeof(Drzava));
    strcpy(novaDrzava->ime, ime);
    novaDrzava->gradovi = gradovi;
    novaDrzava->next = NULL;

    if (*head == NULL || strcmp(ime, (*head)->ime) < 0) {
        novaDrzava->next = *head;
        *head = novaDrzava;
    }
    else {
        Drzava* trenutna = *head;
        while (trenutna->next != NULL && strcmp(ime, trenutna->next->ime) > 0) {
            trenutna = trenutna->next;
        }
        novaDrzava->next = trenutna->next;
        trenutna->next = novaDrzava;
    }
}

// Funkcija za ispis gradova u vezanoj listi
void ispisiGradove(Grad* head) {
    Grad* trenutni = head;
    while (trenutni != NULL) {
        printf("%s, %d\n", trenutni->ime, trenutni->broj_stanovnika);
        trenutni = trenutni->next;
    }
}

// Funkcija za ispis država i gradova
void ispisiDrzave(Drzava* head) {
    Drzava* trenutna = head;
    while (trenutna != NULL) {
        printf("Drzava: %s\n", trenutna->ime);
        printf("Gradovi:\n");
        ispisiGradove(trenutna->gradovi);
        printf("\n");
        trenutna = trenutna->next;
    }
}

// Funkcija za pretragu gradova određene države s brojem stanovnika većim od unosa
void pretraziGradove(Drzava* head, char trazenaDrzava[50], int brojStanovnika) {
    Drzava* trenutna = head;
    while (trenutna != NULL) {
        if (strcmp(trenutna->ime, trazenaDrzava) == 0) {
            Grad* grad = trenutna->gradovi;
            printf("Gradovi u %s s brojem stanovnika većim od %d:\n", trazenaDrzava, brojStanovnika);
            while (grad != NULL) {
                if (grad->broj_stanovnika > brojStanovnika) {
                    printf("%s, %d\n", grad->ime, grad->broj_stanovnika);
                }
                grad = grad->next;
            }
            return;
        }
        trenutna = trenutna->next;
    }
    printf("Drzava %s nije pronađena.\n", trazenaDrzava);
}

int main() {
    FILE* drzaveFile = fopen("drzave.txt", "r");

    if (drzaveFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    Drzava* listaDrzava = NULL;

    char imeDrzave[50];
    char imeDatoteke[50];

    // Čitanje datoteke drzave.txt i formiranje listaDrzava
    while (fscanf(drzaveFile, "%s %s", imeDrzave, imeDatoteke) == 2) {
        FILE* gradoviFile = fopen(imeDatoteke, "r");

        if (gradoviFile == NULL) {
            perror("Error opening file");
            fclose(drzaveFile);
            return 1;
        }

        Grad* listaGradova = NULL;

        char imeGrada[50];
        int brojStanovnika;

        // Čitanje datoteke gradova i formiranje listaGradova
        while (fscanf(gradoviFile, "%[^,], %d", imeGrada, &brojStanovnika) == 2) {
            dodajGrad(&listaGradova, imeGrada, brojStanovnika);
        }

        fclose(gradoviFile);

        // Dodavanje države u vezanu listu država
        dodajDrzavu(&listaDrzava, imeDrzave, listaGradova);
    }

    fclose(drzaveFile);

    // Ispis država i gradova
    printf("Drzave i gradovi:\n");
    ispisiDrzave(listaDrzava);

    // Traženje gradova po državi s brojem stanovnika većim od unosa
    char trazenaDrzava[50];
    int brojStanovnika;

    printf("\nUnesite drzavu za pretragu: ");
    scanf("%s", trazenaDrzava);

    printf("Unesite broj stanovnika za pretragu: ");
    scanf("%d", &brojStanovnika);

    pretraziGradove(listaDrzava, trazenaDrzava, brojStanovnika);

    return 0;
}
