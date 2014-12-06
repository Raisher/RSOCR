#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operation.h"


int average_color(SDL_Surface *s);
SDL_Surface* binarize(SDL_Surface *s);

SDL_Surface* detect_block(SDL_Surface *s);
