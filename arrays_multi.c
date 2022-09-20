// Programa para trabajar con arrays multidimensionales

#include <stdio.h>

int main(int argc, char const *argv[])
{
    int myArray[2][2];

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("Ingrese un valor para la posicion [%d][%d]: ", i, j);
            scanf("%d", &myArray[i][j] );
        }
        
    }

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            printf("myArray[%d][%d]: %d\n", i, j, *(*(myArray + i) + j));
        }
    }

    printf("Direccion del elemento [0][1]: %p\n", ( (myArray + 0) + 1) );
    

    return 0;
}
