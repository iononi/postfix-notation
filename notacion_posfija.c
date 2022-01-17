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
#include <math.h>
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
int processArray(Stack *start);
bool isNumeric(char ch);
bool isLetter(char ch);
int count(Stack *start);
Stack *postfix(char *expression);


int main(int argc, char const *argv[])
{
	char expr[MAX_BUFFER];
	Stack *pos;
	int result, op;
	

	printf("Please, write the expression you want to evaluate: ");
	fgets(expr, MAX_BUFFER, stdin);

	printf("\nWhat do you want to do next?\n%s\n%s\nType an option: ", "1. Get and evaluate postfix notation", "2. Get postfix notation only");

	scanf("%d", &op);

	switch (op)
	{
		case 1: pos = postfix(expr);
				printf("\nInfix notation: %s\n", expr);
				printf("Postfix notation: "); print(pos);
				result = processArray(pos);
				printf( (result == -1) ? "\n\nSomething went wrong while processing postfix notation\n\n" : "\n\nResult after evualating the expression: %d\n\n", result );
		break;
		case 2: pos = postfix(expr);
				printf("\nInfix notation: %s\n", expr);
				printf("Postfix notation: "); print(pos); printf("\n\n");
		break;
		default: printf("\nType a valid option\n");
	}

	return 0;
}

/* Allocates memory for new Stack node. 
	If memory allocation was possible, return the new node, return NULL otherwise.
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

// Returns the stack top element but does not delete it, return NULL (in its ASCII representation) otherwise.
char returnTop(Stack *top)
{
	if ( isEmpty(top) )
		return '\0';
	return top->data;
}

// Check if the stack passed as parameter is empty. Return true if the stack is empty, return false otherwise.
bool isEmpty(Stack *top)
{
	if (top == NULL)
		return true;
	return false;
}

// Print the stack/queue content.
void print(Stack *top)
{
	if (top == NULL)
		return;
	printf("%c", top->data);
	print(top->next);
}

// Add a new element into the queue. Return 0 if the element was added, return -1 otherwise.
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

// If next element in expression array is numeric, add it to the queue but linked with the previous node
void addDigit(Stack **start, Stack **end, char ch, char *expression, int *index)
{
	if (add(&*start, &*end, ch) != 0)
	{
		printf("\nCannot add the element into the queue.\n");
		return;
	}
	while ( isNumeric(expression[(*index) + 1]) || expression[(*index) + 1] == '.')
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

// Check if character ch is in array. Return true if ch is in array, false otherwise.
bool in(char *array, char ch)
{
	for (int i = 0; i < strlen(array); ++i)
	{
		if ( strncmp(&array[i], &ch, 1) == 0 )
			return true;
	}
	return false;
}

// Return the index of ch in array, return -1 if ch is not in array.
int getIndex(char *array, char ch)
{
	for (int i = 0; i < strlen(array); ++i)
	{
		if (strncmp(&array[i], &ch, 1) == 0)
			return i;
	}
	return -1;
}

/* Insert the elements of the stack top into the queue pointed by start.
   This happens when operators has the same priority level, in addition/substraction and
   multiplication/division cases, or the top of the top stack contains a operator with 
   equal or higher priority level than the current operator.
*/
void fromStackToArray(Stack **top, Stack **start, Stack **end, char *operators, char operator)
{
	while (!isEmpty(*top) & returnTop(*top) != '(' & (getIndex(operators, returnTop(*top)) >= getIndex(operators, operator)) )
	{
		char topChar = pop(&*top);
		add(&*start, &*end, topChar);
	}	
}

// Allocates memory for an intStack node. Return the new node if allocation was successful, return NULL otherwise.
intStack *new(float n)
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

// Insert a new element into the float stack.
void pushStack(intStack **top, float n)
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

// Delete the top element from the int stack and return it. Return -1 otherwise.
float popStack(intStack **top)
{
	if (*top == NULL)
	{
		printf("\nERROR: Trying to pop on empty stack.\n");
		return -1;
	}
	intStack *toDelete = *top;
	float n = toDelete->data;
	*top = (*top)->next;
	free(toDelete);
	return n;
}

