#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_KEYBOARD_KEYS 300

/// Core Game Struct ///
typedef struct {
	bool running;
	SDL_Renderer* renderer;
	SDL_Window* window;
	int keyboard[MAX_KEYBOARD_KEYS];
} Game;

enum gamestate {
	GS_TEST_1,
	GS_TEST_2,
};

