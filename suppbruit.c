#include "pixel_operation.h"
#include <stdio.h>
#include <stdlib.h>
#include "suppbruit.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void insert (Uint32* tab, int val, int size)
{
	int i = size -1;
	tab[size -1] = val;
	while ((i>0) && tab[i] < tab[ i - 1])
	{
		tab[i] = tab[i] + tab [i-1];
		tab[i-1] = tab[i]-tab [i-1];
		tab[i] = tab [i] - tab[i-1];
		i--;
	}
}

int exist (int x, int y, SDL_Surface *s)
{
	return ((x>=0) && (x < s->w) && (y>=0) && (y < s->h));
}

SDL_Surface* suppression(SDL_Surface *s)
{
	SDL_Surface *new_s;
	int nbcase;
	int x; 
	int y;
	Uint32 tab[9] = {0};
	int i;
	int j;
	int median = 0;

	new_s = SDL_CreateRGBSurface (SDL_HWSURFACE, s->w, s->h, s->format->BitsPerPixel, s->format->Rmask, s->format->Gmask, s->format->Bmask, s->format->Amask);

	if(new_s==NULL || s ==NULL)
		return NULL;

	for (x = 0; x< s->w; x++)
		for(y=0; y< s->h; y++)
		{
			nbcase = 0;
			for (i=-1; i<=1; i++)
				for (j=-1; j<=1; j++)
					if (exist (x+i, y+j, s))
					{
						Uint32 color = getpixel(s, x+i, y+j);
						insert(tab, color, ++nbcase);
					}
			median = nbcase/2;
			Uint32 actcolor = getpixel(s,x,y);
			if((nbcase == 9) && (actcolor == tab[median-2] ||
						actcolor == tab[median-1] ||
						actcolor == tab[median+1] ||
						actcolor == tab[median+2] ))
				putpixel(new_s, x ,y , actcolor);
			else
				putpixel(new_s,x,y,tab[nbcase/2]);
			
		}
	return (new_s);
}	
