#include "detection.h"
#include "pixel_operation.h"

struct Block
{
    int x;
    int y;
};


void addlist(struct charlist *l,int x,int y, int xend, int yend)
{
  while(l->next!=NULL)
  {
    l=l->next;
  }
  struct charlist *aux = malloc(sizeof(struct charlist));
  aux->x=x;
  aux->y=y;
  aux->xend=xend;
  aux->yend=yend;
  aux->next=NULL;
  l->next=aux;
}

SDL_Surface* nored(SDL_Surface *s)
{
	Uint8 r, g, b;
	for (int i = 0; i < s->h; ++i)
    {
        for (int j = 0; j < s->w; ++j)
        {
            Uint32 pixel = getpixel(s, j, i);
            SDL_GetRGB(pixel, s->format, &r, &g, &b);
						if (r == 255 && g == 0 && b == 0)
						{
                pixel = SDL_MapRGB(s->format, 255, 255, 255);
              	putpixel(s, j, i, pixel);
						}
        }
    }
		return s;
}

// Aerer le code

// FONCTIONS UTILITAIRES

int check = 0;

int detect_wlines(SDL_Surface * s, int x, int y, int xmax, int ymax)
{
    Uint8 r, g, b;
    int blackpixel = 0;
    int whitepixel = 0;
    Uint32 pixel;
    for (; x < xmax && blackpixel == 0; x++)
    {
        y = 0;
        while (y < ymax && blackpixel == 0)
        {
            pixel = getpixel(s, y, x);
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

int detect_wlines_side(SDL_Surface * s, int x, int y, int xmax, int ymax)
{
    Uint8 r, g, b;
    int blackpixel = 0;
    int whitepixel = 0;
    Uint32 pixel;
    for (; y < ymax && blackpixel == 0; y++)
    {
        x = 0;
        while (x < xmax && blackpixel == 0)
        {
            pixel = getpixel(s, y, x);
            SDL_GetRGB(pixel, s->format, &r, &g, &b);
            if (r == 0 && g == 0 && b == 0)
            {
                blackpixel = 1;
            }
            whitepixel++;
            x++;
        }
    }
    return whitepixel / ymax;
}

int detect_endblack(SDL_Surface * s, int x, int y, int xmax, int ymax)
{
    Uint8 r, g, b;
    int blackpixel = 1;
    int nbblackline = 0;
    Uint32 pixel;
    for (; x < xmax && blackpixel != 0; x++)
    {
        blackpixel = 0;
        for (y = 0; y < ymax; y++)
        {
            pixel = getpixel(s, y, x);
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
    for (; y < ymax && blackpixel != 0; y++)
    {
        blackpixel = 0;
        for (x = 0; x < xmax; x++)
        {
            pixel = getpixel(s, y, x);
            SDL_GetRGB(pixel, s->format, &r, &g, &b);
            if (g != 255)
            {
                blackpixel++;
            }
        }
        nbblackline++;
    }
    return nbblackline - 1;
}



void draw_char(SDL_Surface *s,int i1, int i2,struct charlist *list)
{
  Uint8 r, g, b;
  Uint32 pixelvert = SDL_MapRGB(s->format,255,0,0);
  int j1, j = 0;
  while (j < s->w)
  {
    int isblack = 0;
    while( j < s->w && isblack == 0)
    {
      int k = i1;
      while ( k < i2  && isblack == 0)
      {
        Uint32 pixel = getpixel(s,j,k);
        SDL_GetRGB(pixel, s->format, &r, &g, &b);
        if (r == 0 && g == 0 && b == 0)
        {
          isblack = 1;
        }
        k++;
      }
      j++;
    }
    int j1 = j;
    for (int p = i1; p < i2 - 1; ++p)
    {
      putpixel(s,j-2,p,pixelvert);
    }
    int blackpixel = 1;
    for(; j < s->w && blackpixel != 0; j++)
    {
      blackpixel = 0;
      int l = i1;
      for(; l < i2; ++l)
      {
        Uint32 pixel = getpixel(s,j,l);
        SDL_GetRGB(pixel, s->format, &r, &g, &b);
        if (r == 0 && g == 0 && b == 0)
        {
          blackpixel++;
        }
      }
    }
    for (int p = i1; p < i2 ; ++p)
    {
      putpixel(s,j-1,p-1,pixelvert);
    }   
  addlist(list,i1,j1,i2,j);
  } 
}

// Aerer le code 

// FONCTION QUI TRACE LES LIGNES INF ET SUP DE CHAUE LIGNE

// Aerer le code

SDL_Surface* detect_line(SDL_Surface *s, int x,int y, int xe, int ye, int doforchar,struct charlist *list) 
{
  Uint8 r, g, b;
  Uint32 pixelrouge = SDL_MapRGB(s->format,255,0,0);
  int i = 0;
  while ( i < s->h )
  {
    int isblack = 0;
    int j=0;
    while ((i < s->h) && (isblack == 0))
    {
     j = 0;
      while ((j < s->w) && (isblack == 0)) 
      {
         Uint32 pixel = getpixel(s,j,i);
         SDL_GetRGB(pixel, s->format, &r, &g, &b);
         if (r == 0 && g == 0 && b == 0)
         {
           isblack = 1;
         }
         j++;
      }
    i++;
    }
    int isave = i;
    for (int p = 0; p<s->w ; ++p)
    {
      putpixel(s,p,i-2,pixelrouge);
    } 
    int blackpixel = 1;
    for(; i < s->h && blackpixel != 0; ++i)
    {
      blackpixel = 0;
      for(j = 0; j < s->w ; ++j)
      {
        Uint32 pixel = getpixel(s,j,i);
        SDL_GetRGB(pixel, s->format, &r, &g, &b);
        if (r == 0 && g == 0 && b == 0)
        {
          blackpixel++;
        }
      }
    }
    for (int p = 0; p<s->w && i < s->h ; ++p)
    {
      putpixel(s,p,i-1,pixelrouge);
    }  
    if(doforchar == 1)
    {
    draw_char(s, isave - 1, i,list);
    }
    i++;
  }
  return s;
}




// DETECT_BLOCK

int ybegin = 0;
int yend = 0;
int xbegin = 0;
int xend = 0;

SDL_Surface* detect_block_slide(SDL_Surface * s, struct Block *c,struct charlist *list)
{
    Uint32 pixelrouge = SDL_MapRGB(s->format, 255, 0, 0);
    c->y = 0;
    while (c->y < s->w)
    {
        ybegin = 1 + c->y + detect_wlines_side(s, c->x, c->y, s->h, s->w);
        c->y = ybegin;

        yend = 1 + c->y + detect_endblack_side(s, c->x, c->y, s->h, s->w);
        c->y = yend;
	
        if (yend - ybegin > 1)
        {
	    s=detect_line(s,xbegin,ybegin,xend,yend,0,list);
            for (int p = xbegin - 0; p < xend - 1; ++p)
            {
                putpixel(s, yend - 2, p, pixelrouge);
            }
            if (c->y < s->w)
            {
                for (int p = xbegin - 1; p < xend - 1; ++p)
                {
                    putpixel(s, ybegin - 2, p, pixelrouge);
                }
            }
	    s=detect_line(s,xbegin,ybegin,xend,yend,1,list);
        }

        if (c->y < s->w && yend - ybegin > 1)
        {
            for (int p = ybegin - 1; p < yend - 1; ++p)
            {
                putpixel(s, p, xbegin - 2, pixelrouge);
            }
            for (int p = ybegin - 1; p < yend - 1; ++p)
            {
                putpixel(s, p, xend - 1, pixelrouge);
            }
        }
    }
    return s;
}


SDL_Surface *detect_block(SDL_Surface * s,struct charlist *list)
{
    struct Block *cur = malloc(sizeof (struct Block));
    cur->x = 0;
    cur->y = 0;

    Uint32 pixelrouge = SDL_MapRGB(s->format, 255, 0, 0);

    while (cur->x < s->h)
    {
        check = 0;

        xbegin = 1 + cur->x + detect_wlines(s, cur->x, cur->y, s->h, s->w);

        if (check > 20)
        {
            if (xend != 0)
            {
                s=detect_block_slide(s, cur,list);
            }
            if (cur->x < s->h)
            {
                cur->x = xbegin;
            }
        }

        xend = 1 + cur->x + detect_endblack(s, cur->x, cur->y, s->h, s->w);
        cur->x = xend;

    }
    int np = SDL_SaveBMP(s, "result.bmp");
    return s;
}

struct charlist* newlist()
{
  struct charlist *l = malloc(sizeof(struct charlist));
  l->x=0;
  l->y=0;
  l->xend=0;
  l->yend=0;
  l->next=NULL;
  return l;
}
void Detection(SDL_Surface *s,struct charlist *list)
{
   s=detect_block(s,list);
	 Resizechar(s,list);
   int np = SDL_SaveBMP(s,"result.bmp");
} 
