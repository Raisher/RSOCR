#include "pixel_operation.h"
#include <stdio.h>
#include <stdlib.h>
#include "detection.h"

struct doublearray
{
	unsigned sizeX;
	double *elm;
};

struct doublearray2D
{
	unsigned sizeX;
	unsigned sizeY;
	struct doublearray *elm;
};

struct listmat{
	struct doublearray2D mat;
	struct listmat *next;
};

struct doublearray2D Norm(struct doublearray2D, SDL_Surface *s, int x, int y, int xend, int yend);
