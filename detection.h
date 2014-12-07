#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operation.h"

struct charlist
{
	   int x;
		 int y;
		 int xend;
		 int yend;
		 struct charlist *next;
};

struct charlist* newlist();
SDL_Surface* detect_block(SDL_Surface *s,struct charlist *list);
