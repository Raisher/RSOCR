CC=gcc
CFLAGS= -Wall -Wextra -std=c99 $(shell pkg-config --cflags gtk+-3.0 sdl) $(shell sdl-config --cflags)
LDFLAGS= $(shell pkg-config --libs gtk+-3.0 sdl) $(shell sdl-config --libs) -lSDL_image -lm
SRC= rotation.c detection.c pixel_operation.c suppbruit.c interface.c
SRCDIR=src
TARGET=OCR
# SOURCES=$(addprefix $(SRCDIR)/,$(SRC))
SOURCES=$(SRC)
OBJECTS=$(SOURCES:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(OBJECTS) $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

debug: CFLAGS += -g
debug: CC = clang
debug: all
