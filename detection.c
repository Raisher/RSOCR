#include "detection.h"
#include "pixel_operation.h"

/*struct Vector
{
    int x;
    int y;
};*/
struct Block
{
    int x;
    int y;
    //int xend;
    //int yend;
};

struct list
{
    struct Block *begin;
    struct Block *end;
    struct list *next;
};

int average_color(SDL_Surface * s)
{
    Uint8 r, g, b;
    int sum = 0, nbpixel = 0;
    for (int i = 0; i < s->h; ++i)
    {
        for (int j = 0; j < s->w; ++j)
        {
            Uint32 pixel = getpixel(s, j, i);
            SDL_GetRGB(pixel, s->format, &r, &g, &b);
            sum += (r + g + b) / 3;
            nbpixel++;
        }
    }
    return sum / nbpixel;
}

SDL_Surface *binarize(SDL_Surface * s)
{
    Uint8 r, g, b;
    double grey;
    int average = average_color(s);
    for (int i = 0; i < s->h; ++i)
    {
        for (int j = 0; j < s->w; ++j)
        {
            Uint32 pixel = getpixel(s, j, i);
            SDL_GetRGB(pixel, s->format, &r, &g, &b);
            grey = (double) r *0.3 + (double) g *0.59 + (double) b *0.11;
            if (grey < average)
                pixel = SDL_MapRGB(s->format, 0, 0, 0);
            else
                pixel = SDL_MapRGB(s->format, 255, 255, 255);
            putpixel(s, j, i, pixel);
        }
    }
    int np = SDL_SaveBMP(s, "result.bmp");
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
                //printf("%d, %d, %d, %d\n",xmax, x, ymax, y);
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

int detect_endblack_side(SDL_Surface * s, int x, int y, int xmax, int ymax)
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
            if (r == 0 && g == 0 && b == 0)
            {
                blackpixel++;
            }
        }
        nbblackline++;
    }
    return nbblackline - 1;
}

struct list *add(int x, int y, int xend, int yend, struct list *l)
{
    struct list *t = NULL;
    t = malloc(sizeof (struct list));
    t->begin = malloc(sizeof (struct list));
    t->end = malloc(sizeof (struct list));
    t->begin->x = x;
    t->begin->y = y;
    t->end->x = xend;
    t->end->y = yend;
    t->next = l;
    return t;
}

struct list *newlist()
{
    struct list *l = malloc(sizeof (struct list));
    l->begin = malloc(sizeof (struct Block));
    l->begin->x = 0;
    l->begin->y = 0;
    l->end = malloc(sizeof (struct Block));
    l->end->x = 0;
    l->end->y = 0;
    l->next = NULL;
    return l;
}

struct list *recup_last(struct list *l)
{
    struct list *a = newlist();
    while (l->next->next != NULL)
    {
        l = l->next;
    }
    l->next = NULL;
    return l;
}


// FIN FONCTIONS UTILITAIRES

// DETECT_BLOCK

int ybegin = 0;
int yend = 0;
int xbegin = 0;
int xend = 0;

void detect_line(SDL_Surface * s, struct list *l)
{
    Uint32 pixelrouge = SDL_MapRGB(s->format, 255, 0, 0);
    struct list *a = NULL;
    int x;
    while (l->next != NULL)
    {
        a = recup_last(l);
        x = a->begin->x;
        while (x < a->end->x - 1)
        {
            xbegin =  x + detect_wlines(s, x, a->begin->y, a->end->x, a->end->y);
            x = xbegin;

            for (int p = a->begin->y; p < a->end->y; p++)
            {
                putpixel(s, p - 1, x - 2, pixelrouge);
            }
            xend =
                x + detect_endblack(s, x, a->begin->y, a->end->x, a->end->y);
            x = xend;
            for (int p = a->begin->y; p < a->end->y; p++)
            {
                putpixel(s, p - 1, x, pixelrouge);
            }
        }
    }
}

void detect_block_slide(SDL_Surface * s, struct Block *c)
{
    Uint32 pixelrouge = SDL_MapRGB(s->format, 255, 0, 0);
    c->y = 0;
    struct list *l = malloc(sizeof (struct list));
    l->begin = malloc(sizeof (struct Block));
    l->end = malloc(sizeof (struct Block));
    l->next = NULL;
    while (c->y < s->w)
    {
        ybegin = 1 + c->y + detect_wlines_side(s, c->x, c->y, s->h, s->w);
        c->y = ybegin;

        yend = 1 + c->y + detect_endblack_side(s, c->x, c->y, s->h, s->w);
        c->y = yend;
        if (yend - ybegin > 1)
        {
            l = add(xbegin, ybegin, xend, yend, l);
            for (int p = xbegin - 1; p < c->x - 1; ++p)
            {
                putpixel(s, yend - 2, p, pixelrouge);
            }
            if (c->y < s->w)
            {
                //printf("%d\n", c->y);
                for (int p = xbegin - 1; p < c->x - 1; ++p)
                {
                    putpixel(s, ybegin - 2, p, pixelrouge);
                }
            }
        }

        if (c->y < s->w && yend - ybegin > 1)
        {
            //printf("%d, %d, %d, %d, %d\n", c->y, ybegin, yend, xbegin, xend);
            for (int p = ybegin - 1; p < yend - 1; ++p)
            {
                putpixel(s, p, xbegin - 2, pixelrouge);
            }
            for (int p = ybegin - 1; p < yend - 1; ++p)
            {
                putpixel(s, p, xend - 1, pixelrouge);
            }
        }
        //l = l->next;
    }
    detect_line(s, l);
}

//gcc pixel_operation.c pixel_operation.h detection.c -std=c99 `pkg-config --libs sdl --cflags sdl` -lSDL_image

SDL_Surface *detect_block(SDL_Surface * s)
{
    struct Block *cur = malloc(sizeof (struct Block));
    cur->x = 0;
    cur->y = 0;
    //cur->xend = 0;
    //cur->yend = 0;

    Uint32 pixelrouge = SDL_MapRGB(s->format, 255, 0, 0);

    while (cur->x < s->h)
    {
        check = 0;

        cur->x = 1 + cur->x + detect_wlines(s, cur->x, cur->y, s->h, s->w);

        //printf("x : %d, xbegin, : %d\n", cur->x, cur->xbegin);
        if (check > 20)
        {
            if (xend != 0)
            {
                //printf("x : %d, xbegin : %d, keep : %d\n", cur->x, cur->xend, keep);
                detect_block_slide(s, cur);
            }
            if (cur->x < s->h)
            {
                xbegin = cur->x;
            }
        }

        xend = 1 + cur->x + detect_endblack(s, cur->x, cur->y, s->h, s->w);
        cur->x = xend;

    }
    int np = SDL_SaveBMP(s, "result.bmp");
    return s;
}


/*int main(int argc, char *argv[])
{
   init_sdl();
   if (argc!=1) {
     SDL_Surface *img = load_image(argv[1]);
     display_image(img);
     SDL_Surface *img2 = binarize(img);
         display_image(img2);
     display_image(detect_block(img2));
     return 0;
   }
   else {
     printf("Mettre une image en parametre \n");
     return 0;
   }
}*/
