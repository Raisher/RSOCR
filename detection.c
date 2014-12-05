#include "detection.h"

/*struct Vector
{
	int x;
	int y;
};*/
struct Block
{
	int x;
	int y;
	int xbegin;
	int ybegin;
	int xend;
	int yend;
};

int average_color(SDL_Surface *s)
{
  Uint8 r, g, b;
  int sum = 0, nbpixel = 0;
  for(int i = 0; i < s->h; ++i)
  {
    for(int j = 0; j < s->w; ++j)
    {
      Uint32 pixel = getpixel(s,j,i);
      SDL_GetRGB(pixel, s->format, &r, &g, &b);
      sum += ( r + g + b ) / 3;
      nbpixel++;
    }
  }
  return sum / nbpixel;
}

SDL_Surface*  binarize(SDL_Surface *s) {
  Uint8 r, g, b;
  double grey;
  int average = average_color(s);
  for(int i = 0; i < s->h; ++i)
  {
    for(int j = 0; j < s->w; ++j)
    {
      Uint32 pixel = getpixel(s,j,i);
      SDL_GetRGB(pixel, s->format, &r, &g, &b);
      grey = (double)r*0.3 + (double)g*0.59+(double)b*0.11;
      if ( grey < average )
        pixel = SDL_MapRGB(s->format, 0, 0, 0);
      else
        pixel = SDL_MapRGB(s->format,255,255,255);
      putpixel(s, j, i, pixel);
    }
  }
  return s;
}

// Aerer le code

int check = 0;



int detect_wlines(SDL_Surface *s, int x, int y, int xmax, int ymax)
{
	Uint8 r, g, b;
	int blackpixel = 0;
	int whitepixel = 0;
	Uint32 pixel;
	for (; x<xmax && blackpixel == 0 ;x++)
	{
		y = 0;
		while(y < ymax && blackpixel == 0)
		{
			pixel = getpixel(s,y,x);
			SDL_GetRGB(pixel, s->format, &r, &g, &b);
	    if (r == 0 && g == 0 && b == 0)
      {
        blackpixel = 1;
      }
			whitepixel++;
			y++;
		}
		check++;
	}
	return whitepixel / ymax;
}

int detect_wlines_side(SDL_Surface *s, int x, int y, int xmax, int ymax)
{
	Uint8 r, g, b;
	int blackpixel = 0;
	int whitepixel = 0;
	Uint32 pixel;
	for (; y<xmax && blackpixel == 0 ; y++)
	{
		y = 0;
		while(x < xmax && blackpixel == 0)
		{
			pixel = getpixel(s,y,x);
			SDL_GetRGB(pixel, s->format, &r, &g, &b);
	    if (r == 0 && g == 0 && b == 0)
      {
        blackpixel = 1;
      }
			whitepixel++;
			y++;
		}
		check++;
	}
	return whitepixel / ymax;
}

int detect_endblack(SDL_Surface *s, int x, int y, int xmax, int ymax)
{
	Uint8 r, g, b;
	int blackpixel = 1;
	int nbblackline = 0;
	Uint32 pixel;
	for(; x < xmax && blackpixel != 0; x++)
  {
    blackpixel = 0;
		for(y = 0; y < ymax ; ++y)
    {
			pixel = getpixel(s,y,x);
			SDL_GetRGB(pixel, s->format, &r, &g, &b);
      if (r == 0 && g == 0 && b == 0)
			{
        blackpixel++;
      }
    }
		nbblackline++;
  }
	return nbblackline - 1;
}

int detect_endblack_side(SDL_Surface *s, int x, int y, int xmax, int ymax)
{
	Uint8 r, g, b;
	int blackpixel = 1;
	int nbblackline = 0;
	Uint32 pixel;
	for(; y < ymax && blackpixel != 0; y++)
  {
    blackpixel = 0;
		for(x = 0; x < xmax ; ++x)
    {
			pixel = getpixel(s,y,x);
			SDL_GetRGB(pixel, s->format, &r, &g, &b);
      if (r == 0 && g == 0 && b == 0)
			{
        blackpixel++;
      }
    }
		nbblackline++;
  }
	return nbblackline - 1;
}


void detect_block_side(SDL_Surface *s, struct Block *c)
{
	Uint32 pixelrouge = SDL_MapRGB(s->format,255,0,0);
	while( c->y < s->h )
	{
		check = 0;
		c->y = 1 + c->y + detect_wlines_side(s, c->x, c->y, c->xend, s->h);

		for (int p = c->xbegin; p < c->xend; ++p)
    {
      putpixel(s, c->y-2 , p, pixelrouge);
    }

		//printf("%d, %d\n",c->xbegin, c->xend);

		c->yend = 1 + c->y + detect_endblack_side(s, c->x, c->y, c->xend, s->w);
		c->y = c->yend;
	}
}

SDL_Surface* detect_block(SDL_Surface *s)
{
	struct Block *cur = malloc(sizeof(struct Block));
	cur->x = 0;
	cur->y = 0;
	cur->xbegin = 0;
	cur->ybegin = 0;
	cur->xend = 0;
	cur->yend = 0;

	int keep = 0;

	Uint32 pixelrouge = SDL_MapRGB(s->format,255,0,0);

	while(cur->x < s->h)
	{
		check = 0;

		cur->x = 1 + cur->x + detect_wlines(s, cur->x, cur->y, s->h, s->w);

		if ( check > 20 && cur->x < s-> h )
		{
			if ( cur->xend != 0 )
			{
				//detect_block_side(s, cur);
			}
			keep = cur->x;
			cur->xbegin = keep;
		}

		//printf("x : %d, xbegin, : %d\n", cur->x, cur->xbegin);
		/*if( check > 20 )
		{
			if(cur->x < s->h)
			{
				for (int p = 0; p<s->w ; ++p)
				{
					putpixel(s,p,cur->x-2,pixelrouge);
				}
			}
			if (cur->xend != 0)
			{
				for (int p = 0; p<s->w ; ++p)
				{
					putpixel(s,p,cur->xend-2,pixelrouge);
				}
			}
		}*/

		cur->xend = 1 + cur->x + detect_endblack(s, cur->x, cur->y, s->h, s->w);
		cur->x = cur->xend;

	}
	return s;
}
