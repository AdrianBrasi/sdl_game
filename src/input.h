#ifdef __APPLE__
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif


void handle_input();
void log_keyboard_input(SDL_KeyboardEvent* event);
void log_mouse_input(SDL_MouseButtonEvent* event);
static void key_down(SDL_KeyboardEvent* event);
static void key_up(SDL_KeyboardEvent* event);
static void mouse_down(SDL_MouseButtonEvent *event);
static void mouse_up(SDL_MouseButtonEvent *event);
