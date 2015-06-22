CC=gcc
CFLAGS=-std=c99 -Wall -g
LIBS=-lm -lpthread -lSDL
OUT=main

$(OUT): $(OUT).o gfx.o
	$(CC) $^ -o $@ $(LIBS)

$(OUT).o: $(OUT).c gfx.h
	$(CC) $(CFLAGS) $< -c

gfx.o: gfx.c gfx.h
	$(CC) $(CFLAGS) $< -c

clean:
	rm -f $(OUT) *.o
