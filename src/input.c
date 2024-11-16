#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <stdio.h>

#include "game.h"
#include "input.h"

extern Game game;

void handle_input(){
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
			key_down(&event.key);
			log_keyboard_input(&event.key);
			break;

			case SDL_KEYUP:
			key_up(&event.key);
			break;

			case SDL_MOUSEBUTTONDOWN:
			mouse_down(&event.button);
				log_mouse_input(&event.button);
			break;

			case SDL_MOUSEBUTTONUP:
			mouse_up(&event.button);
			break;

			case SDL_QUIT:
				printf("Game quitting\n");
				game.running = false;
				exit(0);
				break;
		}
	}
	SDL_GetMouseState(&game.mouse.x, &game.mouse.y);
}

void log_keyboard_input(SDL_KeyboardEvent* key_event) {
	printf("Key press: %s\n", SDL_GetKeyName(key_event->keysym.sym));
}

void log_mouse_input(SDL_MouseButtonEvent *button_event) {
	printf("Mouse %d press: (%d, %d)\n",
		button_event->button,
		button_event->x,
		button_event->y
		);
}

static void key_down(SDL_KeyboardEvent *event) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		game.keyboard[event->keysym.scancode] = 1;
	}
}

static void key_up(SDL_KeyboardEvent* event) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		game.keyboard[event->keysym.scancode] = 0;
	}
}

static void mouse_down(SDL_MouseButtonEvent *event) {
	if (event->button >= 0 && event->button < MAX_MOUSE_BUTTONS)
	{
		game.mouse.buttons[event->button] = 1;
	}
}

static void mouse_up(SDL_MouseButtonEvent *event) {
	if (event->button >= 0 && event->button < MAX_MOUSE_BUTTONS)
	{
		game.mouse.buttons[event->button] = 0;
	}
}
