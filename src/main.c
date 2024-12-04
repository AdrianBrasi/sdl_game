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

//TODO: create primitive gamestate loading and freeing functions

void cleanup();

Game game;
SceneManager game_manager = {0};

Scene main_menu = {
	.init = main_menu_init,
	.update = main_menu_update,
	.render = main_menu_render,
	.cleanup = main_menu_cleanup,
	.data = NULL
};

Scene level_one = {
	.init = level_one_init,
	.update = level_one_update,
	.render = level_one_render,
	.cleanup = level_one_cleanup,
};

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


	game_manager.current_scene = &main_menu;
	game_manager.current_scene->init(game_manager.current_scene);

	while (game.running) {
		if (game_manager.current_scene->update) {
			game_manager.current_scene->update(game_manager.current_scene);
		}
		if (game_manager.current_scene->render) {
			game_manager.current_scene->render(game_manager.current_scene);
		}
	}

	if (game_manager.current_scene->cleanup) {
		game_manager.current_scene->cleanup(game_manager.current_scene);
	}

	return 0;
}


void cleanup() {
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
	TTF_Quit();
	SDL_Quit();
	printf("Game resources have been freed\n");
}
