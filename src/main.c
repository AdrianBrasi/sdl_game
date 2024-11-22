#ifdef __APPLE__
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "game.h"
#include "text.h"

//TODO: create primitive gamestate loading and freeing functions

void cleanup();

Game game;

int main() {

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL subsystems failed to initialize\n");
		exit(1);
	} else { printf("All SDL subsystems good\n"); }

	//INITIALIZE GAME RESOURCES && SET GAME RUNNING = TRUE;
	memset(&game, 0, sizeof(Game));
	game.running = true;
	atexit(cleanup);

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
	} else { printf("SDL renderer is good\n"); }

	SDL_ShowCursor(SDL_ENABLE);

	if (TTF_Init() == 0 ) {
		printf("SDL TTF is good\n");
	} else {
		fprintf(stderr, "SDL TTF failed to initialize\n");
		exit(1);
	}

	TTF_Font* main_text_font = load_font("./fonts/ibm.ttf", 50);

	Text main_text = {
		.font = main_text_font,
		.content = "This is the fucking game",
		.color = {255, 255, 255, 255},
		.x = 700,
		.y = 1000
	};

	place_static_text(game.window, &main_text, 0, 0, TEXT_CENTERED);

	Text other_text = {
		.font = main_text_font,
		.content = "x_center test",
		.color = {255, 255, 255, 255},
		.x = 1000,
		.y = 1000,
	};

	place_static_text(game.window, &other_text, 0, 500, TEXT_CENTERED_X);

	while (game.running) {
		SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
		SDL_RenderClear(game.renderer);

		handle_input();
		render_text(&main_text, game.renderer);
		render_text(&other_text, game.renderer);

		SDL_RenderPresent(game.renderer);
		SDL_Delay(16);
	}

	TTF_CloseFont(main_text_font);

	return 0;
}


void cleanup() {
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
	TTF_Quit();
	SDL_Quit();
	printf("Game resources have been freed\n");
}
