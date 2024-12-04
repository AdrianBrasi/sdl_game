#pragma once

#ifdef __APPLE__
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <stdbool.h>
#include "text.h"

#define WIN_W 1280
#define WIN_H 720
#define MAX_KEYBOARD_KEYS 300
#define MAX_MOUSE_BUTTONS 10

/// Core Game Struct ///
typedef struct {

	bool running;
	SDL_Renderer* renderer;
	SDL_Window* window;
	int keyboard[MAX_KEYBOARD_KEYS];

	struct {
		int x;
		int y;
		int buttons[MAX_MOUSE_BUTTONS];
		bool visible;
	} mouse;

} Game;

/// Gamestate handling ///
typedef struct Scene {
    void (*init)(struct Scene* self);
    void (*update)(struct Scene* self);
    void (*render)(struct Scene* self);
    void (*cleanup)(struct Scene* self);
    void* data;
} Scene;

typedef struct SceneManager {
	 Scene* current_scene;
} SceneManager;

void change_scene(SceneManager* manager, Scene* new_scene);

/// SCENE HEADERS ///

/// Main Menu ///
typedef struct {
	Text title;
	Text sub_title;
	//TODO: Button
} MainMenuData;

void main_menu_init(Scene* self);
void main_menu_update(Scene* self);
void main_menu_render(Scene* self);
void main_menu_cleanup(Scene* self);

/// Level One ///
typedef struct {
	Text test_text;
} LevelOneData;

void level_one_init(Scene* self);
void level_one_update(Scene* self);
void level_one_render(Scene* self);
void level_one_cleanup(Scene* self);
