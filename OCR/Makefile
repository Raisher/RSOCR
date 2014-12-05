CC=clang
 
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS= -lm
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
SRC= pixel_operation.h pixel_operation.c detection.c
OBJ= ${SRC:.c=.o}
 
all: OCR
 
OCR: ${OBJ}
 
clean:
	rm -f *~*.o
