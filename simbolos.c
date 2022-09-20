/*
	Simple program to check that an if statement
	is well formed using dynamic single-linked lists.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_BUFF 100

//Struct that represents a stack using single-linked lists
typedef struct NodeStack
{
	char data;
	struct NodeStack *next;
}Stack;

Stack *newElement(char ch); //function that allocates memory for a new node of the stack
void push(Stack **top, char ch); //add an element into the stack
char pop(Stack **top); //delete the top element and returns it
void printStack(Stack *top); //print the contents of the stack
char returnTop(Stack *top); //return the top element, but does not delete it
bool isEmptyStack(Stack *top); //return true if stack is empty, false otherwise
bool in(char *array, char ch); //check if character ch is in the array passed as parameter

int main(int argc, char const *argv[])
{
	Stack *top = NULL;

	char string[MAX_BUFF];
	char temp[] = "1234";

	printf("Convirtiendo \"1234\" a numero y le sumo 1: %d\n", atoi(temp) + 1);
	/*char array[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', '\0'};

	if (in(array, 'k'))
		printf("The char 'k' is in the array.\n");
	else
		printf("The char 'k' is not in the array.\n");*/

	printf("Please, type the if statement to check: ");
	fgets(string, MAX_BUFF, stdin);


	for (int index = 0; index < strlen(string); index++)
	{	
		if (string[index] == '(' || string[index] == '[' || string[index] == '{')
			push(&top, string[index]);
		if (string[index] == ')' && returnTop(top) == '(')
			pop(&top);
		if (string[index] == ']' && returnTop(top) == '[')
			pop(&top);
		if (string[index] == '}' && returnTop(top) == '{')
			pop(&top);
	}

	//printStack(top);

	if ((string[0] == 'i' && string[1] == 'f') && isEmptyStack(top))
		printf("\nThe if statement is well formed.\n");
	else
		printf("\nYou have a syntax error in the if statement.\n");

	return 0;
}

Stack *newElement(char ch)
{
	Stack *new = (Stack *) malloc(sizeof(Stack));
	if (!new)
	{
		printf("\nError trying to allocate memory.\n");
		return NULL;
	}

	new->data = ch;
	new->next = NULL;

	return new;
}

void push(Stack **top, char ch)
{
	Stack *newNode = newElement(ch);
	if (!newNode)
		printf("\nCannot push the element into the stack.\n");
	if (*top != NULL)
		newNode->next = *top;
	*top = newNode;
}

char pop(Stack **top)
{
	Stack *toDelete = *top;
	char ch = toDelete->data;
	*top = (*top)->next;
	free(toDelete);
	return ch;
}

void printStack(Stack *top)
{
	if (top == NULL) 
	{
		printf("\nEnd of stack.\n");
		return;
	}
	printf("%2c", top->data);
	printStack(top->next);
}

char returnTop(Stack *top)
{
	if (top == NULL)
		return '\0';
	return top->data;
}

bool isEmptyStack(Stack *top)
{
	if (top == NULL)
		return true;
	return false;
}

bool in(char *array, char ch)
{
	for (int i = 0; i < strlen(array); ++i)
	{
		//printf("%c -> %c = %d\n", array[i], ch, strncmp(&array[i], &ch, 1));
		if ( strncmp(&array[i], &ch, 1) == 0 )
			return true;
	}
	return false;
}