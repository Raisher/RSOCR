CC=clang
 
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS= -lm
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
SRC= neural_network.c
OBJ= ${SRC:.c=.o}
 
all: neural_network
 
OCR: ${OBJ}
 
clean:
	rm -f *~*.o
