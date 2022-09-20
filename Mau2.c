#include <stdio.h>

/*Calcular la siguiente serie para n terminos
  (1/2) + (3/4) + (7/8) + (15/16) + ...*/

int main(int argc, char const *argv[])
{
	int n, cont = 0, patron = 2;
	float numerador = 1, denominador = 2, resultado = 0;

	printf("Ingrese la cantidad de terminos de la serie: ");
	scanf("%d", &n);

	while (cont < n)
	{
		resultado += (numerador / denominador);
		numerador += patron;
		denominador *= 2;
		patron *= 2;
		cont++;
	}

	printf("\n------------------------\n");
	printf("Resultado: %.4f\n", resultado);
	return 0;
}