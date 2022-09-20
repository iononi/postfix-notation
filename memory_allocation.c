// Difference between malloc() and calloc()
// for memory allocation

#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int size);

int main(int argc, char const *argv[])
{
	int *scores = (int *) malloc( 10 * sizeof(int) ); // is possible to malloc() to iniatilize as 0 every element,
													  // but there is no guaratee.
	int *prices = (int *) calloc(10, sizeof(int));	  // on the other hand, calloc() always initialize every
													  // element as 0.
	if ( !scores || !prices ) 
	{
		perror("Unable to allocate memory for arrays.");
		exit(-1);
	}

	printf("\nPrinting scores array (malloc'd): \n\n");
	printArray(scores, 10);

	printf("\nPrinting prices array (calloc'd): \n\n");
	printArray(prices, 10);


	return 0;
}

void printArray(int *array, int size) 
{
	for (int i = 0; i < size; i++)
		printf("%d\n", *(array + i));
}