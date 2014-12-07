# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
# include <stdlib.h>
# include <SDL.h>
 
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void init_sdl(void);
void wait_for_keypressed(void);

# endif


