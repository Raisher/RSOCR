#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operation.h"


void wait_for_keypressed(void) {
  SDL_Event event;
  for(;;) {
    SDL_PollEvent( &event);
    switch(event.type) {
      case SDL_KEYDOWN : return;
      default : break;
    }
  }
}

SDL_Surface*  binarize(SDL_Surface *s) {
  Uint8 r, g, b;
  double grey;
  for(int i = 0; i < s->w; ++i)
  {
    for(int j = 0; j < s->h; ++j)
    {
      Uint32 pixel = getpixel(s,i,j);
      SDL_GetRGB(pixel, s->format, &r, &g, &b);
      grey = (double)r*0.3 + (double)g*0.59+(double)b*0.11;
      if (grey<255/2)
        pixel = SDL_MapRGB(s->format, 0, 0, 0);
      else
        pixel = SDL_MapRGB(s->format,255,255,255);
      putpixel(s, i, j, pixel);
    }
  }
  return s;
}
void bite(){};

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}
 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}


void init_sdl(void) {
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    errx(1,"Could not initialise SDL : %s. \n", SDL_GetError());
  }
}
 
SDL_Surface* load_image(char *path) {
  SDL_Surface *img;
  img = IMG_Load(path);
  if (!img)
    errx(3,"Can't load %s : %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface *screen;
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE | SDL_ANYFORMAT);
  if (screen == NULL) {
    errx(1, "Couldn't set %dx%d video mode : %s\n", 
         img->w, img->h, SDL_GetError());
  }
  if (SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error : %s\n", SDL_GetError());
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
  wait_for_keypressed();
  return screen;
}


int main()
{
   init_sdl();
   SDL_Surface *img = load_image("test_ocrbite.jpg");
   display_image(img);
   display_image(binarize(img));
   return 0;
}
