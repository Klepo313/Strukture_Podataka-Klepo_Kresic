#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int godina_rodjenja;
    struct Osoba* next; //Ovo next sluzi za povezivanje lista međusobno
} Osoba;

Osoba* dodajNaPocetak(Osoba* head, const char ime[], const char prezime[], int god_rod);
Osoba* dodajNaKraj(Osoba* head, const char ime[], const char prezime[], int god_rod);
Osoba* pronadjiElement(Osoba* head, char prezime[]);
void izbrisiElement(Osoba* head, const char ime[], const char prezime[], int god_rod);
Osoba* dodajIza(Osoba* head, const char ime[], const char prezime[], int god_rod, const char tr_prezime[]);
Osoba* dodajIspred(Osoba* head, const char ime[], const char prezime[], int god_rod, const char tr_prezime[]);
void ispisListe(Osoba* head);

void upisiListuUdatoteku(Osoba* head, FILE *file);
int ispisiListuIzDatoteke(FILE* file);

int main() {
    Osoba* head, *pronadji_element, *datoteka_lista;

    head = (Osoba*)malloc(sizeof(Osoba));
    pronadji_element = (Osoba*)malloc(sizeof(Osoba)); 
    //datoteka_lista = (Osoba*)malloc(sizeof(Osoba)); //Ovo sam samo kreira novu listu da ne radim sve u jednoj, mada je ista stvar
    
    head->next = NULL;
    pronadji_element = NULL;
    //datoteka_lista->next = NULL;

    if (head == NULL){
        printf("GRESKA\n"); return -1;
    }

    //Inicijalizacija file-a 'lista.txt'
    FILE* lista = NULL, *lista_read = NULL;
    lista = fopen("lista.txt", "w");
    lista_read = fopen("lista_2.txt", "r");
    if (lista == NULL || lista_read == NULL) {
        printf("Greska u otvaranju datoteke.\n");
        return -1;
    }

    //Dodavanje na pocetak
    head = dodajNaPocetak(head, "Amela", "Pavic", 1999);
    head = dodajNaPocetak(head, "Ivan", "Mekic", 1999);
    head = dodajNaPocetak(head, "Ante", "Maldic", 1999);

    printf("Lista:\n");
    ispisListe(head);

    //Dodavanje na kraj
    head = dodajNaKraj(head, "Ivona", "Opara", 1989);
    head = dodajNaKraj(head, "Nikola", "Ivic", 1979);

    printf("\nLista 2:\n");
    ispisListe(head);

    //Trazenje elementa
    char fPrezime[] = "Maldic";
    pronadji_element = pronadjiElement(head, fPrezime);

    if (pronadji_element != NULL)
        printf("\nPronadjen: %s %s\t[%d]\n", pronadji_element->ime, pronadji_element->prezime, pronadji_element->godina_rodjenja);

    //Brisanje elementa
    izbrisiElement(head, "Nikola", "Ivic", 1979);
    printf("\nLista 3:\n");
    ispisListe(head);

    //Dodavanje ispred odredjenog elementa
    dodajIspred(head, "Mateo", "Kovac", 1989, "Mekic");
    printf("\nLista 4:\n");
    ispisListe(head);

    //Dodavanje iza odredjenog elementa
    dodajIza(head, "Marino", "Maric", 1989, "Mekic");
    printf("\nLista 4:\n");
    ispisListe(head);

    //Upisivanje liste u datoteku
    upisiListuUdatoteku(head, lista);

    //Ispis liste iz datoteke
    ispisiListuIzDatoteke(lista_read);
    
    fclose(lista);
    return 0;
}

Osoba* dodajNaPocetak(Osoba* head, const char ime[], const char prezime[], int god_rod) {
    Osoba* nova = NULL; //Inicijliziranje novog elementa liste "nova" sta znaci nova osoba
    nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL)
        printf("GRESKA!");

    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina_rodjenja = god_rod; //U ove 3 linije sam samo uvalia u element liste ime, prezime i godinu rodjenja

    nova->next = head->next; //Povezivanje novog elementa sa iducim koji ide iza njega.
    head->next = nova; //Prebacivanje head veze na novi element (head je prvi element liste i od njega prema desno ide lista)
    return head; //Vracam listu, ondsno njen prvi element
}

Osoba* dodajNaKraj(Osoba* head, const char ime[], const char prezime[], int god_rod) {
    Osoba* nova = NULL; //Inicijliziranje novog elementa liste "nova" sta znaci nova osoba
    nova = (Osoba*)malloc(sizeof(Osoba));
    Osoba* temp = head;

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
    nova->next = NULL; //Na slican nacin se ovde veze prespajaju, samo šta se ovde dodaje zadnji element
    return head; //Vraćanje prvog elementa liste
}

