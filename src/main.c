#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "game.h"

#define GAME_TITLE "2D SDL Game"

Game game;

int main() {

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL_INIT failed\n");
		exit(1);
	} else {
		printf("SDL subsystems all good...\n");
	}

	memset(&game, 0, sizeof(Game));

	game.window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if(game.window == NULL) {
		fprintf(stderr, "SDL window failed to create\n");
		exit(1);
	} else {
		//GAME GETS SET TO RUNNING HERE
		game.running = true;
		printf("SDL window is good...\n");
	}

	game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
	if(game.renderer == NULL) {
		fprintf(stderr, "SDL renderer failed to create\n");
		exit(1);
	}

	while (game.running) {
		SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
		SDL_RenderClear(game.renderer);

		handle_input();

		SDL_RenderPresent(game.renderer);
		SDL_Delay(16);
	}
	

	SDL_DestroyWindow(game.window);
	SDL_DestroyRenderer(game.renderer);
	SDL_Quit();

	printf("Game exited\n");
	return 0;
}

