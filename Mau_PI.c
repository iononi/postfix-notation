#include <stdio.h>

int main(int argc, char const *argv[])
{
	int term = 1; //la posicion del termino actual
	float Pi = 4, denominador = 3; //el unico que voy a incrementar es el denominador
	
	//Si el termino es mayor que 0.01, entra
	while ((4 / denominador) > 0.01)
	{
		//Si el numero del termino es impar, se resta, en caso contrario se suma.
		if (term % 2 != 0)
			Pi -= (4/denominador);
		else
			Pi += (4/denominador);
		printf("%d / %.0f\n", 4, denominador); //sirve para ver hasta que numero llega el denominador, no afecta al programa (puedes eliminar o comentar)
		denominador += 2; //incremento el denominador segun el patron de la serie
		term++; //incremento el termino en 1
	}

	printf("Valor de Pi: %f\n", Pi);

	return 0;
}