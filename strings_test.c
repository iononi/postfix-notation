// Prueba de un programa para ver si se pueden almacenar dinámicamente los strings
// en un array sin especificar su tamaño
// sirve para trabajar desde la cli (cmd)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print(char const *array)
{
	if (*array == '\0')
	{
		printf("\n");
		return;
	}
	printf("%3c", *array);
	print(++array);
}

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		/*char const *num1 = argv[1], *num2 = argv[2];

		int left_operand = atoi(num1);
		int right_operand = atoi(num2);

		printf("La suma de %s y %s es %d\n", num1, num2, (left_operand + right_operand));*/

		for (int i = 1; i < argc; i++)
		{
			char const *string = argv[i];

			printf("El primer comando es (almacenado en string[]): %s\n", string);
			printf("La longitud del string es: %d\n", strlen(string));

			printf("Los elementos del string procesador por separado son:\n");
			print(string);
		}
		
	}
	else
		printf("Ingrese algun comando\n");
	return 0;
}