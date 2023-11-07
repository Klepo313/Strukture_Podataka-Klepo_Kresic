#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Polinom {
    int Koef;
    int Pot;
    struct Polinom* next;
} Polinom;

Polinom* dodajNaPocetak(Polinom* head, int koef, int pot);
void ispisPolinoma(Polinom* head);
void oslobodiListu(Polinom* head);

int main() {
    FILE* datoteka = fopen("polinomi.txt", "r");
    if (datoteka == NULL) {
        printf("Greška pri otvaranju datoteke.\n");
        return 1;
    }

    int koef[2][50] = { {0} };  // Inicijalizacija nizova za koeficijente za dva polinoma
    int pot[2][50] = { {0} };   // Inicijalizacija nizova za potencije za dva polinoma
    int broj_clanova[2] = { 0 }; // Brojači članova za dva polinoma

    char linija[255];

    int trenutni_polinom = 0; // Varijabla koja prati trenutni polinom (0 za prvi, 1 za drugi)

    while (fgets(linija, sizeof(linija), datoteka) != NULL) {
        if (strcmp(linija, "P(x)\n") == 0) {
            trenutni_polinom = 0;
            continue;
        }
        else if (strcmp(linija, "Q(x)\n") == 0) {
            trenutni_polinom = 1;
            continue;
        }

        if (sscanf(linija, "%dx^%d", &koef[trenutni_polinom][broj_clanova[trenutni_polinom]], &pot[trenutni_polinom][broj_clanova[trenutni_polinom]]) == 2) {
            broj_clanova[trenutni_polinom]++;
        }
    }

    fclose(datoteka);

    // Sortiranje članova po potencijama za oba polinoma
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < broj_clanova[i] - 1; j++) {
            for (int k = j + 1; k < broj_clanova[i]; k++) {
                if (pot[i][j] < pot[i][k]) {
                    // Zamijeni koeficijente i potencije ako je potencija veća
                    int temp_koef = koef[i][j];
                    int temp_pot = pot[i][j];

                    koef[i][j] = koef[i][k];
                    pot[i][j] = pot[i][k];

                    koef[i][k] = temp_koef;
                    pot[i][k] = temp_pot;
                }
            }
        }
    }

    // Ispis sortiranih članova
    for (int i = 0; i < 2; i++) {
        printf("Sortirani polinom %c(x) = ", i == 0 ? 'P' : 'Q');
        for (int j = 0; j < broj_clanova[i]; j++) {
            printf("%+dx^%d ", koef[i][j], pot[i][j]);
        }
        printf("\n");
    }

    // Stvaranje i ispis liste za oba polinoma
    Polinom* polinom_head[2] = { NULL };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < broj_clanova[i]; j++) {
            polinom_head[i] = dodajNaPocetak(polinom_head[i], koef[i][j], pot[i][j]);
        }
        printf("Polinom %c(x) kao lista:\n", i == 0 ? 'P' : 'Q');
        ispisPolinoma(polinom_head[i]);
    }

    // Oslobađanje memorije
    for (int i = 0; i < 2; i++) {
        oslobodiListu(polinom_head[i]);
    }

    return 0;
}

Polinom* dodajNaPocetak(Polinom* head, int koef, int pot) {
    Polinom* novi = (Polinom*)malloc(sizeof(Polinom));
    if (novi == NULL) {
        printf("Greška pri alokaciji memorije.\n");
        exit(1);
    }
    novi->Koef = koef;
    novi->Pot = pot;
    novi->next = head;
    return novi;
}

void ispisPolinoma(Polinom* head) {
    Polinom* trenutni = head;
    while (trenutni != NULL) {
        printf("%+dx^%d ", trenutni->Koef, trenutni->Pot);
        trenutni = trenutni->next;
    }
    printf("\n");
}

void oslobodiListu(Polinom* head) {
    Polinom* trenutni = head;
    while (trenutni != NULL) {
        Polinom* temp = trenutni;
        trenutni = trenutni->next;
        free(temp);
    }
}
