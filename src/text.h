#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

#define MAX_TEXT_LENGTH 2048

typedef struct {
	TTF_Font* 		font;
	char* 			content;
	SDL_Color		color;
	int 			x, y; 
} Text;

// TODO: create button class that has a Text struct as a field

typedef enum {
	TEXT_DEFAULT = 0,
	TEXT_CENTERED_Y = 1 << 0,
	TEXT_CENTERED_X = 1 << 1,
	TEXT_CENTERED = TEXT_CENTERED_X | TEXT_CENTERED_Y,
	TEXT_RIGHT_ALIGNED = 1 << 2,
} tflags;

static char* get_name_from_filepath(const char* filepath);
TTF_Font* load_font(const char* filepath, int fontsize);
void place_static_text(SDL_Window* window, Text* text, int xpos, int ypos, int tflags);
void render_text(const Text* text, SDL_Renderer* renderer);
// TODO: place_floating_text
