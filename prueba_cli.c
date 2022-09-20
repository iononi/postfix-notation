#include <stdio.h>
#include <string.h>

/*int length(char const **matriz) 
{
	int total_elements = 0, int i = 0;

	while (matriz[i++] != NULL)
		total_elements++;


}*/

void saludo()
{
	printf("Hola! Como estas?\n");
}

void saludoPersona(char const *nombre)
{
	printf("Hola %s! Como has estado?\n", nombre);
}

int main(int argc, char const *argv[])
{
	if (strcmp(argv[1], "hola") == 0)
		if (argv[2] != NULL)
			saludoPersona(argv[2]);
		else
			saludo();
	else
		printf("Note vi, disculpa :c");

	return 0;
}