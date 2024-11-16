#include "render.h"
#include <stdlib.h>
#include <string.h>


void load_font(const char* filepath) {
	TTF_Font* font = TTF_OpenFont(filepath, 20);
	char* filename = get_name_from_filepath(filepath);
	if (font == NULL) {
		fprintf(stderr, "Failed to load font: %s\n", filename);
	} else {
		printf("Font properly loaded: %s\n", filename);
	}
	free(filename);
}

char* get_name_from_filepath(const char* filepath) {
	const char* last_slash = strrchr(filepath, '/'); 
	const char* short_filename = last_slash ? last_slash + 1: filepath;
	size_t length = strlen(short_filename);
	char* result = malloc(length + 1);
	strncpy(result, short_filename, length);
	result[length] = '\0';
	return result;
}
