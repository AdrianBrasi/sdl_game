#include "game.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "text.h"

extern Game game;

static char* get_name_from_filepath(const char* font_filepath) {
	const char* last_slash = strrchr(font_filepath, '/'); 
	const char* short_filename = last_slash ? last_slash + 1: font_filepath;

	size_t length = strlen(short_filename);
	char* result = malloc(length + 1);
	strncpy(result, short_filename, length);
	result[length] = '\0';

	return result;
}

TTF_Font* load_font(const char* font_filepath, int fontsize) {
	TTF_Font* font = TTF_OpenFont(font_filepath, fontsize);
	char* filename = get_name_from_filepath(font_filepath);

	if (font == NULL) {
		fprintf(stderr, "Failed to load font: %s\n", filename);
	}

	free(filename);

	return font;
}

void place_static_text(SDL_Window* window, Text* text, int xpos, int ypos, int tflags) {
    if (!text->font || !text->content) {
        fprintf(stderr, "Error: Font or content is not set.\n");
        return;
    }

    int w_width, w_height;
    SDL_GetWindowSize(window, &w_width, &w_height);

    int t_width = 0, t_height = 0;
    if (TTF_SizeText(text->font, text->content, &t_width, &t_height) != 0) {
        fprintf(stderr, "Error getting text dimensions: %s\n", TTF_GetError());
        return;
    }

    if (tflags & TEXT_CENTERED_X) {
        text->x = (w_width / 2) - (t_width / 2);
    } else {
        text->x = xpos;
    }

    if (tflags & TEXT_CENTERED_Y) {
        text->y = (w_height / 2) - (t_height / 2);
    } else {
        text->y = ypos;
    }
}

void render_text(const Text* text, SDL_Renderer* renderer) { 
	if (strlen(text->content) > MAX_TEXT_LENGTH) {
		fprintf(stderr, "Too much text in one rendering call");
		return;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(text->font, text->content, text->color);
	if (!surface) {
		fprintf(stderr, "Failed to apply font to surface\n");
		TTF_CloseFont(text->font);
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		fprintf(stderr, "Failed to create texture from surface\n");
		TTF_CloseFont(text->font);
		return;
	}

	SDL_Rect dstrect = {text->x, text->y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

