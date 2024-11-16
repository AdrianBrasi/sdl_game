build:
	gcc src/*.c -lSDL2 -ldl -lSDL2_ttf -o out/game

run:
	./out/game

clean:
	rm /out/game
