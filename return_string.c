#include <stdio.h>
#include <stdlib.h>

char *dia(int d);

int main(int argc, char const *argv[])
{
	char *p = "Lunes";
	printf("Contenido de la variable p: %s\n", p);
	p = dia(1);
	printf("Contenido de la variable p despues de la funcion dia(): %s\n", p);
	p = (char *) malloc(15 * sizeof(char));
	printf("Ingrese un nuevo dia: ");
	fgets(p, 14, stdin);
	printf("El nuevo valor de la variable p despues de leer de stdin: %s\n", p);
	return 0;
}

char *dia(int d)
{
	if ( (d - 1) >= 0 && (d - 1) <= 6) 
	{
		char *dia[] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};
		return dia[d - 1];
	}
	printf("Ingrese un dia valido\n");
	return NULL;
	
}