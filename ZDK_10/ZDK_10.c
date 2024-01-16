//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct Country {
//	char nameOfCountry[50];
//	struct Country* next;
//	struct Country* left;
//	struct Country* right;
//} Country;
//
//typedef struct City {
//	char nameOfCity[50];
//	int population;
//	struct City* next;
//} City;
//
//FILE* openFile(FILE*, char[50]);
//int readFile(FILE*);
//
//int main() {
//
//	FILE* f_drzave = NULL, 
//		* f_hrvatska = NULL, 
//		* f_austrija = NULL, 
//		* f_crnagora = NULL, 
//		* f_makedonija = NULL;
//
//	f_drzave = openFile(f_drzave, "drzave.txt");
//	f_hrvatska = openFile(f_hrvatska, "hrvatska.txt");
//	f_austrija = openFile(f_austrija, "austrija.txt");
//	f_crnagora = openFile(f_crnagora, "crna_gora.txt");
//	f_makedonija = openFile(f_makedonija, "makedonija.txt");
//
//	printf("Radi\n");
//
//
//	return 0;
//}
//
//FILE* openFile(FILE* file, char nameOfFile[50]) {
//	file = fopen(nameOfFile, "r");
//	if (file == NULL) {
//		printf("Neuspješno učitavanje datoteke %s.\n", nameOfFile);
//		return -1;
//	}
//
//	return file;
//}
//
//int readFile(FILE* file) {
//	char nameOfCountry[50] = { NULL }, firstLetter = " ";
//	int population[20] = { 0 };
//
//	char c[1024] = "";
//	if (fgets(c, sizeof(c), file) == NULL) {
//		printf("Datoteka je prazna ili se ne može pročitati.\n");
//		return 0;
//	}
//
//	firstLetter = nameOfCountry[0];
//	while (fscanf(file, "%s, %d", nameOfCountry, population) == 2) {
//		if(nameOfCountry[0] < )
//	}
//
//}