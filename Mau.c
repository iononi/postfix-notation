#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*En una empresa con N empleados se necesita obtener cierta informacion. Por cada empleado se ingresan los siguientes datos CLAVE, EDAD, SEXO y sueldo
  DUDF para calcular e imprimmir lo siguiente:
  a) Numero de hombres
  b) Numero de mujeres
  c) Numero de mujeres que ganen con mas de $ 1000
  d) Numero de hombres menores de 40 años que ganen menos de $ 100
  e) Numero de empleados mayores de 50 años*/

//Los datos referentes a cada empleado
struct Empleado
{
	int clave;
	int edad;
	char nombre[35];
	char sexo[2];
	float sueldo;
};

int main(int argc, char const *argv[])
{
	int N; //la cantidad de empleados
	int index = 0; //su usará para iterar a través del array struct Empleado empleados[]
	int hombres = 0, mujeres = 0, mujeres_mayor_mil = 0, 
		hombres_40_100 = 0, //hombres menores de 40 con sueldo menor de 100
		empleado_mayor_50 = 0;
	struct Empleado empleado; //representa a un empleado
	

	printf("Ingrese la cantidad de empleados: ");
	scanf("%d", &N);

	struct Empleado empleados[N]; //un array que almacenará structs de tipo Empleado

	for (int i = 0; i < N; i++)
	{
		printf("\nEmpleado %d\n\n", i + 1);
		printf("Ingrese la clave: ");
		scanf("%d", &empleado.clave);
		printf("Ingrese la edad: ");
		scanf("%d", &empleado.edad);
		printf("Ingrese el nombre: "); scanf("\n");
		scanf("%[^\n]s", empleado.nombre); fflush(stdin);
		printf("Ingrese el sexo (M - Hombre y F - Mujer): ");
		scanf("%[^\n]s", &empleado.sexo);
		printf("Ingrese el sueldo: ");
		scanf("%f", &empleado.sueldo);

		empleados[i] = empleado;
	}

	while (index < N)
	{
		if (strncmp(empleados[index].sexo, "M", 1) == 0 || strncmp(empleados[index].sexo, "m", 1) == 0)
		{
			hombres++;
			if (empleados[index].edad < 40 && empleados[index].sueldo < 100.00)
				hombres_40_100++;
		}

		if (strncmp(empleados[index].sexo, "F", 1) == 0 || strncmp(empleados[index].sexo, "f", 1) == 0)
		{
			mujeres++;
			if (empleados[index].sueldo > 1000.00)
				mujeres_mayor_mil++;
		}

		if (empleados[index].edad > 50)
				empleado_mayor_50++;

		index++;
	}

	printf("\n\n-------------------------------\n");
	printf("Total hombres: %d\n", hombres);
	printf("Total mujeres: %d\n", mujeres);
	printf("Mujeres que ganan mas de $1,000: %d\n", mujeres_mayor_mil);
	printf("Hombres menores de 40 anios con sueldo menor de 100: %d\n", hombres_40_100);
	printf("Empleados mayores de 50 anios: %d\n", empleado_mayor_50);
	printf("-------------------------------\n");

	//system("pause");

	return 0;
}