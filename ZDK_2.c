
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int godina_rodjenja;
    struct Osoba *next; //Ovo next sluzi za povezivanje lista međusobno
} Osoba;

Osoba* dodajNaPocetak(Osoba* head, const char ime[], const char prezime[], int god_rod) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba)); //Inicijliziranje novog elementa liste "nova" sta znaci nova osoba
    if (nova == NULL)
        printf("GRESKA!");

    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina_rodjenja = god_rod; //U ove 3 linije sam samo uvalia u element liste ime, prezime i godinu rodjenja

    nova->next = head->next; //Povezivanje novog elementa sa iducim koji ide iza njega.
    head->next =nova; //Prebacivanje head veze na novi element (head je prvi element liste i od njega prema desno ide lista)
    return head; //Vracam listu, ondsno njen prvi element
}

Osoba* dodajNaKraj(Osoba* head, const char ime[], const char prezime[], int god_rod) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba)); //nova osoba
    Osoba *temp = head; 
     
    if (nova == NULL)
        printf("GRESKA!");

    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina_rodjenja = god_rod;

    while (temp->next != NULL) {
        temp = temp->next;
    }                               //  Ovde provjeravam koji element ima vezu (next) na NULL, odnosno na onaj element koji je 
                                    //  zadnji element liste (zadnji element ima vezu NULL). Kada nađe NULL element, prekida se while i nastavlja kod dalje
    temp->next = nova;
    nova->next = NULL; //Na sličan način se ovde veze prespajaju, samo šta se ovde dodaje zadnji element
    return head; //Vraćanje prvog elementa liste
}

Osoba* pronadjiElement(Osoba* head, char prezime[]) {
    Osoba* temp = head;
    temp = temp->next; //Ovime odma mičem vezu sa heada na prvi element liste jer head nema nikakve atribute kao ostali elementi

    if (temp == NULL) {
        printf("Lista je prazna!\n"); 
        return NULL;
    }

    while (temp != NULL) {
        if (strcmp(prezime, temp->prezime) == 0) //Uspoređujem upisano prezime sa prezimenom svakog elementa liste
            return temp;
        
        temp = temp->next; //Ako nije naša prezime ide na idući element
    }

    if (temp == NULL)
        printf("\nElement nije pronadjen!"); //Javlja ako nema tog prezimena

    return NULL;
}

void izbrisiElement(Osoba* head, const char ime[], const char prezime[], int god_rod) {
    Osoba* temp = head;

    if (temp->next == NULL) {
        printf("Lista je prazna\n");
        return NULL;
    }

    while (temp->next != NULL){
        if (strcmp(temp->next->ime, ime) == 0 && strcmp(temp->next->prezime, prezime) == 0 && temp->next->godina_rodjenja == god_rod) {
            Osoba* brisi = temp->next;
            temp->next = brisi->next;
            free(brisi);
            return head; 
        }

        temp = temp->next;
    }

    return head;

}

void ispisListe(Osoba* head) {
    Osoba* temp = head;
    temp = temp->next;

    while (temp != NULL) {
        printf("%s %s\t[%d]\n", temp->ime, temp->prezime, temp->godina_rodjenja);
        temp = temp->next;
    }
}

int main() {
    Osoba* head, *pr_el;
    head = (Osoba*)malloc(sizeof(Osoba));
    pr_el = (Osoba*)malloc(sizeof(Osoba)); //Ovo sam samo kreira novu listu da ne radim sve u jednoj, mada je ista stvar
    head->next = NULL;
    pr_el = NULL;

    char fPrezime[] = "Maldic";
  
    head = dodajNaPocetak(head, "Ana", "Pavic", 1999);
    head = dodajNaPocetak(head, "Ivan", "Mekic", 1999);
    head = dodajNaPocetak(head, "Ante", "Maldic", 1999);

    printf("Lista:\n");
    ispisListe(head);

    head = dodajNaKraj(head, "Ivo", "Oop", 1989);
    head = dodajNaKraj(head, "Nikola", "Ivic", 1979);

    printf("\nLista 2:\n");
    ispisListe(head);

    pr_el = pronadjiElement(head, fPrezime);

    if (pr_el != NULL)
        printf("\nPronadjen: %s %s\t[%d]\n", pr_el->ime, pr_el->prezime, pr_el->godina_rodjenja);
 
    izbrisiElement(head, "Nikola", "Ivic", 1979);
    printf("\nLista 3:\n");
    ispisListe(head);

    return 0;
}