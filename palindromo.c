#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reverse(char *str);


int main(int argc, char const *argv[])
{
	char *word = "aba"; //lo ideal seria convertir este string primero a lower case y continuar

	char *r = reverse(word);

	if (!r)
		printf("No se pudo obtener el reverso del string %s\n", r);
	else
	{
		if (strcmp(word, r) == 0)
			printf("Son palindromas\nword = %s, r = %s\n", word, r);
		else
			printf("No son palindromas\nword = %s, r = %s\n", word, r);
	}

	free(r);
	free(word);
	return 0;
}

//retorna el string pasado como paramétro al revés
char *reverse(char *str)
{
	int str_len = strlen(str), index = 0;

	char *temp = (char *) malloc(str_len * sizeof(char));
	
	if (!temp)
		return NULL;

	for (int i = str_len - 1; i >= 0 ; --i)
	{
		temp[index++] = str[i];
	}

	return temp;
}