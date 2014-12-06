#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operation.h"


int average_color(SDL_Surface *s);
SDL_Surface* binarize(SDL_Surface *s);
int detect_wlines(SDL_Surface *s, int x, int y, int xmax, int ymax);
int detect_wlines_side(SDL_Surface *s, int x, int y, int xmax, int ymax);
int detect_endblack(SDL_Surface *s, int x, int y, int xmax, int ymax);
int detect_endblack_side(SDL_Surface *s, int x, int y, int xmax, int ymax);
void detect_block_side(SDL_Surface *s, struct Block *c);
SDL_Surface* detect_block(SDL_Surface *s);
