#include <string.h>
#include "strings.h"
#include <stdlib.h>
#include <stdio.h>

char *concatenation (char *s1, char *s2)
{
	char *result = malloc((strlen(s1) + strlen(s2) +1)* sizeof(char));
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

char *concatenationCarac(char *s1, char s2)
{
	char *resultat = malloc((strlen(s1) + 2) * sizeof(char));
	strcpy(resultar, s1);
	char *s3 = (char[2]) {(char) s2, '\0'};
	strcar (resultat, s3);
	return resultat;
}
