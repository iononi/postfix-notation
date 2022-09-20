#include <stdio.h>

void imprimir_recur(int *array)
{
	if (*array == '\0')
	{
		printf("\n");
		return;
	}
	printf("%d\n", *array);
	imprimir_recur(++array);
	
}


int main(int argc, char const *argv[])
{
	int mi_arreglo[] = {1,5,4,3, '\0'};

	imprimir_recur(mi_arreglo);

	return 0;
}