/* Processes the queue when it cointains the postfix notation.
   Iterates over the queue and check if the digit pointer of the current node is <> NULL,
   in that case, means that we have a number with two or more digits so it concatenates 
   the elements linked by the digit  pointer into an array to apply atoi() function later
   and get the full number. If the number has no linked nodes, it just push it into the stack.
   Return the expression result if everything went OK, and returns -1 if an error occurr.
*/
int processArray(Stack *start)
{
	char operators[] = {'-', '+', '/', '*', '^', '\0'}; //from left to right, less priority to higher priority
	intStack *aux = NULL;
	float n1, n2, result = 0;
	char *temp;

	while (!isEmpty(start))
	{
		bool allocate = true;
		while ( start->digit != NULL )
		{
			if (allocate)
			{
				int size = count(start);
				temp = (char *)calloc(size, sizeof(char));
				if (!temp)
					return -1;
			}
			strncat(temp, &start->data, 1);
			if ( (start->next)->digit == NULL )
			{ start = start->next; strncat(temp, &start->data, 1); pushStack(&aux, atof(temp)); start = start->next; free(temp); break; }
			start = start->digit;
			allocate = false;
		}
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
				case '^': result = pow(n2, n1);
				break;
			}

			pushStack(&aux, result);
		}
		start = start->next;
	}

	n1 = popStack(&aux);
	return n1;
}

// Return true if character ch is in range 0-9, return false otherwise.
bool isNumeric(char ch)
{
	if (ch >= 48 && ch <= 57)
		return true;
	return false;
}

// Return true if character ch is in range a-z or A-Z, return false otherwise.
bool isLetter(char ch)
{
	if ( (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) )
		return true;
	return false;
}

/* Count how many digits are linked in the queue to allocate that space in memory
   to process the whole number.
*/
int count(Stack *start)
{
	if (isEmpty(start))
		return 0;
	return 1 + count(start->digit);
}

// Get postfix notation from expression, that may be given in infix notation to work correctly.
Stack *postfix(char *expression)
{
	char operators[] = {'-', '+', '/', '*', '^', '\0'}; //from left to right, less priority to higher priority
	Stack *top;
	Stack *start, *end; //to manage it like an queue
	int result;

	top = start = end = NULL;
	for (int i = 0; i < strlen(expression); ++i)
	{
		if ( isLetter(expression[i]) | expression[i] == '.' )
			add(&start, &end, expression[i]);
		if ( isNumeric(expression[i]) ) 
			addDigit(&start, &end, expression[i], expression, &i);
		if (expression[i] == '(')
			push(&top, expression[i]);
		// the current character is an operator
		if ( in(operators, expression[i]) )
		{
			if (isEmpty(top))
				push(&top, expression[i]);
			else
			{
				// check operator priority level
				/* if current operator and top element has same priority level, unstack each element and add it
					to the queue-array until the first condition is met: empty stack, open parenthesis or higher
					priority operator*/
				if ( (expression[i] == '+' && returnTop(top) == '-') | (expression[i] == '-' && returnTop(top) == '+') )
				{
					fromStackToArray(&top, &start, &end, operators, expression[i]);
					push(&top, expression[i]);
					continue;	
				}
				if ( (expression[i] == '*' && returnTop(top) == '/') || (expression[i] == '/' && returnTop(top) == '*') )
				{
					fromStackToArray(&top, &start, &end, operators, expression[i]);
					push(&top, expression[i]);
					continue;	
				}

				// if the top element has lower priority, push the current element into the stack
				if ( getIndex(operators, returnTop(top)) < getIndex(operators, expression[i]) )
				{
					push(&top, expression[i]);
					continue;
				}
				/*if top element has higher priority, unstack from the stack until stack is empty, lower priority operator, or an open
				parenthesis is found and add each element to the array, then push the current element*/
				if ( getIndex(operators, returnTop(top)) >= getIndex(operators, expression[i]) )
				{
					fromStackToArray(&top, &start, &end, operators, expression[i]);
					push(&top, expression[i]);
				}

			}
			
		}
		if (expression[i] == ')')
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
	return start;
}