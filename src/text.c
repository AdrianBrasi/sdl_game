#include "game.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "text.h"

extern Game game;

// TODO: make create_text function that handles different position flags

void render_text(const Text* text, SDL_Renderer* renderer) { 
	if (strlen(text->content) > MAX_TEXT_LENGTH) {
		fprintf(stderr, "Too much text in one rendering call");
		return;
	}

	TTF_Font* font = load_font(text->filepath, text->fontsize);
	if (!font) {
		fprintf(stderr, "Failed to load font\n");
		return;
	}

	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface* surface = TTF_RenderText_Solid(font, text->content, text->color);
	if (!surface) {
		fprintf(stderr, "Failed to apply font to surface\n");
		TTF_CloseFont(font);
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		fprintf(stderr, "Failed to create texture from surface\n");
		TTF_CloseFont(font);
		return;
	}

	SDL_Rect dstrect = {text->x, text->y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void free_font(const char* filepath) {
	TTF_Font* font = load_font(filepath, 0);
	if (font) {
		TTF_CloseFont(font);
	}
}

static char* get_name_from_filepath(const char* filepath) {
	const char* last_slash = strrchr(filepath, '/'); 
	const char* short_filename = last_slash ? last_slash + 1: filepath;

	size_t length = strlen(short_filename);
	char* result = malloc(length + 1);
	strncpy(result, short_filename, length);
	result[length] = '\0';

	return result;
}

static TTF_Font* load_font(const char* filepath, int fontsize) {
	TTF_Font* font = TTF_OpenFont(filepath, fontsize);
	char* filename = get_name_from_filepath(filepath);

	if (font == NULL) {
		fprintf(stderr, "Failed to load font: %s\n", filename);
	}

	free(filename);

	return font;
}

