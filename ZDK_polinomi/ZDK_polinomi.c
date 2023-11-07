//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define maxPot 5
//
////typedef struct Poli* Polinom;
//
//typedef struct Polinom {
//	int Koef;
//	int Pot;
//	struct Polinom* next;
//} Polinom;
//
////int loadPol(Polinom *, char pol[]);
//int sortPol(char pol[], int koef[], int pot[]);
//int getKoefPot(char[], int[], int[], int);
////void printPol(Polinom*);
//
//int main() {
//
//	//Inicijalizacija i provjera file-a
//	FILE* file;
//	file = fopen("polinomi.txt", "r");
//	if (file == NULL) {
//		printf("Datoteka nije pronadjena\n");
//		return -1;
//	}
//
//	char px[50] = {}, qx[50] = {};
//	int koef_px[10] = { 0 }, koef_qx[10] = { 0 },
//		pot_px[10] = { 0 }, pot_qx[10] = { 0 },
//		noChar_px = 0, noChar_qx = 0;
//
//	if (fgets(px, sizeof(px), file) != NULL) {
//		printf("P(x) = %s", px);
//	}
//	if (fgets(qx, sizeof(qx), file) != NULL) {
//		printf("Q(x) = %s\n", qx);
//	}
//	else {
//		printf("Greška pri citanju iz datoteke.\n");
//		fclose(file);
//		return -1;
//	}
//
//	printf("\nP(x) atributi:\n");
//	getKoefPot(px, koef_px, pot_px, noChar_px);
//
//	printf("\nQ(x) atributi:\n");
//	getKoefPot(qx, koef_qx, pot_qx, noChar_qx);
//
//	//Liste za dva polinoma Px i Qx
//	/*Polinom* Px = NULL, * Qx = NULL;
//	Px = (Polinom* )malloc(sizeof(Polinom));
//	Qx = Px;
//
//	if (Px == NULL || Qx == NULL) {
//		printf("Greska pri din. alokaciji liste\n");
//		return -1;
//	}*/
//
//	//Sortiranje polinoma
//	//sortPol(px, )
//
//	/*if (loadPol(Px, px) == 1) {
//		printPol(Px);
//	}
//	if (loadPol(Qx, qx) == 1) {
//		printPol(Px);
//	} 
//	else {
//		printf("Krivo ucitana lista\n");
//		return -1;
//	}*/
//
//
//	return 0;
//}
//
////void printPol(Polinom *head) {
////	Polinom* temp = head;
////	temp = temp->next;
////
////	if (temp == NULL)
////		printf("Lista je prazna!\n");
////
////	while (temp != NULL){
////		printf("%dx^%d ", temp->Koef, temp->Pot);
////		temp = temp->next;
////	}
////}
//
////int loadPol(Polinom *head, char pol[]) {
////	Polinom* newPol = NULL;
////	newPol = (Polinom*)malloc(sizeof(Polinom));
////	
////	char ch[255] = {};
////
////	for (int i = 0; i < sizeof(pol); i++) {
////		ch[i] = pol[i];
////
////		if (ch[i] == 'x') {
////			return 1;
////		}
////	}
////}
//
//int getKoefPot(char pol[], int koef[], int pot[], int noChar) {
//	char* token = strtok(pol, "+"); // Razdvajamo string na članove koristeći znak '+'
//
//	while (token != NULL) {
//		char* x_pos = strchr(token, 'x'); // Pronalazimo poziciju znaka 'x' u trenutnom članu
//
//		if (x_pos != NULL) {
//			// Ako postoji 'x' u trenutnom članu
//			char* caret_pos = strchr(x_pos, '^'); // Pronalazimo poziciju znaka '^'
//			if (caret_pos != NULL) {
//				*caret_pos = '\0'; // Postavljamo null terminator nakon 'x'
//				pol[noChar] = atoi(token); // Pretvaramo koeficijent u cijeli broj
//				pot[noChar] = atoi(caret_pos + 1); // Preskačemo '^' i pretvaramo potenciju u cijeli broj
//			}
//		}
//		else {
//			// Ako nema 'x' u trenutnom članu
//			pol[noChar] = atoi(token); // Koeficijent je cijeli broj iz trenutnog člana
//			pot[noChar] = 0; // Potencija je 0
//		}
//		noChar++;
//		token = strtok(NULL, "+"); // Prelazimo na sljedeći član
//	}
//
//	// Ispis koeficijenata i potencija
//	for (int i = 0; i < noChar; i++) {
//		printf("Koeficijent %d: %d, Potencija %d: %d\n", i + 1, koef[i], i + 1, pot[i]);
//	}
//	return 1;
//}
//
//int sortPol(char pol[], int koef[], int pot[]) {
//	return 1;
//}