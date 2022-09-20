#include <stdio.h>

int main(int argc, char const *argv[])
{
	int resultado = 0, sumando = 1, contador = 0, n;

	printf("Ingrese un numero: ");
	scanf("%d", &n);

	if (n > 2)
	{
		while (resultado < n)
		{
			if (contador != 0 && contador % 3 == 0)
				sumando++;
			printf("%d    ", resultado); 
			resultado += sumando; 
			contador++;
		}
		
	}
	else
		printf("Ingrese un numero mayor a 2.\n");

	printf("\n");
	return 0;
}