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

SDL_Surface* otsu_th(SDL_Surface *s,int ok)
{
	SDL_Surface *new_s;
	float *hist = malloc (sizeof(float)*256);
	int  i,x, y, max_x, max_y;
	Uint8 r,g,b,R,G,B;
	Uint8 r1, g1, b1;
	max_x = s->w;
	max_y = s->h;
	new_s = SDL_CreateRGBSurface(SDL_HWSURFACE, s->w, s->h, 
	s->format->BitsPerPixel, s->format->Rmask, s->format->Gmask, 
	s->format->Bmask, s->format->Amask);
	int N=max_x*max_y;


	double prob[256], omega[256];
	double mu[256];
	double max_sigma, sigma[256];



	for (int i =0; i<=256;i++)
		hist[i]= 0.0;


	for (int x = 0; x < max_x;++x)
	{
		for(int y = 0; y<max_y; y++)
		{
			Uint32 current = getpixel(s,x,y);
			SDL_GetRGB(current, s->format, &r, &g, &b);
			int graylevel = max(0.0, min(255.0, 0.299*r+0.587*g+0.114*b));
			hist[graylevel]+=1;
		}
	}
	for (int i = 0;i<256; i++)
		hist[i]=hist[i]/N;
	
	float ut = 0;
	for (int i = 0;i<256;i++)
		ut+=i*hist[i];
	
	int max_k = 0;
	int max_sigma_k_=0;
	for(int k = 0; k<256;k++)
	{
		float wk=0;
		for(int i=0;i<=k;i++)
			wk+=hist[i];
		float uk = 0;
		for (int i = 0; i<=k;i++)
			uk+=i*hist[i];
		float sigma_k=0;
		if(wk!=0 && wk!=1)
			sigma_k = ((ut*wk-uk)*(ut*wk-uk))/(wk*(1-wk));
		if (sigma_k>max_sigma_k_)
		{
			max_k=k;
			max_sigma_k_=sigma_k;
		}
	}

	if (!ok)
	{
		for (int x=0;x<max_x;x++)
		{
			for(int y=0;y<max_y;y++)
			{
				Uint32 cur;
				cur = getpixel(s,x,y);
				SDL_GetRGB(cur,s->format,&R,&G,&B);
				int graylevel = max(0.0,min(255.0,0.299*R+0.587*G+0.114*B));
				if(graylevel < max_k)
					putpixel(new_s,x,y,SDL_MapRGB(s->format,0,0,0));
				else
					putpixel(new_s,x,y,SDL_MapRGB(s->format,255,255,255));
			}
		}
	}
	else
	{
		for (int x=0;x<max_x;x++)
		{
			for(int y=0;y<max_y;y++)
			{
				Uint32 cur;
				cur = getpixel(s,x,y);
				SDL_GetRGB(cur,s->format,&R,&G,&B);
				int graylevel = max(0.0,min(255.0,0.299*R+0.587*G+0.114*B));
				if(graylevel < max_k)
					putpixel(new_s,x,y,SDL_MapRGB(s->format,255,0,0));
				else
					putpixel(new_s,x,y,SDL_MapRGB(s->format,255,255,255));
			}
		}
	}
	int np = SDL_SaveBMP(new_s,"result.bmp");
	return (new_s);
}
