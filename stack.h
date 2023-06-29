#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//struct for the stack
typedef struct NodeStack
{
	char data;
	struct NodeStack *next, *digit;
}Stack;

//struct for an int stack
typedef struct eStack
{
	float data;
	struct eStack *next;
}intStack;

Stack *newElement(char ch);
void push(Stack **top, char ch);
char pop(Stack **top);
char returnTop(Stack *top);
bool isEmpty(Stack *top);
void print(Stack *top);
int add(Stack **start, Stack **end, char ch);
void addDigit(Stack **start, Stack **end, char ch, char *expression, int *index);
bool in(char *array, char ch);
int getIndex(char *array, char ch);
void fromStackToArray(Stack **top, Stack **start, Stack **end, char *operators, char operator);
intStack *new(float n);
void pushStack(intStack **top, float n);
float popStack(intStack **top);
float processArray(Stack *start);
bool isNumeric(char ch);
bool isLetter(char ch);
int count(Stack *start);
Stack *postfix(char *expression);
void delStackQueue(Stack **start);

#include "stack.c"
#endif