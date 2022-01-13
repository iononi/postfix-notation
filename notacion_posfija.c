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
	struct NodeStack *next, *digit;
}Stack;

//struct for an int stack
typedef struct eStack
{
	int data;
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
intStack *new(int n);
void pushStack(intStack **top, int n);
int popStack(intStack **top);
int processArray(Stack *start, char *operators);
bool isNumeric(char ch);
bool isLetter(char ch);
int count(Stack *start);


int main(int argc, char const *argv[])
{
	char expr[MAX_BUFFER];
	char operators[] = {'-', '+', '/', '*', '^', '\0'}; //from left to right, less priority to higher priority
	Stack *top;
	Stack *start, *end; //to manage it like an queue

	top  = NULL;
	start = end = NULL;

	printf("Please, write the expression you want to evaluate: ");
	fgets(expr, MAX_BUFFER, stdin);

	for (int i = 0; i < strlen(expr); ++i)
	{
		if ( isNumeric(expr[i]) ) 
			addDigit(&start, &end, expr[i], expr, &i);
		if (expr[i] == '(')
			push(&top, expr[i]);
		// the current character is an operator
		if ( in(operators, expr[i]) )
		{
			if (isEmpty(top))
				push(&top, expr[i]);
			else
			{
				// check operator priority level
				/* if current operator and top element has same priority level, unstack each element and add it
					to the queue-array until the first condition is met: empty stack, open parenthesis or higher
					priority operator*/
				if ( (expr[i] == '+' && returnTop(top) == '-') | (expr[i] == '-' && returnTop(top) == '+') )
				{
					fromStackToArray(&top, &start, &end, operators, expr[i]);
					push(&top, expr[i]);
					continue;	
				}
				if ( (expr[i] == '*' && returnTop(top) == '/') || (expr[i] == '/' && returnTop(top) == '*') )
				{
					fromStackToArray(&top, &start, &end, operators, expr[i]);
					push(&top, expr[i]);
					continue;	
				}

				// if the top element has lower priority, push the current element into the stack
				if ( getIndex(operators, returnTop(top)) < getIndex(operators, expr[i]) )
				{
					push(&top, expr[i]);
					continue;
				}
				/*if top element has higher priority, unstack from the stack until stack is empty, lower priority operator, or an open
				parenthesis is found and add each element to the array, then push the current element*/
				if ( getIndex(operators, returnTop(top)) >= getIndex(operators, expr[i]) )
				{
					fromStackToArray(&top, &start, &end, operators, expr[i]);
					push(&top, expr[i]);
				}

			}
			
		}
		if (expr[i] == ')')
		{
			char ch_aux;
			while (!isEmpty(top))
			{
				if (returnTop(top) == '(')
				{
					pop(&top);
					break;
				}
				ch_aux = pop(&top);
				add(&start, &end, ch_aux);	
			}
		}
	}

	while (!isEmpty(top)) 
	{	
		char ch_aux = pop(&top);
		add(&start, &end, ch_aux);
	}

	printf("\nInfix notation: %s\n", expr);
	printf("Postfix notation: ");
	print(start);
	printf("\n");
	//printf("Array size: %d\n", count(start, operators));

	printf("\nResult after evaluating the expression: %d\n", processArray(start, operators));

	return 0;
}

/* Allocates memory for new Stack node. 
	If memory allocation was possible, return the new node, return NULL otherwise
*/
Stack *newElement(char ch)
{
	Stack *new = (Stack *) malloc(sizeof(Stack));
	if (!new)
	{
		printf("\nError trying to allocate memory.\n");
		return NULL;
	}
	new->data = ch;
	new->next = new->digit = NULL;
	return new;
}

/* Creates a new Stack node, if creation was successful, 
	insert the node into the stack, print an error message otherwise.
*/
void push(Stack **top, char ch)
{
	Stack *newNode = newElement(ch);
	if (!newNode)
	{
		printf("\nCannot push the element into the stack.\n");
		return;
	}
	if (*top != NULL)
		newNode->next = *top;
	*top = newNode;
}

/* Delete the top element in the stack and returns it, prints an error message otherwise.
*/
char pop(Stack **top)
{
	if (isEmpty(*top))
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
	if ( isEmpty(top) )
		return '\0';
	return top->data;
}

bool isEmpty(Stack *top)
{
	if (top == NULL)
		return true;
	return false;
}

void print(Stack *top)
{
	if (top == NULL)
		return;
	printf("%c", top->data);
	print(top->next);
}

int add(Stack **start, Stack **end, char ch)
{
	Stack *newNode = newElement(ch);
	if (!newNode)
	{
		printf("\nCannot add the element into the queue.\n");
		return -1;
	}
	if (isEmpty(*start))
		*start = *end = newNode;
	else
		(*end)->next = newNode;
	*end = newNode;
	return 0;
}

void addDigit(Stack **start, Stack **end, char ch, char *expression, int *index)
{
	if (add(&*start, &*end, ch) != 0)
	{
		printf("\nCannot add the element into the queue.\n");
		return;
	}
	if ( isNumeric(expression[(*index) + 1]) )
		{
			(*end)->digit = newElement(expression[(*index) + 1]);
			if (!(*end)->digit)
			{
				printf("\nCannot add the element into the queue.\n");
				return;
			}
			(*end)->next = (*end)->digit; *end = (*end)->digit; (*index)++;
		}
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

void fromStackToArray(Stack **top, Stack **start, Stack **end, char *operators, char operator)
{
	while (!isEmpty(*top) & returnTop(*top) != '(' & (getIndex(operators, returnTop(*top)) >= getIndex(operators, operator)) )
	{
		char topChar = pop(&*top);
		add(&*start, &*end, topChar);
	}	
}

intStack *new(int n)
{
	intStack *new = (intStack *) malloc(sizeof(intStack));
	if (!new)
	{
		printf("\nError trying to allocate memory.\n");
		return NULL;
	}
	new->data = n;
	new->next = NULL;
	return new;
}

void pushStack(intStack **top, int n)
{
	intStack *newNode = new(n);
	if (!newNode)
	{
		printf("\nCannot push the element into the stack.\n");
		return;
	}
	if (*top != NULL)
		newNode->next = *top;
	*top = newNode;
}

int popStack(intStack **top)
{
	if (*top == NULL)
	{
		printf("\nERROR: Trying to pop on empty stack.\n");
		return -1;
	}
	intStack *toDelete = *top;
	int n = toDelete->data;
	*top = (*top)->next;
	free(toDelete);
	return n;
}


int processArray(Stack *start, char *operators)
{
	intStack *aux = NULL;
	int n1, n2, result = 0, size = count(start);
	char *temp = (char *) calloc(size, sizeof(char));

	while ( start->digit != NULL )
	{
		strncat(temp, &start->data, 1);
		if ( (start->next)->digit == NULL )
		{ strncat(temp, &(start->next)->data, 1); pushStack(&aux, atoi(temp)); break; }
		start = start->digit;
	}

	printf("temp content as a number: %d\n", atoi(temp));

	while (!isEmpty(start))
	{
		if ( isNumeric(start->data) )
			pushStack(&aux, atoi(&start->data));
		if ( in(operators, start->data) )
		{ 
			n1 = popStack(&aux); n2 = popStack(&aux);
			switch( start->data )
			{
				case '-': result = n2 - n1;
				break;
				case '+': result = n2 + n1;
				break;
				case '*': result = n2 * n1;
				break;
				case '/': result = n2 / n1;
				break;
				case '^': result = n2 ^ n1;
				break;
			}

			pushStack(&aux, result);
		}
		start = start->next;
	}
	n1 = popStack(&aux);
	free(temp);
	return n1;
}

bool isNumeric(char ch)
{
	if (ch >= 48 && ch <= 57)
		return true;
	return false;
}

bool isLetter(char ch)
{
	if ( (ch >= 65 && ch <= 90) | (ch >= 97 && ch <= 122) )
		return true;
	return false;
}

int count(Stack *start)
{
	if (isEmpty(start))
		return 0;
	return 1 + count(start->digit);
}