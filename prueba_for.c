//Programa para ver si el indice del ciclo for se modifica pasandolo a una función por referencia

#include <stdio.h>

void modIndex(int *index);

int main(int argc, char const *argv[])
{
	//0 2 3 4
	for (int i = 0; i < 5; i++)
	{
		printf("%2d", i);
		if (i == 0)
			modIndex(&i);
	}
	return 0;
}

void modIndex(int *index)
{
	//do something
	(*index )++;
}