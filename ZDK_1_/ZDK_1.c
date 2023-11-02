#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Student {
    char ime[100];
    char prezime[100];
    int bodovi;
} Student;

int prebrojiStudente(FILE* f) {
    int br = 0;
    char ch;

    while (!feof(f)) {
        ch = fgetc(f);
        if (ch == '\n')
            br++;
    }

    rewind(f);
    return br;
}

void ucitajStudente(FILE* f, Student* studenti, int br) {
    for (int i = 0; i < br; i++)
        fscanf(f, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
}

void ispisStudenta(Student student) {
    printf("%s\t%s\t\t%d/20\t\t%.0f%%\n",
        student.ime, student.prezime, student.bodovi, (float)(student.bodovi * 100) / 20);
}

void ispisStudenti(Student* studenti, int br) {
    printf("STUDENTI:\n");
    printf("IME\tPREZIME\t\tBODOVI\t\tPOSTOTAK\n");
    for (int i = 0; i < br; i++) {
        ispisStudenta(studenti[i]);
    }
}

int main() {
    FILE* f = fopen("../studenti.txt", "r");
    if (f == NULL) {
        printf("Ne mogu otvoriti datoteku 'studenti.txt'.");
        return 1;
    }

    int br = prebrojiStudente(f);
    Student* studenti;
    studenti = (Student*)malloc(br * sizeof(Student));

    if (studenti == NULL)
        return -1;

    ucitajStudente(f, studenti, br);
    ispisStudenti(studenti, br);

    fclose(f);
    free(studenti);
    return 0;
}
