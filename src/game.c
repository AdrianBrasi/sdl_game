#include "game.h"
#include "input.h"
#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Game game;

void change_scene(SceneManager* manager, Scene* new_scene) {
	if (manager->current_scene && manager->current_scene->cleanup) {
		manager->current_scene->cleanup(manager->current_scene);
	}

	printf("'change_scene' function has been invoked\n");

	manager->current_scene = new_scene;

	if (manager->current_scene && manager->current_scene->init) {
		manager->current_scene->init(manager->current_scene);
	}
}


void main_menu_init(Scene *self) {
	MainMenuData* data = malloc(sizeof(MainMenuData));
	self->data = data;

	TTF_Font* title_font_large = load_font("./fonts/ibm.ttf", 50);
	data->title.font = title_font_large;
	data->title.content = strdup("TITLE PAGE TEST MAIN FONT");
	data->title.color = (SDL_Color){255, 255, 255, 255};
	place_static_text(game.window, &data->title, 0, 0, TEXT_CENTERED);

	TTF_Font* title_font_small = load_font("./fonts/ibm.ttf", 25);
	data->sub_title.font = title_font_small;
	data->sub_title.content = strdup("TITLE PAGE TEST SMALLER FONT");
	data->sub_title.color = (SDL_Color){255, 255, 255, 255};
	place_static_text(game.window, &data->sub_title, 0, 500, TEXT_CENTERED_X);
}

void main_menu_update(Scene* self) {
	MainMenuData* data = (MainMenuData*)self->data;
	handle_input();
}

void main_menu_render(Scene* self) {
	MainMenuData* data = (MainMenuData*)self->data;

	SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
	SDL_RenderClear(game.renderer);

	render_text(&data->title, game.renderer);
	render_text(&data->sub_title, game.renderer);

	SDL_RenderPresent(game.renderer);
	SDL_Delay(16);

}

void main_menu_cleanup(Scene* self) {
	MainMenuData* data = (MainMenuData*)self->data;
	free(data->title.content);
	free(data->sub_title.content);
	TTF_CloseFont(data->title.font);
	free(data);
}

/// SCENE 2: LEVEL ONE ///


void level_one_init(Scene* self) {
	LevelOneData* data = malloc(sizeof(LevelOneData));
	TTF_Font* font = load_font("./fonts/ibm.ttf", 50);
	data->test_text.font = font;
	data->test_text.content = strdup("Level One...");
	data->test_text.color = (SDL_Color){255, 255, 255, 255};
	place_static_text(game.window, &data->test_text, 0, 0, TEXT_CENTERED);
}

void level_one_update(Scene* self) {
	LevelOneData* data = (LevelOneData*)self->data;
	handle_input();
}

void level_one_render(Scene* self) {
	LevelOneData* data = (LevelOneData*)self->data;
	SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
	SDL_RenderClear(game.renderer);

	render_text(&data->test_text, game.renderer);

	SDL_RenderPresent(game.renderer);
	SDL_Delay(16);
}

void level_one_cleanup(Scene* self) {
	LevelOneData* data = (LevelOneData*)self->data;
	free(data->test_text.content);
	TTF_CloseFont(data->test_text.font);
	free(data);
}
