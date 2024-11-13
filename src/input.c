#include "game.h"
#include "input.h"

extern Game game;

void handle_input(){
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
			key_press_down(&event.key);
			break;
			case SDL_KEYUP:
			key_press_down(&event.key);
			break;
			case SDL_QUIT:
				printf("Game quitting...\n");
				exit(0);
				break;
		}
	}
}

void key_press_up(SDL_KeyboardEvent* event){
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		game.keyboard[event->keysym.scancode] = 0;
	}
}

void key_press_down(SDL_KeyboardEvent *event) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		game.keyboard[event->keysym.scancode] = 1;
	}
}
