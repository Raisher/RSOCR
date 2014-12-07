#include "pixel_operation.h"
#include "binarisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#define MAX_BRIGHTNESS 255
#define L 256
#define max(a,b)(a>=b?a:b)
#define min(a,b)(a<=b?a:b)

SDL_Surface* otsu_th(SDL_Surface *s)
{
	SDL_Surface *new_s;
	float *hist = malloc (sizeof(float)*256);
	int  i,x, y, max_x, max_y;
	Uint8 r,g,b;
	Uint8 r1, g1, b1;
	max_x = s->w;
	max_y = s->h;
	new_s = SDL_CreateRGBSurface(SDL_HWSURFACE, s->w, s->h, s->format->BitsPerPixel, s->format->Rmask, s->format->Gmask, s->format->Bmask, s->format->Amask);
	int total=max_x*max_y;


	double prob[256], omega[256];
	double mu[256];
	double max_sigma, sigma[256];



	for (int i =0; i<=256;i++)
		hist[i]= 0.0;


	for (int x = 0; x < max_x;++x)
		for(int y = 0; y<max_y; y++)
		{
			Uint32 current = getpixel(s,x,y);
			SDL_GetRGB(current, s->format, &r, &g, &b);
			int graylevel = max(0.0, min(255.0, 0.299*r+0.587*g+0.114*b));
			hist[graylevel]+=1;
		}
 
	for (int i=0; i<256;i++)
		prob[i] = (double)hist[i]/total;

	omega[0]=prob[0];
	mu[0]=0.0;
	for(i=1;i<256;i++)
	{
		omega[i] = omega[i-1] + prob [i];
		mu[i] = mu[i-1]*prob[i];
	}

	int threshold = 0;
	max_sigma=0.0;
	for (i=0;i<255;i++)
	{
		if (omega[i] != 0.0 && omega[i] != 1.0)
			sigma[i] = pow(mu[255]*omega[i]-mu[i], 2)/(omega[i]*(1.0 -omega[i]));
		else
			sigma[i]=0.0;
		if (sigma[i] > max_sigma)
		{
			max_sigma = sigma[i];
			threshold = i;
		}
	}

	for (x = 0; x < max_x; x++)
		for (y = 0; y< max_y; y++)
		{
			Uint32 actpixel1 = getpixel(s,x,y);
			SDL_GetRGB(actpixel1, s->format, &r1,&g1,&b1);
			int graylevel =  max(0.0, min(255.0, 0.299*r1+0.587*g1+0.114*b1));
			if (graylevel < 128)
				putpixel(new_s, x,y, SDL_MapRGB(s->format, 0,0,0));
			else
				putpixel(new_s,x,y, SDL_MapRGB(s->format, 255,255,255));
		}
	return (new_s);
}
