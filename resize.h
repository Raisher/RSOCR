#include "pixel_operation.h"
#include <stdio.h>
#include <stdlib.h>
#include "detection.h"

struct doublearray {
	unsigned sizeX;
	double *elements;
};

struct doublearray2D{
	unsigned sizeX;
	unsigned sizeY;
	int** elements;
};

struct listmat{
	struct doublearray2D mat;
	struct list *next;
};

void Resizechar(SDL_Surface *s, struct charlist *list);
