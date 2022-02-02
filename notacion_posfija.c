/*
	Program to convert to convert from infix notation to postfix notation
	using a stack implemented with dynamic single-linked list and queues.

	To consider:

	Infix notation: the regular way we write arithmetic expressions. Example: 3+2*7-1

	Postfix notation: operands first, then operators. Example: 327*+1-

	I use the stack for store the operators and the queue-array to store the operands.
*/

#include "stack.h"
#define MAX_BUFFER 100


int main(int argc, char *argv[])
{
	char expr[MAX_BUFFER];
	Stack *pos;
	int op;
	float result;

	if (  argc != 0 )
	{
		for (int i = 0; i < argc - 1; i++)
		{
			pos = postfix( argv[i + 1] );
			printf("Infix notation: %s\n", argv[i + 1]);
			printf("Postfix notation: "); print(pos);
			result = processArray(pos);
			printf( (result == -1) ? "\n\nSomething went wrong while processing postfix notation\n\n" : "\n\nResult after evaluating the expression: %.2f\n\n", result );
			delStackQueue(&pos);
		}
	}

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
				printf( (result == -1) ? "\n\nSomething went wrong while processing postfix notation\n\n" : "\n\nResult after evaluating the expression: %.2f\n\n", result );
		break;
		case 2: pos = postfix(expr);
				printf("\nInfix notation: %s\n", expr);
				printf("Postfix notation: "); print(pos); printf("\n\n");
		break;
		default: printf("\nType a valid option\n");
	}

	return 0;
}