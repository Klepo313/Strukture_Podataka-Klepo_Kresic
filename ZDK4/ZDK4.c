#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Polinom {
    int Koef;
    int Pot;
    struct Polinom* next;
} Polinom;

int insertPoly(Polinom*, char[]);
int printList(Polinom*);
int addPolys(Polinom*, Polinom*);
int multiplyPolys(Polinom*, Polinom*);
int summPoly(Polinom*); //Funkcija koja sumira koef sa istim potencijama toga polinoma.

int main() {
    FILE* file = NULL;
    file = fopen("polinom.txt", "r");

    //Polinomi u datoteci spremljeni u dvije lokalne varijable char[]
    printf("polinomi.txt\n");
    char px[50] = { 0 }, qx[50] = { 0 };
    if (fgets(px, sizeof(px), file)){
        printf("%s", px); //Prvi red je Px
    }
    if (fgets(qx, sizeof(qx), file)) {
        printf("%s\n", qx); //Drugi red je Qx
    }

    //Alokacija lista polinoma Px i Qx
    Polinom * Px = NULL, * Qx = NULL;
    Px = (Polinom*)malloc(sizeof(Polinom));
    Qx = (Polinom*)malloc(sizeof(Polinom));

    if ((Px, Qx) == NULL) {
        printf("Greska pri alokaciji lista.\n");
        return -1;
    }

    //Unosi polinome iz lok. var. px[] u listu
    if (insertPoly(Px, px) == 1) {
        printf("\nPolinom u listi P(x): ");
        printList(Px);
    }
    if (insertPoly(Qx, qx) == 1) {
        printf("\nPolinom u listi Q(x): ");
        printList(Qx);
    }
    else {
        printf("Greska pri unosenju polinoma u listu.\n");
        return -1;
    }
    
    //Zbrajanje polinoma Px i Qx
    printf("\nZbrojeni P(x) i Q(x) polinomi:\n");
    addPolys(Px, Qx);

    //Mnozenje polinoma Px i Qx
    printf("\nPomnozeni P(x) i Q(x) polinomi:\n");
    multiplyPolys(Px, Qx);
}

int printList(Polinom* head) {
    Polinom* temp = head;
    temp = temp->next;

    if (temp == NULL) {
        printf("Lista je prazna.\n");
        return -1;
    }

    while (temp != NULL) {
        printf("%dx%d ", temp->Koef, temp->Pot);
        temp = temp->next;
    }

    return 1;
}

int summPoly(Polinom* poly) {
    /*Polinom* temp = NULL;
    temp = (Polinom*)malloc(sizeof(Polinom));*/
    Polinom* temp = poly;
    Polinom* resultPoly = NULL, * resultTemp = NULL;
    resultPoly = (Polinom*)malloc(sizeof(Polinom));
    resultTemp = resultPoly;

    if ((temp, resultPoly) == NULL) {
        printf("Greska pri alokaciji.\n");
        return -1;
    }

    temp = temp->next;
    while (temp != NULL) {

        resultTemp->next = (Polinom*)malloc(sizeof(Polinom));
        if (resultTemp->next == NULL) {
            printf("Greska u alokaciji polinoma.\n");
            return -1;
        }

        resultTemp->next->next = NULL;

        if (temp->next != NULL &&  temp->Pot == temp->next->Pot) {
            resultTemp->next->Koef = temp->Koef + temp->next->Koef;
            resultTemp->next->Pot = temp->Pot;
            temp = temp->next;
        }
        else {
            resultTemp->next->Koef = temp->Koef;
            resultTemp->next->Pot = temp->Pot;
        }
        temp = temp->next; 
        resultTemp = resultTemp->next;
    }

    //resultTemp->next = NULL; // Postavljanje poslednjeg čvora na NULL
    printList(resultPoly);
}

int insertPoly(Polinom* head, char poly[]) {
    Polinom* temp = head;

    if (temp == NULL) {
        printf("Greska u alokaciji ili je lista prazna.\n");
        return -1;
    }

    char* token = strtok(poly, " ");
    int i = 0;

    while (token != NULL) {
        Polinom* newPoly = NULL;
        newPoly = (Polinom*)malloc(sizeof(Polinom));

        if (newPoly == NULL) {
            printf("Greska u alokaciji ili je lista prazna.\n");
            return -1;
        }

        if (sscanf(token, "%dx%d", &newPoly->Koef, &newPoly->Pot) == 2) {
            temp->next = newPoly;
            newPoly->next = NULL;

            temp = newPoly;
        }
        else {
            free(newPoly);
        }
        //printf("Koef = %d, Pot = %d\n", newPoly->Koef, newPoly->Pot);

        i++;
        token = strtok(NULL, " ");
    }

    return 1;
}