Osoba* pronadjiElement(Osoba* head, char prezime[]) {
    Osoba* temp = head;
    temp = temp->next; //Ovime odma micem vezu sa heada na prvi element liste jer head nema nikakve atribute kao ostali elementi

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

    while (temp->next != NULL) {
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

Osoba* dodajIspred(Osoba* head, const char ime[], const char prezime[], int god_rod, const char tr_prezime[]) {
    //Funckija kao parametar tr_prezime prima prezime ispred kojeg ce umetnit element
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
    Osoba* temp = head;

    if (nova == NULL)
        printf("GRESKA!");

    if (temp == NULL)
        printf("Greska!\n");

    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina_rodjenja = god_rod;

    int prezimeNadjeno = 0;

    while (temp != NULL && temp->next != NULL) {
        if (strcmp(tr_prezime, temp->next->prezime) == 0) {
            prezimeNadjeno = 1;
            break;
        }

        temp = temp->next;
    }

    if (prezimeNadjeno) {
        nova->next = temp->next;
        temp->next = nova;
        return head;
    }
    else {
        printf("\nPrezime '%s' nije pronadjeno u listi.\n", tr_prezime);
        free(nova);
    }

}

Osoba* dodajIza(Osoba* head, const char ime[], const char prezime[], int god_rod, const char tr_prezime[]) {
    //Funckija kao parametar tr_prezime prima prezime iza kojeg ce umetnit element
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
    Osoba* temp = head;

    if (nova == NULL)
        printf("GRESKA!");
    if (temp == NULL)
        printf("Greska!\n");

    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina_rodjenja = god_rod;

    int prezimeNadjeno = 0;

    while (temp != NULL) {
        if (strcmp(tr_prezime, temp->prezime) == 0) {
            prezimeNadjeno = 1;
            break;
        }

        temp = temp->next;
    }

    if (prezimeNadjeno) {
        nova->next = temp->next->next;
        temp->next = nova;
        return head;
    }
    else {
        printf("\nPrezime '%s' nije pronadjeno u listi.\n", tr_prezime);
        free(nova);
    }

}

void ispisListe(Osoba* head) {
    Osoba* temp = head;
    temp = temp->next;

    if (temp == NULL)
        printf("Greska!\n");

    while (temp != NULL) {
        printf("%s %s\t[%d]\n", temp->ime, temp->prezime, temp->godina_rodjenja);
        temp = temp->next;
    }
}

void upisiListuUdatoteku(Osoba* head, FILE *file) {
    Osoba* temp = head;
    temp = temp->next;

    if (temp == NULL)
        printf("Greska. Lista je prazna.\n");

    fprintf(file, "IME\t\tPREZIME\t\tGODINA_RODJENJA\n");

    while (temp != NULL){
        fprintf(file, "%s\t%s\t\t%d\n", temp->ime, temp->prezime, temp->godina_rodjenja);
        temp = temp->next;
    }

    printf("\nLista je upisana u datoteku 'lista.txt'.\n");
}

int ispisiListuIzDatoteke(FILE* file) {
    Osoba* head = NULL;  // Glava liste za ucitavanje
    Osoba* temp = NULL;  // Trenutni cvor za iteraciju kroz listu

    char ime[50] = "/", prezime[50] = "/";
    int godina_rodjenja = 0000;

    // Preskoči prvu liniju
    char c[1024];
    if (fgets(c, sizeof(c), file) == NULL) {
        printf("Datoteka je prazna ili ne može se pročitati.\n");
        return 0;
    }

    while (fscanf(file, "%s\t%s\t%d", ime, prezime, &godina_rodjenja) == 3) {
        Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

        if (nova == NULL) {
            printf("Greška pri alokaciji memorije.\n");
            fclose(file);
            return 0;
        }

        strcpy(nova->ime, ime);
        strcpy(nova->prezime, prezime);
        nova->godina_rodjenja = godina_rodjenja;
        nova->next = NULL;

        if (head == NULL) {
            head = nova;
            temp = nova;
        }
        else {
            temp->next = nova;
            temp = nova;
        }
    }

    if (head == NULL) {
        printf("Lista iz datoteke je prazna.\n");
    }
    else {
        printf("\nLista iz datoteke:\n");
        ispisListe(head);
    }

    // Oslobodi memoriju alociranu za listu iz datoteke
    while (head != NULL) {
        Osoba* brisi = head;
        head = head->next;
        free(brisi);
    }

    return 1;
}

