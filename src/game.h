#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIN_W 1920
#define WIN_H 1080
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

enum gamestate {
	GS_TEST_1,
	GS_TEST_2,
};