int addPolys(Polinom* px, Polinom* qx) {
    Polinom* tempPx = px,
        * tempQx = qx,
        * resultPoly = NULL,
        * resultTemp = NULL;

    tempPx = tempPx->next;
    tempQx = tempQx->next;

    resultPoly = (Polinom*)malloc(sizeof(Polinom));
    resultTemp = resultPoly;

    if (tempPx == NULL || tempQx == NULL ||resultPoly == NULL) {
        printf("Liste su prazne ili je greska pri alokaciji.\n");
        return -1;
    }

    while (tempPx != NULL && tempQx != NULL) {

        resultTemp->next = (Polinom*)malloc(sizeof(Polinom));
        if (resultTemp->next == NULL) {
            printf("Greska u alokaciji polinoma.\n");
            return -1;
        }

        if (tempPx->Pot == tempQx->Pot) {

            resultTemp->next->Koef = tempPx->Koef + tempQx->Koef;
            resultTemp->next->Pot = tempPx->Pot;

            //printf("Koeficijenti upisani 1.\n");

            tempPx = tempPx->next;
            tempQx = tempQx->next;
        }
        else if (tempPx->Pot > tempQx->Pot) {
            // Ako je eksponent u px veći, kopiraj px
            resultTemp->next->Koef = tempPx->Koef;
            resultTemp->next->Pot = tempPx->Pot;
            tempPx = tempPx->next;
        }
        else {
            // Ako je eksponent u qx veći, kopiraj qx
            resultTemp->next->Koef = tempQx->Koef;
            resultTemp->next->Pot = tempQx->Pot;
            tempQx = tempQx->next;
        }
        resultTemp = resultTemp->next;
    }

    // Dodavanje preostalih članova iz px ili qx (ako postoje)
    while (tempPx != NULL) {
        resultTemp->next = (Polinom*)malloc(sizeof(Polinom));
        if (resultTemp->next == NULL) {
            printf("Greska u alokaciji rezultujuceg polinoma.\n");
            return -1;
        }

        resultTemp->next->Koef = tempPx->Koef;
        resultTemp->next->Pot = tempPx->Pot;
        tempPx = tempPx->next;
        resultTemp = resultTemp->next;
    }

    while (tempQx != NULL) {
        resultTemp->next = (Polinom*)malloc(sizeof(Polinom));
        if (resultTemp->next == NULL) {
            printf("Greska u alokaciji rezultujuceg polinoma.\n");
            return -1;
        }

        resultTemp->next->Koef = tempQx->Koef;
        resultTemp->next->Pot = tempQx->Pot;
        tempQx = tempQx->next;
        resultTemp = resultTemp->next;
    }

    resultTemp->next = NULL; // Postavljanje poslednjeg čvora na NULL

    printList(resultPoly);
    return 1;
}

int multiplyPolys(Polinom* px, Polinom* qx) {
    Polinom* tempPx = px, * tempQx = qx;
    if (tempPx == NULL || tempQx == NULL) {
        printf("Lista prazna.\n");
        return -1;
    }

    Polinom* resultPoly = NULL, *resultTemp = NULL;
    resultPoly = (Polinom*)malloc(sizeof(Polinom));
    resultTemp = resultPoly;

    if (resultPoly == NULL || resultTemp == NULL) {
        printf("Lista prazna.\n");
        return -1;
    }

    tempPx = tempPx->next;
    tempQx = tempQx->next;

    while (tempPx != NULL) {
        while (tempQx != NULL) {

            resultTemp->next = (Polinom*)malloc(sizeof(Polinom));
            if (resultTemp == NULL) {
                printf("Greska pri alokaciji novog elementa liste.\n");
                return -1;
            }

            resultTemp->next->Koef = tempPx->Koef * tempQx->Koef;
            resultTemp->next->Pot = tempPx->Pot + tempQx->Pot;

            tempQx = tempQx->next;
            resultTemp = resultTemp->next;
        }

        tempPx = tempPx->next;
        tempQx = qx->next;
    }

    resultTemp->next = NULL;

    //summPoly(resultPoly);
    printList(resultPoly);
    return 1;
}

