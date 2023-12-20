#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Directory {
	char nameOfDirectory[50];
	struct Directory* directory;
	struct Directory* nextDirectory;
} Directory;

int main() {

	Directory* root = NULL;
	root = malloc(sizeof(Directory));
	root->directory = NULL;
	root->nextDirectory = NULL;

	char command[50] = { NULL };

	printf("Unesi ime root direktorija: ");
	scanf(" %s", root->nameOfDirectory);

	printf("Naredbe:\n- md <dir>\n- cd <dir>\n- cd..\n- dir\n- IZLAZ - 5\n");
	printf("\n%s://", root->nameOfDirectory);
	scanf(" %s", command);
	do {
		if (strcmp(command, "cd"));
	} while (command != '5');

	return 0;
}