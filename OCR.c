#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>



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
   display_image(load_image("test_ocr.jpg"));
   return 0;
}
