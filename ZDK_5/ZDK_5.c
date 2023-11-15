#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// struktura za vezanu listu
struct Node {
    int data;
    struct Node* next;
};

// struktura za stog
struct Stack {
    struct Node* top;
};

// struktura za stavaranje stoga
struct Stack* createStack() {
    struct Stack* stack = NULL;
    stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

void push(struct Stack* stack, int val); // stavljanje elementa
int pop(struct Stack* stack); // izbacivanje elementa
int calculation(FILE* file); //za racunanje
int isEmpty(struct Stack* stack); //samo provjera

int main() {
    FILE* inputFile = NULL;
    inputFile = fopen("dokument.txt", "r");
    if (inputFile == NULL) {
        printf("Unable to open file!\n");
        return 1;
    }

    int result = 0;
    result = calculation(inputFile);
    printf("Result: %d\n", result);

    fclose(inputFile);
    return 0;
}

int isEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// racunanje
int calculation(FILE* file) {
    struct Stack* stack = createStack();

    char token = {0};
    int operand = 0;
    int operand1 = 0;
    int operand2 = 0;
    while ((token = fgetc(file)) != EOF) {

        if (isdigit(token)) {
            ungetc(token, file);
            fscanf(file, "%d", &operand);
            push(stack, operand);
        }
        else if (token != ' ' && token != '\n') {
            operand2 = pop(stack);
            operand1 = pop(stack);

            switch (token) {
            case '+':
                push(stack, operand1 + operand2);
                break;
            case '-':
                push(stack, operand1 - operand2);
                break;
            case '*':
                push(stack, operand1 * operand2);
                break;
            case '/':
                push(stack, operand1 / operand2);
                break;
            default:
                printf("Invalid operator!\n");
                return -1;
            }
        }
    }
    return pop(stack);
}

int pop(struct Stack* stack) {
    struct Node* temp = NULL;
    temp = stack->top;

    int val = 0;
    val = stack->top->data;

    if (stack->top == NULL) {
        printf("Stack underflow!\n");
        return -1;
    }
    stack->top = stack->top->next;

    free(temp);
    return val;
}


void push(struct Stack* stack, int val) {
    struct Node* newNode = NULL;
    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = val;
    newNode->next = stack->top;
    stack->top = newNode;
}