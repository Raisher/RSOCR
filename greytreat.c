#include <stdio.h>
#include <stdlib.h>
#include "pixel_operation.h"
#include "greytreat.h"

void toGrayLevel(SDL_Surface *s)
{
	int i;
	int j;
	Uint32 grey;
	Uint8 r,g,b;
	for(i = 0; i < s->w; i++)
		for(j = 0; j < s->h; j++)
		{
			SDL_GetRGB(getpixel(s,i,j), s->format, &r, &g, &b);
			grey =((Uint32)r + (Uint32)g + (Uint32) b)/3;
			Uint32 pixel = SDL_MapRGB (s -> format, grey, grey, grey);
			putpixel(s, i,j, pixel);
		}
		int np = SDL_SaveBMP(s, "result.bmp"); 
}
		       	
