#include "pixel_operation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "rotation.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

float trouver_deg(SDL_Surface *s)
{
	float deg = 0;
	int pix_count = 0;
	int pix_comp = 0;
	float final_deg = -(PI/12);
	int x = 0;
	int y = 0;
	SDL_Surface *sdl_copy;

	for (deg = -(PI/7); deg <= (PI/7); deg += (PI/700))
	{
		sdl_copy = SDL_RotationCentralN(s, deg);
		pix_count = 0;
		for (y = 0; y < s->h; y++)
		{
			for (x = 0; (x < s->w) && (getpixel(sdl_copy,x,y) == 1); x++)
			{
				if (x >= s->w)
				{ 
					pix_count++;
				}
			}
		}
		if (pix_count > pix_comp)
		{
			pix_comp = pix_count;
			final_deg = deg;
		}
		SDL_FreeSurface(sdl_copy);
	}
	printf("%f\n", final_deg);
	return (final_deg);
}

SDL_Surface* SDL_RotationCentralN(SDL_Surface *s, float angle)
{
	SDL_Surface* dst;
	int i;
	int j;
	Uint32 couleur;
	int mx, my, mxdest, mydest;
	int bx, by;
	float angle_radian;
	float tcos;
	float tsin;
	double largeurdst;
	double hauteurdst;

	angle_radian = -angle * M_PI / 180.0;

	tcos = cos(angle_radian);
	tsin = sin(angle_radian);

	largeurdst = ceil(s->w * fabs (tcos) + s->h * fabs (tsin));
	hauteurdst = ceil(s->w * fabs (tsin)+ s-> h * fabs (tcos));

	dst = SDL_CreateRGBSurface (SDL_HWSURFACE, largeurdst, hauteurdst, s->format->BitsPerPixel, s->format->Rmask, s->format->Gmask, s->format->Bmask, s->format->Amask);

	if(dst==NULL)
		return NULL;
	
	mxdest = dst -> w/2.;
	mydest = dst -> h/2.;
	mx = s -> w/2.;
	my = s -> h/2.;

	for(j=0; j<dst->h; j++)
		for(i = 0;i<dst -> w; i++)
		{
			bx = (ceil(tcos * (i-mxdest)+ tsin * (j-mydest) +mx));
			by = (ceil(-tsin * (i-mxdest) +tcos * (j-mydest) +my));

			if (bx >= 0 && bx < s-> w && by >= 0 && by < s->h)
			{
				couleur = getpixel(s, bx, by);
				putpixel (dst, i, j, couleur);
			}
		}
	return dst;
}



