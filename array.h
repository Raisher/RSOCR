#ifndef FONCTION_ARRAY
#define FONCTION_ARRAY

typedef struct 
{
	unsigned sizeX;
	unsigned *elements;
} unsignedArray;

typedef struct 
{
	unsigned sizeX;
	unsigned *elements;
} doubleArray;

typedef struct 
{
	unsigned sizeX;
	unsigned sizeY;
	unsignedArray *elements;
} unsignedArray2D;

typedef struct 
{
	unsigned sizeX;
	unsigned sizeY;
	doubleArray *elements;
} doubleArray2D;

doubleArray nouveau_doubleArray(unsigned i);
doubleArray2D nouveau_doubleArray2D(unsigned i, unsigned j);
doubleArray remplir_da(doubleArray tableau, double x);
unsignedArray nouveau_unsignedArray(unsigned i);
unsignedArray2D nouveau_unsignedArray2D(unsigned i, unsigned j);
unsignedArray remplir_ua(unsignedArray tableau, double x);

#endif
