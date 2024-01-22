#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define FILE_OPEN_ERROR 1
#define MEMORY_ALLOCATION_ERROR 1
#define HASH_TABLE_SIZE 11

// Struktura za čvor gradova
typedef struct Grad {
    char ime[MAX_NAME_LENGTH];
    int broj_stanovnika;
    struct Grad* next;
} Grad;

// Struktura za čvor država
typedef struct Drzava {
    char ime[MAX_NAME_LENGTH];
    Grad* gradovi;  // Vezana lista gradova
    struct Drzava* next;
} Drzava;

// Struktura za hash tablicu
typedef struct HashTable {
    Drzava* buckets[HASH_TABLE_SIZE];
} HashTable;

// Funkcija za dodavanje grada u vezanu listu gradova
void dodajGrad(Grad** head, char ime[MAX_NAME_LENGTH], int broj_stanovnika) {
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
void dodajDrzavu(Drzava** head, char ime[MAX_NAME_LENGTH], Grad* gradovi) {
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
void pretraziGradove(Drzava* head, char trazenaDrzava[MAX_NAME_LENGTH], int brojStanovnika) {
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

// Funkcija za izračunavanje hash vrijednosti za ime države
unsigned int izracunajHash(char* imeDrzave) {
    unsigned int hashVrijednost = 0;
    int i = 0;
    while (i < 5 && imeDrzave[i] != '\0') {
        hashVrijednost += (unsigned int)imeDrzave[i];
        i++;
    }
    return hashVrijednost % HASH_TABLE_SIZE;
}

// Funkcija za dodavanje države u hash tablicu
void dodajDrzavuUHash(HashTable* hashTablica, Drzava* novaDrzava) {
    unsigned int indeks = izracunajHash(novaDrzava->ime);

    if (hashTablica->buckets[indeks] == NULL) {
        hashTablica->buckets[indeks] = novaDrzava;
        novaDrzava->next = NULL;
    }
    else {
        // Rješavanje kolizije dodavanjem nove države u vezanu listu na ovom indeksu
        novaDrzava->next = hashTablica->buckets[indeks];
        hashTablica->buckets[indeks] = novaDrzava;
    }
}

// Funkcija za pretragu države u hash tablici
Drzava* pretraziDrzavuUHash(HashTable* hashTablica, char* imeDrzave) {
    unsigned int indeks = izracunajHash(imeDrzave);
    Drzava* trenutnaDrzava = hashTablica->buckets[indeks];

    while (trenutnaDrzava != NULL && strcmp(trenutnaDrzava->ime, imeDrzave) != 0) {
        trenutnaDrzava = trenutnaDrzava->next;
    }

    return trenutnaDrzava;
}

// Funkcija za ispis svih država iz hash tablice
void ispisiSveDrzaveIzHash(HashTable* hashTablica) {
    for (int indeks = 0; indeks < HASH_TABLE_SIZE; indeks++) {
        Drzava* trenutnaDrzava = hashTablica->buckets[indeks];

        while (trenutnaDrzava != NULL) {
            printf("\n%s", trenutnaDrzava->ime);
            ispisiGradove(trenutnaDrzava->gradovi);
            trenutnaDrzava = trenutnaDrzava->next;
        }
    }
}

int main() {
    FILE* datotekaDrzava = fopen("drzave.txt", "r");

    if (datotekaDrzava == NULL) {
        perror("Greška pri otvaranju datoteke");
        return FILE_OPEN_ERROR;
    }

    HashTable* hashTablica = (HashTable*)malloc(sizeof(HashTable));
    if (hashTablica == NULL) {
        perror("Greška pri alociranju memorije");
        fclose(datotekaDrzava);
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTablica->buckets[i] = NULL;
    }

    char imeDrzave[MAX_NAME_LENGTH];
    char imeDatotekeGradova[MAX_NAME_LENGTH];

    // Čitanje datoteke drzave.txt i formiranje hashTablice
    while (fscanf(datotekaDrzava, "%s %s", imeDrzave, imeDatotekeGradova) == 2) {
        FILE* datotekaGradova = fopen(imeDatotekeGradova, "r");

        if (datotekaGradova == NULL) {
            perror("Greška pri otvaranju datoteke");
            fclose(datotekaDrzava);
            free(hashTablica);
            return FILE_OPEN_ERROR;
        }

        Grad* listaGradova = NULL;

        char imeGrada[MAX_NAME_LENGTH];
        int brojStanovnika;

        // Čitanje datoteke gradova i formiranje listaGradova
        while (fscanf(datotekaGradova, "%[^,], %d", imeGrada, &brojStanovnika) == 2) {
            dodajGrad(&listaGradova, imeGrada, brojStanovnika);
        }

        fclose(datotekaGradova);

        // Dodavanje države u hashTablicu
        Drzava* novaDrzava = (Drzava*)malloc(sizeof(Drzava));
        if (novaDrzava == NULL) {
            perror("Greška pri alociranju memorije");
            fclose(datotekaDrzava);
            free(hashTablica);
            return MEMORY_ALLOCATION_ERROR;
        }

        strcpy(novaDrzava->ime, imeDrzave);
        novaDrzava->gradovi = listaGradova;

        dodajDrzavuUHash(hashTablica, novaDrzava);
    }

    fclose(datotekaDrzava);

    // Ispis država i gradova iz hash tablice
    printf("Drzave i gradovi:\n");
    ispisiSveDrzaveIzHash(hashTablica);

    // Pretraga gradova u državi s brojem stanovnika većim od unosa korisnika
    char trazenaDrzava[MAX_NAME_LENGTH];
    int brojStanovnikaCilj = 0;

    printf("\nUnesite drzavu za pretragu: ");
    scanf("%s", trazenaDrzava);

    printf("Unesite broj stanovnika za pretragu: ");
    scanf("%d", &brojStanovnikaCilj);

    pretraziGradove(hashTablica->buckets[izracunajHash(trazenaDrzava)], trazenaDrzava, brojStanovnikaCilj);

    // Oslobađanje alocirane memorije
    // ...

    return 0;
}
