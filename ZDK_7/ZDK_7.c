#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Directory {
	char nameOfDirectory[50];
	struct Directory* dirParent;
	struct Directory* dirFirstChild;
	struct Directory* dirNextSibling;
} Directory;

// md dir
int makeDirectory(Directory* , char* );

// cd dir
Directory* changeDirectory(Directory* , char*);

// cd..
Directory* previousDirectory(Directory*);

// dir
int listDirectories(Directory*);

int main() {

	Directory* root = NULL;
	root = malloc(sizeof(Directory));

	if (root == NULL)
		return -1;

	root->dirParent = NULL;
	root->dirFirstChild = NULL;
	root->dirNextSibling = NULL;

	char inputValue[40] = { NULL };
	char *command = NULL;
	char *dirName = NULL;
	char path[200] = { NULL };

	printf("Unesi ime root direktorija: ");
	scanf(" %s", root->nameOfDirectory);
	getchar();

	strcpy(path, root->nameOfDirectory);
	strcat(path,":");

	printf("Naredbe:\n- md <dir>\n- cd <dir>\n- cd..\n- dir\n- IZLAZ - 5\n");

	do {
		printf("\n%s/", path);
		scanf(" %[^\n]s", inputValue);
		getchar();

		int i = 0, noWords = 0;
		while (inputValue[i] != '\0') {
			if (inputValue[i] == ' ' && noWords == 0) {
				noWords = 1;
			}
			i++;
		}

		if (noWords == 0) {
			command = inputValue;
			//dirName = NULL;
			//printf("\n\t%s", command);
			//printf("..");
		}
		else {
			command = strtok(inputValue, " ");
			dirName = strtok(NULL, " ");
		}

		if (strcmp(command, "md") == 0)
			makeDirectory(root, dirName);
		else if (strcmp(command, "cd") == 0) {
			if (root != changeDirectory(root, dirName)) {
				root = changeDirectory(root, dirName);
				strcat(path, "/");
				strcat(path, root->nameOfDirectory);
			}
		}
		else if (strcmp(command, "cd..") == 0) {
			root = previousDirectory(root);

			char* lastSlash = NULL;
			lastSlash = strrchr(path, '/'); //Pronalazi zadnji '/' dodjeljen

			if (lastSlash != NULL) {
				*lastSlash = '\0';
			}
			
		}
			
		else if (strcmp(command, "dir") == 0)
			listDirectories(root);
		else {
			if(strcmp(command, "5") != 0)
				printf("'%s' is not recognized as an internal or external command, operable program or batch file.\n", inputValue);
		}
			

	} while (strcmp(command, "5") != 0);

	printf("\nKRAJ PROGRAMA...\n");
	return 0;
}

int makeDirectory(Directory* root, char* dirName) {
	Directory* newDirectroy = NULL;
	newDirectroy = (Directory*)malloc(sizeof(Directory));

	if (newDirectroy == NULL) return -1;

	strcpy(newDirectroy->nameOfDirectory, dirName);

	newDirectroy->dirNextSibling = root->dirFirstChild;
	root->dirFirstChild = newDirectroy;
	newDirectroy->dirFirstChild = NULL;
	newDirectroy->dirParent = root;

	return 0;
}

Directory* changeDirectory(Directory* root, char* dirName) {
	Directory* tempDir = root->dirFirstChild;
	if (tempDir == NULL) {
		printf("Greska, direktorij je prazan.\n");
		return root;
	}

	while (strcmp(tempDir->nameOfDirectory, dirName) != 0)
		tempDir = tempDir->dirNextSibling;

	if (tempDir == NULL) {
		printf("Direktorij '%s' ne postoji u direktoriju '%s'\n", dirName, root->nameOfDirectory);
		return root;
	}

	return tempDir;
}

int listDirectories(Directory* root){
	Directory* tempDir = root->dirFirstChild;

	if (tempDir == NULL) {
		printf("Direktorij %s nema poddirektorija.\n", root->nameOfDirectory);
		return -1;
	}

	while (tempDir != NULL) {
		printf("\t| %s\n", tempDir->nameOfDirectory);
		tempDir = tempDir->dirNextSibling;
	}

	return 1;
}

Directory* previousDirectory(Directory* root) {
	if (root->dirParent != NULL) {
		return root->dirParent;
	}
	else {
		printf("Ovo je root direktorij, nema direktorija iznad.\n");
		return root;
	}
}
