// Programa para demostrar la aritmetica de punteros
// En este programa se utiliza la aritmetica de punteros para calcular la cantidad
// de elementos que puede contener un array. El resultado de la operacion siempre
// sera un entero, ya sea que el array sea de float, char o int

#include "stdio.h"

int main(int argc, char const *argv[])
{
    int array[10];

    int *p = &array[0];

    int *q = &array[10];

    printf("Cantidad de elementos entre puntero p y q: %d\n", (q - p) );

    printf("Direccion contenida en puntero p: %p\n", p);
    
    printf("Direccion contenida en puntero q: %p\n", q);
    
    return 0;
}
