CC=clang
 
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
SRC= OCR.c
OBJ= ${SRC:.c=.o}
 
all: OCR
 
OCR: ${OBJ}
 
clean:
	rm -f *~ *.o
	rm -f main
