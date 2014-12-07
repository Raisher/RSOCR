#include <err.h>
#include <stdio.h>
#include "array.h"
#include <stdlib.h>

doubleArray nouveau_doubleArray (unsigned i)
{
	double *k = malloc (i * sizeof(double));
	for(unsigned x = 0; x < i; x++)
		k[x] = 0;

	doubleArray tableau;
	tableau.sizeX = i;
	tableau.elements= k;

	return tableau;
}


unsignedArray nouveau_unsignedArray (unsigned i)
{
	double *k = malloc (i * sizeof(double));
	for(unsigned x = 0; x < i; x++)
		k[x] = 0;

	unsignedArray tableau;
	tableau.sizeX = i;
	tableau.elements= k;

	return tableau;
}

doubleArray2D nouveau_doubleArray2D(unsigned i, unsigned j)
{
	doubleArray*x = malloc (i * sizeof(doubleArray));
	for (unsigned m=0; m<i;m++)
		x[m] = nouveau_doubleArray(j);

	doubleArray2D matrice;
	matrice.sizeX = i;
	matrice.sizeY= j;
	matrice.elements = x;

	return matrice;
}


unsigned2D nouveau_unsignedArray2D(unsigned i, unsigned j)
{
	unsignedArray*x = malloc (i * sizeof(doubleArray));
	for (unsigned m=0; m<i;m++)
		x[m] = nouveau_unsignedArray(j);

	doubleArray2D matrice;
	matrice.sizeX = i;
	matrice.sizeY= j;
	matrice.elements = x;

	return matrice;
}

doubleArray remplir_da(unsignedArray tableau, unsigned x)
{
	for (unsigned k = 0; i<tableau.sizeX;k++)
		tableau.elements[k] = x;

	return tableau;
}


unsignedArray remplir_ua(unsignedArray tableau, unsigned x)
{
	for (unsigned k = 0; i<tableau.sizeX;k++)
		tableau.elements[k] = x;

	return tableau;
}


