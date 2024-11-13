build:
	gcc src/*.c -lSDL2 -ldl -o out/game

run:
	./out/game

clean:
	rm /out/game
