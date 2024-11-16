#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

#define MAX_TEXT_LENGTH 2048

typedef struct {
	char* 			filepath;
	char* 			content;
	SDL_Color		color;
	int 			x, y; 
	int 			fontsize;
	int 			tflags;
} Text;

typedef enum {
	TEXT_DEFAULT = 0,
	TEXT_CENTERED_Y = 1 << 0,
	TEXT_CENTERED_X = 1 << 1,
	TEXT_CENTERED = TEXT_CENTERED_X | TEXT_CENTERED_Y,
	TEXT_RIGHT_ALIGNED = 1 << 2,
} tflags;

void create_text(
	Text* text,
	char* filepath,
	char* content,
	int fontsize,
	SDL_Color color,
	int x, int y,
	int tflags
);

void render_text(const Text* text, SDL_Renderer* renderer);
static char* get_name_from_filepath(const char* filepath);
static TTF_Font* load_font(const char* filepath, int fontsize);
