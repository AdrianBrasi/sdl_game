CC = gcc

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    CFLAGS = -I/opt/homebrew/include/SDL2
    LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
else
    CFLAGS = -I/usr/include/SDL2
    LDFLAGS = -L/usr/lib -lSDL2 -lSDL2_ttf
endif

SRC = src/*.c
OUT = out/game

build:
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)

run:
	./$(OUT)

clean:
	rm -f $(OUT)

