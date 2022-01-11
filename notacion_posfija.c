/*
	Program to convert to convert from infix notation to postfix notation
	using a stack implemented with dynamic single-linked list and queues.

	To consider:

	Infix notation: the regular way we write arithmetic expressions. Example: 3+2*7-1

	Postfix notation: operands first, then operators. Example: 327*+1-

	I use the stack for store the operators and the queue-array to store the operands.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_BUFFER 100

//struct for the stack
typedef struct NodeStack
{
	char data;
	struct NodeStack *next;
}Stack;

//struct for the queue-array
typedef struct Node
{
	char data;
	struct Node *next;
}ArrayList;

Stack *newElement(char ch);
void push(Stack **top, char ch);
char pop(Stack **top);
char returnTop(Stack *top);
bool isEmptyStack(Stack *top);
void printStack(Stack *top);
ArrayList *newElem(char ch);
void add(ArrayList **start, ArrayList **end, char ch);
char del(ArrayList **start);
bool isEmptyArray(ArrayList *start);
void printArray(ArrayList *start);
bool in(char *array, char ch);
int getIndex(char *array, char ch);
void fromStackToArray(Stack *top, ArrayList *start, ArrayList *end, char *operators, char operator);

int main(int argc, char const *argv[])
{
	char expr[MAX_BUFFER];
	char operators[] = {'(', '-', '+', '/', '*', '^', '\0'}; //from left to right, less priority to higher priority
	Stack *top, *aux;
	ArrayList *start, *end;

	top = aux = NULL;
	start = end = NULL;

	printf("Please, write the expression you want to evaluate: ");
	fgets(expr, MAX_BUFFER, stdin);

	for (int i = 0; i < strlen(expr); ++i)
	{
		if (expr[i] >= 48 && expr[i] <= 57)
			add(&start, &end, expr[i]); //if is a number, I add it to the queue-array
		if ( in(operators, expr[i]) )
		{
			/*if the index of the top element is smallest than the index of the current character
			based on the operators array, then the current character have higher priority*/
			if (isEmptyStack(top) || (getIndex(operators, returnTop(top)) < getIndex(operators, expr[i])) )
				push(&top, expr[i]);
			else
			{
				//check operators priority level
				if ( expr[i] == '+' && returnTop(top) == '-')
					fromStackToArray(top, start, end, operators, expr[i]);	
				if (expr[i] == '-' && returnTop(top) == '+')
					fromStackToArray(top, start, end, operators, expr[i]);	
				if ( getIndex(operators, returnTop(top)) >= getIndex(operators, expr[i]) )
					fromStackToArray(top, start, end, operators, expr[i]);
			}
		}
		if (expr[i] == ')')
		{
			char ch_aux;
			while (!isEmptyStack(top))
			{
				if (returnTop(top) == '(')
				{
					pop(&top);
					while (!isEmptyStack(aux))
					{
						ch_aux = pop(&aux);
						push(&top, ch_aux);
					}
					break;
				}
				else
				{
					ch_aux = pop(&top);
					push(&aux, ch_aux);	
				}
			}
		}
		

	}

	printf("Printing ArrayList...\n");
	printArray(start);
	printf("Printing Stack...\n");
	printStack(top);

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
	if (*top == NULL)
	{
		printf("\nERROR: Trying to pop on empty stack.\n");
		return '\0';
	}
	Stack *toDelete = *top;
	char ch = toDelete->data;
	*top = (*top)->next;
	free(toDelete);
	return ch;
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

ArrayList *newElem(char ch)
{
	ArrayList *new = (ArrayList *) malloc(sizeof(ArrayList));
	if (!new)
	{
		printf("\nError trying to allocate memory.\n");
		return NULL;
	}
	new->data = ch;
	new->next = NULL;
	return new;
}

void add(ArrayList **start, ArrayList **end, char ch)
{
	ArrayList *newNode = newElem(ch);
	if (!newNode)
	{
		printf("\nCannot add the element into the queue.\n");
		return;
	}
	if (*start == NULL)
		*start = *end = newNode;
	else
		(*end)->next = newNode;
	*end = newNode;
}

char del(ArrayList **start)
{
	if (*start == NULL)
	{
		printf("\nERROR: Trying to delete on empty ArrayList.\n");
		return '\0';
	}
	ArrayList *toDelete = *start;
	char n = toDelete->data;
	*start = (*start)->next;
	free(toDelete);
	return n;
}

bool isEmptyList(ArrayList *start)
{
	if (start == NULL)
		return true;
	return false;
}

void printArray(ArrayList *start)
{
	if (start == NULL)
	{
		printf("\nEnd of queue-array.\n");
		return;
	}
	printf("%2c", start->data);
	printArray(start->next);
}

bool in(char *array, char ch)
{
	for (int i = 0; i < strlen(array); ++i)
	{
		if ( strncmp(&array[i], &ch, 1) == 0 )
			return true;
	}
	return false;
}

int getIndex(char *array, char ch)
{
	for (int i = 0; i < strlen(array); ++i)
	{
		if (strncmp(&array[i], &ch, 1) == 0)
			return i;
	}
	return -1;
}

void fromStackToArray(Stack *top, ArrayList *start, ArrayList *end, char *operators, char operator)
{
	while (!isEmptyStack(top) & returnTop(top) != '(' & (getIndex(operators, returnTop(top)) >= getIndex(operators, operator)) )
	{
		char topChar = pop(&top);
		add(&start, &end, topChar);
	}	
}