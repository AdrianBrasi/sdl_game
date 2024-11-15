#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "game.h"

Game game;

int main() {

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL subsystems failed to initialize\n");
		exit(1);
	} else { printf("All SDL subsystems good\n"); }

	memset(&game, 0, sizeof(Game));
	game.running = true;

	game.window = SDL_CreateWindow("Better than Concord", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);

	if(game.window == NULL) {
		fprintf(stderr, "SDL window failed to create\n");
		game.running = false;
		exit(1);
	} else { printf("SDL window is good\n"); }

	if(game.renderer == NULL) {
		fprintf(stderr, "SDL renderer failed to create\n");
		game.running = false;
		exit(1);
	} else { printf("SDL Renderer is good\n"); }

	SDL_ShowCursor(SDL_DISABLE);

	while (game.running) {
		SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
		SDL_RenderClear(game.renderer);

		handle_input();

		SDL_RenderPresent(game.renderer);
		SDL_Delay(16);
	}

	return 0;
}

